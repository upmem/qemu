#ifndef DPU_TRANSLATE_DEFS_H__
#define DPU_TRANSLATE_DEFS_H__

#include <stdbool.h>
#include <stdint.h>

#include "ctxt.h"
#include "conditions.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "exec/memop.h"
#include "exec/translator.h"
#include "tcg/tcg-op.h"
#include "tcg/tcg.h"
#include "exec/gen-icount.h"

// Global State

static TCGv cpu_gpr[NR_WORK_REGISTERS];
TCGv cpu_tid;
TCGv cpu_pc;
static TCGv cpu_cf, cpu_zf;

void dpu_translate_init(void) {
    for (uint32_t each_reg = 0; each_reg < NR_WORK_REGISTERS; ++each_reg) {
        cpu_gpr[each_reg] = tcg_global_mem_new(cpu_env, offsetof(DpuThreadState, regs[each_reg]), "reg");
    }
    cpu_tid = tcg_global_mem_new(cpu_env, offsetof(DpuThreadState, thread_idx), "tid");
    cpu_pc = tcg_global_mem_new(cpu_env, offsetof(DpuThreadState, pc), "pc");
    cpu_cf = tcg_global_mem_new(cpu_env, offsetof(DpuThreadState, cf), "cf");
    cpu_zf = tcg_global_mem_new(cpu_env, offsetof(DpuThreadState, zf), "zf");
}

void gen_goto_tb(TranslationBlock *tb, int n, target_ulong dest) {
    tcg_gen_goto_tb(n);
    tcg_gen_movi_tl(cpu_pc, dest);
    tcg_gen_exit_tb(tb, n);
}

typedef enum {
    OP_KIND_REG,
    OP_KIND_DOUBLE_REG,
    OP_KIND_VAL,
    OP_KIND_LABEL,
} operand_kind_t;

typedef enum {
    CTX_NONE,
    CTX_ADD,
    CTX_SUB,
    CTX_MUL,
    CTX_CNT,
    CTX_SHIFT,
} ctx_kind_t;

typedef struct {
    operand_kind_t kind;
    union {
        TCGv_i32 reg;
        TCGv_i64 dreg;
        uint64_t value;
        TCGLabel *label;
    };
    ctx_kind_t ctx;
    union {
        struct {
            TCGv_i32 arg1;
            TCGv_i32 arg2;
            TCGv_i32 arg3;
        } add_ctx;
        struct {
            TCGv_i32 arg1;
            TCGv_i32 arg2;
        } sub_ctx;
        struct {
            TCGv_i32 arg0;
        } mul_ctx;
        struct {
            uint32_t max_value;
        } cnt_ctx;
        struct {
            bool is_reg;
            union {
                TCGv_i32 reg_shift;
                uint32_t imm_shift;
            };
        } shift_ctx;
    };
    bool extract_forgot_6th_bit;
    bool extract_src_is_reg;
    union {
        TCGv_i32 extract_src_reg;
        uint64_t extract_src_value;
    };
} operand_t;

static const operand_t ZERO_OPERAND = { .kind = OP_KIND_VAL, .value = 0 };

static inline void set_operand_32(operand_t *op, uint32_t value) {
    op->kind = OP_KIND_VAL;
    op->value = value;
    op->ctx = CTX_NONE;
}

static inline void init_reg32(operand_t *op) {
    memset(op, 0, sizeof(*op));
    op->kind = OP_KIND_REG;
    op->reg = tcg_temp_local_new();
    op->ctx = CTX_NONE;
}

static inline void init_reg64(operand_t *op) {
    memset(op, 0, sizeof(*op));
    op->kind = OP_KIND_DOUBLE_REG;
    op->dreg = tcg_temp_local_new_i64();
    op->ctx = CTX_NONE;
}

static inline void assert_reg32(operand_t op) {
    assert(op.kind == OP_KIND_REG && "expected a 32-bit register operand");
}

static inline void assert_reg64(operand_t op) {
    assert(op.kind == OP_KIND_DOUBLE_REG && "expected a 64-bit register operand");
}

static inline void assert_val(operand_t op) {
    assert(op.kind == OP_KIND_VAL && "expected a value operand");
}

static inline void assert_label(operand_t op) {
    assert(op.kind == OP_KIND_LABEL && "expected a label operand");
}

static inline TCGv promote_value(operand_t op) {
    if (op.kind == OP_KIND_VAL) {
        TCGv tmp = tcg_temp_local_new();
        tcg_gen_movi_tl(tmp, op.value);
        return tmp;
    }

    assert_reg32(op);
    return op.reg;
}

static inline TCGv_i64 promote_value64(operand_t op) {
    if (op.kind == OP_KIND_VAL) {
        TCGv_i64 tmp = tcg_temp_local_new_i64();
        tcg_gen_movi_i64(tmp, op.value);
        return tmp;
    }

    assert_reg64(op);
    return op.dreg;
}

static inline void free_if_value(operand_t op, TCGv tmp) {
    if (op.kind == OP_KIND_VAL) {
        tcg_temp_free(tmp);
    }
}

static inline void free_if_value64(operand_t op, TCGv_i64 tmp) {
    if (op.kind == OP_KIND_VAL) {
        tcg_temp_free_i64(tmp);
    }
}

static inline void free_operand_if_needed(operand_t *op) {
    switch (op->kind) {
        default:
            break;
        case OP_KIND_REG:
            tcg_temp_free(op->reg);
            break;
        case OP_KIND_DOUBLE_REG:
            tcg_temp_free_i64(op->dreg);
            break;
    }
}

static inline void operand_reassign(operand_t *dst, operand_t src) {
    if (dst->kind == OP_KIND_VAL) {
        switch (src.kind) {
            default:
                assert(false && "expected a 32/64-bit reg or a value");
                break;
            case OP_KIND_VAL:
            case OP_KIND_REG:
                init_reg32(dst);
                break;
            case OP_KIND_DOUBLE_REG:
                init_reg64(dst);
                break;
        }
    }

    switch (src.kind) {
        default:
            assert(false && "expected a 32/64-bit reg or a value");
            break;
        case OP_KIND_VAL:
            assert((dst->kind == OP_KIND_REG) && "expected a 32-bit reg");
            tcg_gen_movi_tl(dst->reg, src.value);
            break;
        case OP_KIND_REG:
            assert((dst->kind == OP_KIND_REG) && "expected a 32-bit reg");
            tcg_gen_mov_tl(dst->reg, src.reg);
            break;
        case OP_KIND_DOUBLE_REG:
            assert((dst->kind == OP_KIND_DOUBLE_REG) && "expected a 64-bit reg");
            tcg_gen_mov_i64(dst->dreg, src.dreg);
            break;
    }

    if (src.ctx != CTX_NONE) {
        if (dst->ctx != CTX_NONE) {
            dst->ctx = CTX_NONE;
            return;
        }

        dst->ctx = src.ctx;
        switch (src.ctx) {
            default:
                assert(false && "unexpected context kind");
                break;
            case CTX_ADD:
                dst->add_ctx.arg1 = src.add_ctx.arg1;
                dst->add_ctx.arg2 = src.add_ctx.arg2;
                dst->add_ctx.arg3 = src.add_ctx.arg3;
                break;
            case CTX_CNT:
                dst->cnt_ctx.max_value = src.cnt_ctx.max_value;
                break;
            case CTX_MUL:
                dst->mul_ctx.arg0 = src.mul_ctx.arg0;
                break;
            case CTX_SHIFT:
                dst->shift_ctx.is_reg = src.shift_ctx.is_reg;
                if (src.shift_ctx.is_reg) {
                    dst->shift_ctx.reg_shift = src.shift_ctx.reg_shift;
                } else {
                    dst->shift_ctx.imm_shift = src.shift_ctx.imm_shift;
                }
                break;
            case CTX_SUB:
                dst->sub_ctx.arg1 = src.sub_ctx.arg1;
                dst->sub_ctx.arg2 = src.sub_ctx.arg2;
                break;
        }
    }
}

// REPLAYS
// TODO

#define may_replay_rr()
#define may_replay_rd()
#define next_instruction_will_not_replay()
#define next_instruction_may_replay_32()
#define next_instruction_may_replay_64()

// FLAGS

typedef enum {
    DPU_CF,
    DPU_ZF,
} dpu_flag_t;

static inline void get_flag(operand_t *dst, DisasContext *ctx, dpu_flag_t flag) {
    init_reg32(dst);
    TCGv flag_reg;

    switch (flag) {
        case DPU_CF:
            flag_reg = cpu_cf;
            break;
        case DPU_ZF:
            flag_reg = cpu_zf;
            break;
    }

    tcg_gen_mov_tl(dst->reg, flag_reg);
}

static inline void save_flag(DisasContext *ctx, operand_t op, dpu_flag_t flag) {
    TCGv flag_value = tcg_temp_new();
    TCGv flag_reg;

    switch (flag) {
        case DPU_CF:
            flag_reg = cpu_cf;
            switch (op.ctx) {
                default:
                    assert(false && "invalid context kind");
                    break;
                case CTX_ADD: {
                    TCGv zero = tcg_const_tl(0);
                    TCGv res = tcg_temp_new();
                    tcg_gen_add2_tl(res, flag_value, op.add_ctx.arg1, zero, op.add_ctx.arg2, zero);
                    tcg_gen_add2_tl(res, flag_value, res, flag_value, op.add_ctx.arg3, zero);
                    tcg_temp_free(res);
                    tcg_temp_free(zero);
                    break;
                }
                case CTX_SUB:
                    tcg_gen_setcond_tl(TCG_COND_GEU, flag_value, op.sub_ctx.arg1, op.sub_ctx.arg2);
                    break;
            }
            break;
        case DPU_ZF:
            flag_reg = cpu_zf;
            switch (op.kind) {
                default:
                    assert(false && "invalid operand");
                    break;
                case OP_KIND_REG:
                    tcg_gen_setcondi_tl(TCG_COND_EQ, flag_value, op.reg, 0);
                    break;
                case OP_KIND_DOUBLE_REG: {
                    TCGv_i64 val = tcg_temp_new_i64();
                    tcg_gen_setcondi_i64(TCG_COND_EQ, val, op.dreg, 0);
                    tcg_gen_extrl_i64_i32(flag_value, val);
                    tcg_temp_free_i64(val);
                    break;
                }
                case OP_KIND_VAL:
                    tcg_gen_movi_tl(flag_value, op.value == 0 ? 1 : 0);
                    break;
            }
            break;
    }

    tcg_gen_mov_tl(flag_reg, flag_value);
    tcg_temp_free(flag_value);
}

#define get_status_flag_carry(dst) get_flag(dst, ctx, DPU_CF)
#define save_status_flag_zero(op) save_flag(ctx, op, DPU_ZF)
#define save_status_flag_carry(op) save_flag(ctx, op, DPU_CF)

// REGISTERS

static inline void get_reg(operand_t *dst, DisasContext *ctx, uint8_t idx) {
    switch (idx) {
    default: {
      init_reg32(dst);
      TCGv reg = cpu_gpr[idx];
      tcg_gen_mov_tl(dst->reg, reg);
      break;
    }
    case DPU_REG_ZERO:
      set_operand_32(dst, 0);
      break;
    case DPU_REG_ONE:
      set_operand_32(dst, 1);
      break;
    case DPU_REG_LNEG:
      set_operand_32(dst, 0xffffffff);
      break;
    case DPU_REG_MNEG:
      set_operand_32(dst, 0x80000000);
      break;
    case DPU_REG_ID:
      init_reg32(dst);
      tcg_gen_mov_tl(dst->reg, cpu_tid);
      break;
    case DPU_REG_ID2:
      init_reg32(dst);
      tcg_gen_shli_tl(dst->reg, cpu_tid, 1);
      break;
    case DPU_REG_ID4:
      init_reg32(dst);
      tcg_gen_shli_tl(dst->reg, cpu_tid, 2);
      break;
    case DPU_REG_ID8:
      init_reg32(dst);
      tcg_gen_shli_tl(dst->reg, cpu_tid, 3);
      break;
    }
}

static inline void get_dreg(operand_t *dst, DisasContext *ctx, uint8_t idx) {
    init_reg64(dst);
    TCGv high = cpu_gpr[idx];
    TCGv low = cpu_gpr[idx + 1];
    tcg_gen_concat_tl_i64(dst->dreg, low, high);
}

static inline void set_reg(DisasContext *ctx, operand_t src, uint8_t idx) {
    assert((src.kind == OP_KIND_VAL || src.kind == OP_KIND_REG) && "expected a 32-bit reg or a value");
    TCGv reg = cpu_gpr[idx];

    if (src.kind == OP_KIND_VAL) {
        tcg_gen_movi_tl(reg, src.value);
    } else {
        tcg_gen_mov_tl(reg, src.reg);
    }
}

static inline void set_dreg(DisasContext *ctx, operand_t src, uint8_t idx) {
    assert_reg64(src);
    TCGv high = tcg_temp_new();
    TCGv low = tcg_temp_new();
    tcg_gen_extr_i64_tl(low, high, src.dreg);

    tcg_gen_mov_tl(cpu_gpr[idx], high);
    tcg_gen_mov_tl(cpu_gpr[idx + 1], low);

    tcg_temp_free(high);
    tcg_temp_free(low);
}

#define get_reg_ra(dst) get_reg(&(dst), ctx, descriptor->ra)
#define get_reg_rb(dst) get_reg(&(dst), ctx, descriptor->rb)
#define get_reg_id(dst) get_reg(&(dst), ctx, DPU_REG_ID)
#define get_reg_dbe(dst) get_reg(&(dst), ctx, descriptor->db)
#define get_reg_dbo(dst) get_reg(&(dst), ctx, descriptor->db + 1)
#define get_reg_db(dst) get_dreg(&(dst), ctx, descriptor->db)

#define set_reg_rc(src) set_reg(ctx, src, descriptor->rc)
#define set_reg_dce(src) set_reg(ctx, src, descriptor->dc)
#define set_reg_dco(src) set_reg(ctx, src, descriptor->dc + 1)
#define set_reg_dc(src) set_dreg(ctx, src, descriptor->dc)

// BIT OPERATIONS

static inline void sext(operand_t *dst, operand_t src, uint32_t src_length, uint32_t dst_length) {
    assert((src.kind == OP_KIND_VAL || src.kind == OP_KIND_REG) && "expected a 32-bit reg or a value");

    switch (src.kind) {
        default:
            break;
        case OP_KIND_REG:
            if (dst_length == 32) {
                init_reg32(dst);
                dst->ctx = src.ctx;
                switch (dst->ctx) {
                    default:
                        assert(false && "invalid context type");
                        break;
                    case CTX_NONE:
                        break;
                    case CTX_ADD:
                        dst->add_ctx = src.add_ctx;
                        break;
                    case CTX_SUB:
                        dst->sub_ctx = src.sub_ctx;
                        break;
                    case CTX_MUL:
                        dst->mul_ctx = src.mul_ctx;
                        break;
                    case CTX_CNT:
                        dst->cnt_ctx = src.cnt_ctx;
                        break;
                    case CTX_SHIFT:
                        dst->shift_ctx = src.shift_ctx;
                        break;
                }

                switch (src_length) {
                    default:
                        assert(false && "invalid source length for a 32-bit extension");
                        break;
                    case 8:
                        tcg_gen_ext8s_tl(dst->reg, src.reg);
                        break;
                    case 16:
                        tcg_gen_ext16s_tl(dst->reg, src.reg);
                        break;
                }
            } else if (dst_length == 64) {
                init_reg64(dst);
                switch (src_length) {
                    default:
                        assert(false && "invalid source length for a 64-bit extension");
                        break;
                    case 8: {
                        TCGv tmp = tcg_temp_new();
                        tcg_gen_ext8s_tl(tmp, src.reg);
                        tcg_gen_ext_i32_i64(dst->dreg, tmp);
                        tcg_temp_free(tmp);
                        break;
                    }
                    case 16: {
                        TCGv tmp = tcg_temp_new();
                        tcg_gen_ext16s_tl(tmp, src.reg);
                        tcg_gen_ext_i32_i64(dst->dreg, tmp);
                        tcg_temp_free(tmp);
                        break;
                    }
                    case 32:
                        tcg_gen_ext_i32_i64(dst->dreg, src.reg);
                        break;
                }
            } else {
                assert(false && "invalid extension length");
            }
            break;
        case OP_KIND_VAL: {
            uint64_t mask = (uint64_t)((1L << src_length) - 1);
            uint64_t mask_to = ((dst_length == 64) ? 0xFFFFFFFFFFFFFFFFL : (uint64_t)((1L << dst_length) - 1));
            uint64_t value = src.value & mask;

            if ((value & ((1L << (src_length - 1)))) != 0) {
                value |= (~mask & mask_to);
            }

            if (dst_length == 64) {
                init_reg64(dst);
                tcg_gen_movi_i64(dst->dreg, value);
            } else {
                dst->kind = OP_KIND_VAL;
                dst->value = value;
            }
            break;
        }
    }
}

static inline void uext(operand_t *dst, operand_t src, uint32_t src_length, uint32_t dst_length) {
    assert((src.kind == OP_KIND_VAL || src.kind == OP_KIND_REG) && "expected a 32-bit reg or a value");

    switch (src.kind) {
        default:
            break;
        case OP_KIND_REG:
            if (dst_length == 32) {
                init_reg32(dst);
                dst->ctx = src.ctx;
                switch (dst->ctx) {
                    default:
                        assert(false && "invalid context type");
                        break;
                    case CTX_NONE:
                        break;
                    case CTX_ADD:
                        dst->add_ctx = src.add_ctx;
                        break;
                    case CTX_SUB:
                        dst->sub_ctx = src.sub_ctx;
                        break;
                    case CTX_MUL:
                        dst->mul_ctx = src.mul_ctx;
                        break;
                    case CTX_CNT:
                        dst->cnt_ctx = src.cnt_ctx;
                        break;
                    case CTX_SHIFT:
                        dst->shift_ctx = src.shift_ctx;
                        break;
                }

                switch (src_length) {
                    default:
                        assert(false && "invalid source length for a 32-bit extension");
                        break;
                    case 8:
                        tcg_gen_ext8u_tl(dst->reg, src.reg);
                        break;
                    case 16:
                        tcg_gen_ext16u_tl(dst->reg, src.reg);
                        break;
                }
            } else if (dst_length == 64) {
                init_reg64(dst);
                switch (src_length) {
                    default:
                        assert(false && "invalid source length for a 64-bit extension");
                        break;
                    case 8: {
                        TCGv tmp = tcg_temp_new();
                        tcg_gen_ext8u_tl(tmp, src.reg);
                        tcg_gen_extu_i32_i64(dst->dreg, tmp);
                        tcg_temp_free(tmp);
                        break;
                    }
                    case 16: {
                        TCGv tmp = tcg_temp_new();
                        tcg_gen_ext16u_tl(tmp, src.reg);
                        tcg_gen_extu_i32_i64(dst->dreg, tmp);
                        tcg_temp_free(tmp);
                        break;
                    }
                    case 32:
                        tcg_gen_extu_i32_i64(dst->dreg, src.reg);
                        break;
                }
            } else {
                assert(false && "invalid extension length");
            }
            break;

        case OP_KIND_VAL:
            if (dst_length == 64) {
                init_reg64(dst);
                tcg_gen_movi_i64(dst->dreg, src.value & (uint64_t)((1l << src_length) - 1));
            } else {
                dst->kind = OP_KIND_VAL;
                dst->value = src.value & (uint64_t)((1l << src_length) - 1);
            }
            break;
    }
}

#define sext_8_32(src, dst) sext(dst, src, 8, 32)
#define sext_11_32(src, dst) sext(dst, src, 11, 32)
#define sext_12_32(src, dst) sext(dst, src, 12, 32)
#define sext_16_32(src, dst) sext(dst, src, 16, 32)
#define sext_17_32(src, dst) sext(dst, src, 17, 32)
#define sext_24_32(src, dst) sext(dst, src, 24,32)
#define sext_27_32(src, dst) sext(dst, src, 27, 32)
#define sext_28_32(src, dst) sext(dst, src, 28, 32)
#define sext_8_64(src, dst) sext(dst, src, 8, 64)
#define sext_16_64(src, dst) sext(dst, src, 16, 64)
#define sext_32_64(src, dst) sext(dst, src, 32, 64)

#define uext_1_32(src, dst) uext(dst, src, 1, 32)
#define uext_5_32(src, dst) uext(dst, src, 5, 32)
#define uext_8_32(src, dst) uext(dst, src, 8, 32)
#define uext_16_32(src, dst) uext(dst, src, 16, 32)
#define uext_22_32(src, dst) uext(dst, src, 22, 32)
#define uext_24_32(src, dst) uext(dst, src, 24, 32)
#define uext_28_32(src, dst) uext(dst, src, 28, 32)
#define uext_8_64(src, dst) uext(dst, src, 8, 64)
#define uext_16_64(src, dst) uext(dst, src, 16, 64)
#define uext_32_64(src, dst) uext(dst, src, 32, 64)

static inline void extract_bits(operand_t *dst, operand_t src, uint8_t from, uint8_t to) {
    switch (src.kind) {
        default:
            assert(false && "unexpected op kind for bit extraction");
            break;
        case OP_KIND_VAL:
            dst->kind = OP_KIND_VAL;
            dst->value = (src.value >> from) & ((1 << (to - from + 1)) - 1);
            dst->extract_forgot_6th_bit = to < 5;
            dst->extract_src_is_reg = false;
            dst->extract_src_value = src.value;
            break;
        case OP_KIND_REG:
            init_reg32(dst);
            tcg_gen_extract_tl(dst->reg, src.reg, from, to - from + 1);
            dst->extract_forgot_6th_bit = to < 5;
            dst->extract_src_is_reg = true;
            dst->extract_src_reg = src.reg;
            break;
        case OP_KIND_DOUBLE_REG: {
            init_reg32(dst);
            TCGv_i64 tmp = tcg_temp_new_i64();
            tcg_gen_extract_i64(tmp, src.dreg, from, to - from + 1);
            tcg_gen_extrl_i64_i32(dst->reg, tmp);
            tcg_temp_free_i64(tmp);
            break;
        }
    }
}

#define get_bits(src, from, to, dst) extract_bits(dst, src, from, to)

// ALU OPERATIONS

static inline void _bitflip(operand_t *dst, operand_t op) {
    TCGv arg = promote_value(op);
    init_reg32(dst);
    tcg_gen_not_i32(dst->reg, arg);
    free_if_value(op, arg);
}

static inline void _cao(operand_t *dst, operand_t op) {
    TCGv arg = promote_value(op);
    init_reg32(dst);
    tcg_gen_ctpop_tl(dst->reg, arg);
    dst->ctx = CTX_CNT;
    dst->cnt_ctx.max_value = 32;
    free_if_value(op, arg);
}

static inline void _clz(operand_t *dst, operand_t op) {
    TCGv arg = promote_value(op);
    init_reg32(dst);
    tcg_gen_clzi_tl(dst->reg, arg, TARGET_LONG_BITS);
    dst->ctx = CTX_CNT;
    dst->cnt_ctx.max_value = 32;
    free_if_value(op, arg);
}

static inline void _clo(operand_t *dst, operand_t op) {
    TCGv arg = promote_value(op);
    init_reg32(dst);
    tcg_gen_not_i32(dst->reg, arg);
    tcg_gen_clzi_tl(dst->reg, dst->reg, TARGET_LONG_BITS);
    dst->ctx = CTX_CNT;
    dst->cnt_ctx.max_value = 32;
    free_if_value(op, arg);
}

static inline void _cls(operand_t *dst, operand_t op) {
    TCGv arg = promote_value(op);
    init_reg32(dst);
    tcg_gen_clrsb_tl(dst->reg, arg);
    dst->ctx = CTX_CNT;
    dst->cnt_ctx.max_value = 31;
    free_if_value(op, arg);
}

static inline void _sats(operand_t *dst, operand_t op) {
    TCGv arg = promote_value(op);
    init_reg32(dst);
    TCGv zero = tcg_const_tl(0);
    TCGv mpos = tcg_const_tl(0x7fffffff);
    TCGv mneg = tcg_const_tl(0x80000000);
    tcg_gen_movcond_i32(TCG_COND_LT, dst->reg, arg, zero, mpos, mneg);
    tcg_temp_free(mneg);
    tcg_temp_free(mpos);
    tcg_temp_free(zero);
    free_if_value(op, arg);
}

static inline void gen_alu2_op(operand_t *dst, operand_t op1, operand_t op2, void (*fn)(TCGv, TCGv, TCGv)) {
    init_reg32(dst);
    TCGv arg1 = promote_value(op1);
    TCGv arg2 = promote_value(op2);
    fn(dst->reg, arg1, arg2);
    free_if_value(op2, arg2);
    free_if_value(op1, arg1);
}

static inline void _sub(operand_t *dst, operand_t op1, operand_t op2) {
    init_reg32(dst);
    TCGv arg1 = promote_value(op1);
    TCGv arg2 = promote_value(op2);
    dst->ctx = CTX_SUB;
    dst->sub_ctx.arg1 = arg1;
    dst->sub_ctx.arg2 = arg2;
    tcg_gen_sub_tl(dst->reg, arg1, arg2);
}

static inline void _and(operand_t *dst, operand_t op1, operand_t op2) {
    gen_alu2_op(dst, op1, op2, tcg_gen_and_tl);
}

static inline void _or(operand_t *dst, operand_t op1, operand_t op2) {
    gen_alu2_op(dst, op1, op2, tcg_gen_or_tl);
}

static inline void _xor(operand_t *dst, operand_t op1, operand_t op2) {
    gen_alu2_op(dst, op1, op2, tcg_gen_xor_tl);
}

static inline void _asr(operand_t *dst, operand_t op1, operand_t op2) {
    gen_alu2_op(dst, op1, op2, tcg_gen_sar_tl);

    dst->ctx = CTX_SHIFT;
    dst->shift_ctx.is_reg = op2.kind == OP_KIND_REG;
    if (dst->shift_ctx.is_reg) {
        dst->shift_ctx.reg_shift = op2.reg;
    } else {
        dst->shift_ctx.imm_shift = op2.value;
    }
    dst->extract_forgot_6th_bit = op2.extract_forgot_6th_bit;
    if (dst->extract_forgot_6th_bit) {
        dst->extract_src_is_reg = op2.extract_src_is_reg;
        if (dst->extract_src_is_reg) {
            dst->extract_src_reg = op2.extract_src_reg;
        } else {
            dst->extract_src_value = op2.extract_src_value;
        }
    }
}

static inline void _rol(operand_t *dst, operand_t op1, operand_t op2) {
    gen_alu2_op(dst, op1, op2, tcg_gen_rotl_tl);

    dst->ctx = CTX_SHIFT;
    dst->shift_ctx.is_reg = op2.kind == OP_KIND_REG;
    if (dst->shift_ctx.is_reg) {
        dst->shift_ctx.reg_shift = op2.reg;
    } else {
        dst->shift_ctx.imm_shift = op2.value;
    }
    dst->extract_forgot_6th_bit = op2.extract_forgot_6th_bit;
    if (dst->extract_forgot_6th_bit) {
        dst->extract_src_is_reg = op2.extract_src_is_reg;
        if (dst->extract_src_is_reg) {
            dst->extract_src_reg = op2.extract_src_reg;
        } else {
            dst->extract_src_value = op2.extract_src_value;
        }
    }
}

static inline void _ror(operand_t *dst, operand_t op1, operand_t op2) {
    gen_alu2_op(dst, op1, op2, tcg_gen_rotr_tl);

    dst->ctx = CTX_SHIFT;
    dst->shift_ctx.is_reg = op2.kind == OP_KIND_REG;
    if (dst->shift_ctx.is_reg) {
        dst->shift_ctx.reg_shift = op2.reg;
    } else {
        dst->shift_ctx.imm_shift = op2.value;
    }
    dst->extract_forgot_6th_bit = op2.extract_forgot_6th_bit;
    if (dst->extract_forgot_6th_bit) {
        dst->extract_src_is_reg = op2.extract_src_is_reg;
        if (dst->extract_src_is_reg) {
            dst->extract_src_reg = op2.extract_src_reg;
        } else {
            dst->extract_src_value = op2.extract_src_value;
        }
    }
}

static inline void _cmpb4(operand_t *dst, operand_t op1, operand_t op2) {
    init_reg32(dst);
    TCGv arg1 = promote_value(op1);
    TCGv arg2 = promote_value(op2);
    TCGv tmp1 = tcg_temp_new();
    TCGv tmp2 = tcg_temp_new();
    tcg_gen_movi_tl(dst->reg, 0);
    for (uint32_t i = 0; i < sizeof(uint32_t); ++i) {
        uint32_t shift = 8 * i;
        tcg_gen_extract_tl(tmp1, arg1, shift, 8);
        tcg_gen_extract_tl(tmp2, arg2, shift, 8);
        tcg_gen_setcond_tl(TCG_COND_EQ, tmp1, tmp1, tmp2);
        tcg_gen_deposit_tl(dst->reg, dst->reg, tmp1, shift, 8);
    }
    tcg_temp_free(tmp2);
    tcg_temp_free(tmp1);
    free_if_value(op2, arg2);
    free_if_value(op1, arg1);
}

static inline void _hash(operand_t *dst, operand_t op1, operand_t op2) {
    // TODO possible optimization if op2 is a value

    init_reg32(dst);
    TCGv arg1 = promote_value(op1);
    TCGv arg2 = promote_value(op2);
    TCGv zero = tcg_const_tl(0);
    TCGv one = tcg_const_tl(1);
    TCGv shift = tcg_temp_new();
    TCGv mask = tcg_temp_new();
    TCGv part = tcg_temp_new();
    tcg_gen_shri_tl(shift, arg2, 2);
    tcg_gen_addi_tl(shift, shift, 7);
    tcg_gen_shl_tl(mask, one, shift);
    tcg_gen_subi_tl(mask, mask, 1);
    tcg_gen_and_tl(dst->reg, arg1, mask);
    tcg_gen_shr_tl(part, arg1, shift);
    tcg_gen_and_tl(part, part, mask);
    tcg_gen_xor_tl(dst->reg, dst->reg, part);
    tcg_gen_shli_tl(shift, shift, 1);
    tcg_gen_shr_tl(part, arg1, shift);
    tcg_gen_and_tl(part, part, mask);
    tcg_gen_andi_tl(mask, arg2, 1);
    tcg_gen_movcond_tl(TCG_COND_EQ, part, mask, one, part, zero);
    tcg_gen_xor_tl(dst->reg, dst->reg, part);
    tcg_temp_free(part);
    tcg_temp_free(mask);
    tcg_temp_free(shift);
    tcg_temp_free(one);
    tcg_temp_free(zero);
    free_if_value(op2, arg2);
    free_if_value(op1, arg1);
}

static inline void _add3(operand_t *dst, operand_t op1, operand_t op2, operand_t op3) {
    init_reg32(dst);
    TCGv arg1 = promote_value(op1);
    TCGv arg2 = promote_value(op2);
    TCGv arg3 = promote_value(op3);
    dst->ctx = CTX_ADD;
    dst->add_ctx.arg1 = arg1;
    dst->add_ctx.arg2 = arg2;
    dst->add_ctx.arg3 = arg3;
    tcg_gen_add_tl(dst->reg, arg1, arg2);
    tcg_gen_add_tl(dst->reg, dst->reg, arg3);
}

static inline void _lsl(operand_t *dst, operand_t op1, operand_t op2, operand_t op3) {
    assert_val(op3);
    if (op3.value == 0) {
        gen_alu2_op(dst, op1, op2, tcg_gen_shl_tl);
    } else {
        init_reg32(dst);
        TCGv arg1 = promote_value(op1);
        TCGv arg2 = promote_value(op2);
        TCGv one = tcg_const_tl(1);
        TCGv mask = tcg_temp_new();
        tcg_gen_shl_tl(dst->reg, arg1, arg2);
        tcg_gen_shl_tl(mask, one, arg2);
        tcg_gen_subi_tl(mask, mask, 1);
        tcg_gen_or_tl(dst->reg, dst->reg, mask);
        tcg_temp_free(mask);
        tcg_temp_free(one);
        free_if_value(op2, arg2);
        free_if_value(op1, arg1);
    }

    dst->ctx = CTX_SHIFT;
    dst->shift_ctx.is_reg = op2.kind == OP_KIND_REG;
    if (dst->shift_ctx.is_reg) {
        dst->shift_ctx.reg_shift = op2.reg;
    } else {
        dst->shift_ctx.imm_shift = op2.value;
    }
    dst->extract_forgot_6th_bit = op2.extract_forgot_6th_bit;
    if (dst->extract_forgot_6th_bit) {
        dst->extract_src_is_reg = op2.extract_src_is_reg;
        if (dst->extract_src_is_reg) {
            dst->extract_src_reg = op2.extract_src_reg;
        } else {
            dst->extract_src_value = op2.extract_src_value;
        }
    }
}

static inline void _lsr(operand_t *dst, operand_t op1, operand_t op2, operand_t op3) {
    assert_val(op3);
    if (op3.value == 0) {
        gen_alu2_op(dst, op1, op2, tcg_gen_shr_tl);
    } else {
        init_reg32(dst);
        TCGv arg1 = promote_value(op1);
        TCGv arg2 = promote_value(op2);
        TCGv one = tcg_const_tl(1);
        TCGv mask = tcg_temp_new();
        tcg_gen_shr_tl(dst->reg, arg1, arg2);
        tcg_gen_shl_tl(mask, one, arg2);
        tcg_gen_subi_tl(mask, mask, 1);
        tcg_gen_rotr_tl(mask, mask, arg2);
        tcg_gen_or_tl(dst->reg, dst->reg, mask);
        tcg_temp_free(mask);
        tcg_temp_free(one);
        free_if_value(op2, arg2);
        free_if_value(op1, arg1);
    }

    dst->ctx = CTX_SHIFT;
    dst->shift_ctx.is_reg = op2.kind == OP_KIND_REG;
    if (dst->shift_ctx.is_reg) {
        dst->shift_ctx.reg_shift = op2.reg;
    } else {
        dst->shift_ctx.imm_shift = op2.value;
    }
    dst->extract_forgot_6th_bit = op2.extract_forgot_6th_bit;
    if (dst->extract_forgot_6th_bit) {
        dst->extract_src_is_reg = op2.extract_src_is_reg;
        if (dst->extract_src_is_reg) {
            dst->extract_src_reg = op2.extract_src_reg;
        } else {
            dst->extract_src_value = op2.extract_src_value;
        }
    }
}

typedef enum {
    MUL_S,
    MUL_SU,
    MUL_U,
} dpu_mul_kind_t;

static inline void _mul8(operand_t *dst, operand_t op1, operand_t op2, operand_t op3, dpu_mul_kind_t mul_kind) {
    init_reg32(dst);
    assert_reg32(op1);
    assert_reg32(op2);
    assert_reg32(op3);
    dst->ctx = CTX_MUL;
    dst->mul_ctx.arg0 = op3.reg;

    TCGv arg1 = tcg_temp_new();
    TCGv arg2 = tcg_temp_new();

    switch (mul_kind) {
        case MUL_U:
            tcg_gen_ext8u_tl(arg1, op1.reg);
            tcg_gen_ext8u_tl(arg2, op2.reg);
            break;
        case MUL_S:
            tcg_gen_ext8s_tl(arg1, op1.reg);
            tcg_gen_ext8s_tl(arg2, op2.reg);
            break;
        case MUL_SU:
            tcg_gen_ext8s_tl(arg1, op1.reg);
            tcg_gen_ext8u_tl(arg2, op2.reg);
            break;
    }

    tcg_gen_mul_tl(dst->reg, arg1, arg2);
    tcg_gen_ext16u_tl(dst->reg, dst->reg);

    tcg_temp_free(arg2);
    tcg_temp_free(arg1);
}

#define bitflip(op, dst) _bitflip(dst, op)
#define cao(op, dst) _cao(dst, op)
#define clz(op, dst) _clz(dst, op)
#define clo(op, dst) _clo(dst, op)
#define cls(op, dst) _cls(dst, op)
#define sats(op, dst) _sats(dst, op)

#define add(op1, op2, dst) add3(op1, op2, ZERO_OPERAND, dst)
#define sub(op1, op2, dst) _sub(dst, op1, op2)
#define and(op1, op2, dst) _and(dst, op1, op2)
#define or(op1, op2, dst) _or(dst, op1, op2)
#define xor(op1, op2, dst) _xor(dst, op1, op2)
#define asr(op1, op2, dst) _asr(dst, op1, op2)
#define rol(op1, op2, dst) _rol(dst, op1, op2)
#define ror(op1, op2, dst) _ror(dst, op1, op2)
#define cmpb4(op1, op2, dst) _cmpb4(dst, op1, op2)
#define hash(op1, op2, dst) _hash(dst, op1, op2)

#define add3(op1, op2, op3, dst) _add3(dst, op1, op2, op3)
#define lsl(op1, op2, op3, dst) _lsl(dst, op1, op2, op3)
#define lsr(op1, op2, op3, dst) _lsr(dst, op1, op2, op3)

#define mul8u(op1, op2, op3, dst) _mul8(dst, op1, op2, op3, MUL_U)
#define mul8s(op1, op2, op3, dst) _mul8(dst, op1, op2, op3, MUL_S)
#define mul8su(op1, op2, op3, dst) _mul8(dst, op1, op2, op3, MUL_SU)

// ATOMIC OPERATIONS

static inline void atomic_op(operand_t *dst, operand_t op, bool set) {
    assert_reg32(op);
    init_reg32(dst);
    TCGv addr = tcg_temp_new();
    TCGv val = tcg_const_tl(set ? 1 : 0);
    tcg_gen_ori_tl(addr, op.reg, ATOMIC_ADDR_OFFSET);
    tcg_gen_atomic_xchg_tl(dst->reg, addr, val, 0, MO_UB);
    tcg_temp_free(val);
    tcg_temp_free(addr);
}

static inline void _acquire(operand_t *dst, operand_t op) {
    atomic_op(dst, op, true);
}

static inline void _release(operand_t *dst, operand_t op) {
    atomic_op(dst, op, false);
}

#define acquire(op, dst) _acquire(dst, op)
#define release(op, dst) _release(dst, op)

// CONDITIONS

static const operand_t const_cc_zero = { .kind = OP_KIND_VAL, .value = z_cc };
static const operand_t const_cc_geu = { .kind = OP_KIND_VAL, .value = geu_cc };
static const operand_t const_cc_ge0 = { .kind = OP_KIND_VAL, .value = geu_cc };

static inline void evaluate_ncX_cond(operand_t op, TCGLabel *otherwise, uint8_t carry_idx) {
    assert(op.ctx == CTX_ADD && "expecting an add to resolve this condition");
    TCGv tmp1 = tcg_temp_new();
    TCGv tmp2 = tcg_temp_new();
    TCGv tmp3 = tcg_temp_new();
    TCGv res = tcg_temp_new();

    tcg_gen_extract_tl(tmp1, op.add_ctx.arg1, 0, carry_idx);
    tcg_gen_extract_tl(tmp2, op.add_ctx.arg2, 0, carry_idx);
    tcg_gen_extract_tl(tmp3, op.add_ctx.arg3, 0, carry_idx);

    tcg_gen_add_tl(res, tmp1, tmp2);
    tcg_gen_add_tl(res, res, tmp3);
    tcg_gen_shri_tl(res, res, carry_idx);
    tcg_gen_brcondi_tl(TCG_COND_NE, res, 0, otherwise);

    tcg_temp_free(tmp1);
    tcg_temp_free(tmp2);
    tcg_temp_free(tmp3);
    tcg_temp_free(res);
}

static inline void _evaluate_condition(DisasContext *ctx, operand_t cond, operand_t op, operand_t label, operand_t src_reg_op) {
    assert_val(cond);
    assert_label(label);

    TCGv arg = promote_value(op);
    TCGLabel *otherwise = label.label;
    TCGv src_reg = promote_value(src_reg_op);

    TCGv carry = tcg_temp_new();
    TCGv overflow = tcg_temp_new();

    if (op.ctx == CTX_ADD) {
        TCGv zero = tcg_const_tl(0);
        TCGv res = tcg_temp_new();
        tcg_gen_add2_tl(res, carry, op.add_ctx.arg1, zero, op.add_ctx.arg2, zero);
        tcg_gen_add2_tl(res, carry, res, carry, op.add_ctx.arg3, zero);
        tcg_temp_free(res);

        TCGv_i64 tmp1 = tcg_temp_new_i64();
        TCGv_i64 tmp2 = tcg_temp_new_i64();
        TCGv_i64 tmp3 = tcg_temp_new_i64();
        TCGv tmp4 = tcg_temp_new();
        TCGv tmp5 = tcg_temp_new();
        tcg_gen_extu_i32_i64(tmp1, op.add_ctx.arg1);
        tcg_gen_extu_i32_i64(tmp2, op.add_ctx.arg2);
        tcg_gen_extu_i32_i64(tmp3, op.add_ctx.arg3);
        tcg_gen_shli_i64(tmp1, tmp1, 1);
        tcg_gen_shli_i64(tmp2, tmp2, 1);
        tcg_gen_or_i64(tmp1, tmp1, tmp3);
        tcg_gen_or_i64(tmp2, tmp2, tmp3);
        tcg_gen_extrl_i64_i32(tmp4, tmp1);
        tcg_gen_extrl_i64_i32(tmp5, tmp2);
        tcg_gen_add2_tl(tmp4, tmp5, tmp4, zero, tmp5, zero);
        tcg_gen_add_i64(tmp1, tmp1, tmp2);
        tcg_gen_extrh_i64_i32(tmp4, tmp1);
        tcg_gen_shri_tl(tmp4, tmp4, 1);
        tcg_gen_xor_tl(tmp4, tmp4, tmp5);
        tcg_gen_setcondi_tl(TCG_COND_NE, overflow, tmp4, 0);
        tcg_temp_free_i64(tmp1);
        tcg_temp_free_i64(tmp2);
        tcg_temp_free_i64(tmp3);
        tcg_temp_free(tmp4);
        tcg_temp_free(tmp5);

        tcg_temp_free(zero);
    } else if (op.ctx == CTX_SUB) {
        tcg_gen_setcond_tl(TCG_COND_LTU, carry, op.sub_ctx.arg1, op.sub_ctx.arg2);

        TCGv tmp1 = tcg_temp_new();
        TCGv tmp2 = tcg_temp_new();
        TCGv tmp3 = tcg_temp_new();
        tcg_gen_setcondi_tl(TCG_COND_LT, tmp1, op.sub_ctx.arg1, 0);
        tcg_gen_setcondi_tl(TCG_COND_LT, tmp2, op.sub_ctx.arg2, 0);
        tcg_gen_setcondi_tl(TCG_COND_LT, tmp3, arg, 0);
        tcg_gen_xor_tl(tmp1, tmp1, tmp2);
        tcg_gen_setcond_tl(TCG_COND_EQ, tmp2, tmp2, tmp3);
        tcg_gen_and_tl(overflow, tmp1, tmp2);
        tcg_temp_free(tmp1);
        tcg_temp_free(tmp2);
        tcg_temp_free(tmp3);
    }

    unique_condition_code_e condition = cond.value;
    switch (condition) {
    case c_cc:
        switch (op.ctx) {
            default:
                assert(false && "expecting an add/sub to resolve this condition");
                break;
            case CTX_ADD: {
//                TCGv zero = tcg_const_tl(0);
//                TCGv res = tcg_temp_new();
//                TCGv flag_value = tcg_temp_new();
//                tcg_gen_add2_tl(res, flag_value, op.add_ctx.arg1, zero, op.add_ctx.arg2, zero);
//                tcg_gen_add2_tl(res, flag_value, res, flag_value, op.add_ctx.arg3, zero);
//                tcg_gen_brcond_tl(TCG_COND_EQ, flag_value, zero, otherwise);
//                tcg_temp_free(flag_value);
//                tcg_temp_free(res);
//                tcg_temp_free(zero);
//                break;
            }
            case CTX_SUB:
                tcg_gen_brcondi_tl(TCG_COND_EQ, carry, 0, otherwise);
//                tcg_gen_brcond_tl(TCG_COND_GEU, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
                break;
        }
      break;
    case e_cc: {
      TCGv tmp = tcg_temp_new();
      tcg_gen_andi_tl(tmp, arg, 1);
      tcg_gen_brcondi_tl(TCG_COND_NE, tmp, 0, otherwise);
      tcg_temp_free(tmp);
      break;
    }
    case eq_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          tcg_gen_brcondi_tl(TCG_COND_NE, arg, 0, otherwise);
      } else {
          tcg_gen_brcond_tl(TCG_COND_NE, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case false_cc:
      tcg_gen_br(otherwise);
      break;
    case ges_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_GE, tmp, arg, 0);
          tcg_gen_xor_tl(tmp, tmp, overflow);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
      } else {
          tcg_gen_brcond_tl(TCG_COND_LT, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case geu_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          tcg_gen_brcondi_tl(TCG_COND_EQ, carry, 0, otherwise);
      } else {
          tcg_gen_brcond_tl(TCG_COND_LTU, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case gts_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_GE, tmp, arg, 0);
          tcg_gen_xor_tl(tmp, tmp, overflow);
          tcg_gen_setcondi_tl(TCG_COND_NE, tmp2, arg, 0);
          tcg_gen_and_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      } else {
          tcg_gen_brcond_tl(TCG_COND_LE, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case gtu_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_NE, tmp, arg, 0);
          tcg_gen_and_tl(tmp, tmp, carry);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
      } else {
          tcg_gen_brcond_tl(TCG_COND_LEU, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case large_cc:
      assert(op.ctx == CTX_MUL && "expecting a mul to resolve this condition");
      tcg_gen_brcondi_tl(TCG_COND_EQ, op.mul_ctx.arg0, 0, otherwise);
      break;
    case les_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_LT, tmp, arg, 0);
          tcg_gen_xor_tl(tmp, tmp, overflow);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_or_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      } else {
          tcg_gen_brcond_tl(TCG_COND_GT, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case leu_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp, arg, 0);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, carry, 0);
          tcg_gen_or_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      } else {
          tcg_gen_brcond_tl(TCG_COND_GTU, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case lts_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_LT, tmp, arg, 0);
          tcg_gen_xor_tl(tmp, tmp, overflow);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
      } else {
          tcg_gen_brcond_tl(TCG_COND_GE, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case ltu_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          tcg_gen_brcondi_tl(TCG_COND_NE, carry, 0, otherwise);
      } else {
          tcg_gen_brcond_tl(TCG_COND_GEU, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case max_cc:
      assert(op.ctx == CTX_CNT && "expecting a count to resolve this condition");
      tcg_gen_brcondi_tl(TCG_COND_NE, arg, op.cnt_ctx.max_value, otherwise);
      break;
    case mi_cc:
      tcg_gen_brcondi_tl(TCG_COND_GE, arg, 0, otherwise);
      break;
    case nc_cc:
        switch (op.ctx) {
            default:
                assert(false && "expecting an add/sub to resolve this condition");
                break;
            case CTX_ADD: {
//                TCGv zero = tcg_const_tl(0);
//                TCGv res = tcg_temp_new();
//                TCGv flag_value = tcg_temp_new();
//                tcg_gen_add2_tl(res, flag_value, op.add_ctx.arg1, zero, op.add_ctx.arg2, zero);
//                tcg_gen_add2_tl(res, flag_value, res, flag_value, op.add_ctx.arg3, zero);
//                tcg_gen_brcond_tl(TCG_COND_NE, flag_value, zero, otherwise);
//                tcg_temp_free(flag_value);
//                tcg_temp_free(res);
//                tcg_temp_free(zero);
//                break;
            }
            case CTX_SUB:
                tcg_gen_brcondi_tl(TCG_COND_NE, carry, 0, otherwise);
//               tcg_gen_brcond_tl(TCG_COND_LTU, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
                break;
        }
      break;
    case nc10_cc:
      evaluate_ncX_cond(op, otherwise, 10);
      break;
    case nc11_cc:
      evaluate_ncX_cond(op, otherwise, 11);
      break;
    case nc12_cc:
      evaluate_ncX_cond(op, otherwise, 12);
      break;
    case nc13_cc:
      evaluate_ncX_cond(op, otherwise, 13);
      break;
    case nc14_cc:
      evaluate_ncX_cond(op, otherwise, 14);
      break;
    case nc5_cc:
      evaluate_ncX_cond(op, otherwise, 5);
      break;
    case nc6_cc:
      evaluate_ncX_cond(op, otherwise, 6);
      break;
    case nc7_cc:
      evaluate_ncX_cond(op, otherwise, 7);
      break;
    case nc8_cc:
      evaluate_ncX_cond(op, otherwise, 8);
      break;
    case nc9_cc:
      evaluate_ncX_cond(op, otherwise, 9);
      break;
    case neq_cc:
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          tcg_gen_brcondi_tl(TCG_COND_EQ, arg, 0, otherwise);
      } else {
          tcg_gen_brcond_tl(TCG_COND_EQ, op.sub_ctx.arg1, op.sub_ctx.arg2, otherwise);
      }
      break;
    case nmax_cc:
      assert(op.ctx == CTX_CNT && "expecting a count to resolve this condition");
      tcg_gen_brcondi_tl(TCG_COND_EQ, arg, op.cnt_ctx.max_value, otherwise);
      break;
    case nov_cc:
        switch (op.ctx) {
            default:
                assert(false && "expecting an add/sub to resolve this condition");
                break;
            case CTX_ADD: {
//                TCGv_i64 tmp1 = tcg_temp_new_i64();
//                TCGv_i64 tmp2 = tcg_temp_new_i64();
//                TCGv_i64 tmp3 = tcg_temp_new_i64();
//                TCGv tmp4 = tcg_temp_new();
//                TCGv tmp5 = tcg_temp_new();
//                TCGv zero = tcg_const_tl(0);
//                tcg_gen_extu_i32_i64(tmp1, op.add_ctx.arg1);
//                tcg_gen_extu_i32_i64(tmp2, op.add_ctx.arg2);
//                tcg_gen_extu_i32_i64(tmp3, op.add_ctx.arg3);
//                tcg_gen_shli_i64(tmp1, tmp1, 1);
//                tcg_gen_shli_i64(tmp2, tmp2, 1);
//                tcg_gen_or_i64(tmp1, tmp1, tmp3);
//                tcg_gen_or_i64(tmp2, tmp2, tmp3);
//                tcg_gen_extrl_i64_i32(tmp4, tmp1);
//                tcg_gen_extrl_i64_i32(tmp5, tmp2);
//                tcg_gen_add2_tl(tmp4, tmp5, tmp4, zero, tmp5, zero);
//                tcg_gen_add_i64(tmp1, tmp1, tmp2);
//                tcg_gen_extrh_i64_i32(tmp4, tmp1);
//                tcg_gen_shri_tl(tmp4, tmp4, 1);
//                tcg_gen_xor_tl(tmp4, tmp4, tmp5);
//                tcg_gen_brcondi_tl(TCG_COND_NE, tmp4, 0, otherwise);
//                tcg_temp_free_i64(tmp1);
//                tcg_temp_free_i64(tmp2);
//                tcg_temp_free_i64(tmp3);
//                tcg_temp_free(tmp4);
//                tcg_temp_free(tmp5);
//                tcg_temp_free(zero);
//                break;
            }
            case CTX_SUB: {
                tcg_gen_brcondi_tl(TCG_COND_NE, overflow, 0, otherwise);
//                TCGv tmp1 = tcg_temp_new();
//                TCGv tmp2 = tcg_temp_new();
//                TCGv tmp3 = tcg_temp_new();
//                tcg_gen_setcondi_tl(TCG_COND_LT, tmp1, op.sub_ctx.arg1, 0);
//                tcg_gen_setcondi_tl(TCG_COND_LT, tmp2, op.sub_ctx.arg2, 0);
//                tcg_gen_setcondi_tl(TCG_COND_LT, tmp3, arg, 0);
//                tcg_gen_xor_tl(tmp1, tmp1, tmp2);
//                tcg_gen_setcond_tl(TCG_COND_EQ, tmp2, tmp2, tmp3);
//                tcg_gen_and_tl(tmp1, tmp1, tmp2);
//                tcg_gen_brcondi_tl(TCG_COND_NE, tmp1, 0, otherwise);
//                tcg_temp_free(tmp1);
//                tcg_temp_free(tmp2);
//                tcg_temp_free(tmp3);
                break;
            }
        }
        break;
    case nsh32_cc: {
      assert(op.ctx == CTX_SHIFT && "expecting a shift to resolve this condition");
      bool is_reg;
      TCGv_i32 reg;
      uint64_t value;

      if (op.extract_forgot_6th_bit) {
          if (op.extract_src_is_reg) {
              is_reg = true;
              reg = op.extract_src_reg;
          } else {
              is_reg = false;
              value = op.extract_src_value;
          }
      } else {
          if (op.shift_ctx.is_reg) {
              is_reg = true;
              reg = op.shift_ctx.reg_shift;
          } else {
              is_reg = false;
              value = op.shift_ctx.imm_shift;
          }
      }

      if (is_reg) {
          TCGv tmp = tcg_temp_new();
          tcg_gen_andi_tl(tmp, reg, 32);
          tcg_gen_brcondi_tl(TCG_COND_NE, tmp, 0, otherwise);
          tcg_temp_free(tmp);
      } else if ((value & 32) != 0) {
        tcg_gen_br(otherwise);
      }
      break;
    }
    case nz_cc:
      tcg_gen_brcondi_tl(TCG_COND_EQ, arg, 0, otherwise);
      break;
    case o_cc: {
      TCGv tmp = tcg_temp_new();
      tcg_gen_andi_tl(tmp, arg, 1);
      tcg_gen_brcondi_tl(TCG_COND_NE, tmp, 1, otherwise);
      tcg_temp_free(tmp);
      break;
    }
    case ov_cc:
        switch (op.ctx) {
            default:
                assert(false && "expecting an add/sub to resolve this condition");
                break;
            case CTX_ADD: {
//                TCGv_i64 tmp1 = tcg_temp_new_i64();
//                TCGv_i64 tmp2 = tcg_temp_new_i64();
//                TCGv_i64 tmp3 = tcg_temp_new_i64();
//                TCGv tmp4 = tcg_temp_new();
//                TCGv tmp5 = tcg_temp_new();
//                TCGv zero = tcg_const_tl(0);
//                tcg_gen_extu_i32_i64(tmp1, op.add_ctx.arg1);
//                tcg_gen_extu_i32_i64(tmp2, op.add_ctx.arg2);
//                tcg_gen_extu_i32_i64(tmp3, op.add_ctx.arg3);
//                tcg_gen_shli_i64(tmp1, tmp1, 1);
//                tcg_gen_shli_i64(tmp2, tmp2, 1);
//                tcg_gen_or_i64(tmp1, tmp1, tmp3);
//                tcg_gen_or_i64(tmp2, tmp2, tmp3);
//                tcg_gen_extrl_i64_i32(tmp4, tmp1);
//                tcg_gen_extrl_i64_i32(tmp5, tmp2);
//                tcg_gen_add2_tl(tmp4, tmp5, tmp4, zero, tmp5, zero);
//                tcg_gen_add_i64(tmp1, tmp1, tmp2);
//                tcg_gen_extrh_i64_i32(tmp4, tmp1);
//                tcg_gen_shri_tl(tmp4, tmp4, 1);
//                tcg_gen_xor_tl(tmp4, tmp4, tmp5);
//                tcg_gen_brcondi_tl(TCG_COND_EQ, tmp4, 0, otherwise);
//                tcg_temp_free_i64(tmp1);
//                tcg_temp_free_i64(tmp2);
//                tcg_temp_free_i64(tmp3);
//                tcg_temp_free(tmp4);
//                tcg_temp_free(tmp5);
//                tcg_temp_free(zero);
//                break;
            }
            case CTX_SUB: {
                tcg_gen_brcondi_tl(TCG_COND_EQ, overflow, 0, otherwise);
//                TCGv tmp1 = tcg_temp_new();
//                TCGv tmp2 = tcg_temp_new();
//                TCGv tmp3 = tcg_temp_new();
//                tcg_gen_setcondi_tl(TCG_COND_LT, tmp1, op.sub_ctx.arg1, 0);
//                tcg_gen_setcondi_tl(TCG_COND_LT, tmp2, op.sub_ctx.arg2, 0);
//                tcg_gen_setcondi_tl(TCG_COND_LT, tmp3, arg, 0);
//                tcg_gen_xor_tl(tmp1, tmp1, tmp2);
//                tcg_gen_setcond_tl(TCG_COND_EQ, tmp2, tmp2, tmp3);
//                tcg_gen_and_tl(tmp1, tmp1, tmp2);
//                tcg_gen_brcondi_tl(TCG_COND_EQ, tmp1, 0, otherwise);
//                tcg_temp_free(tmp1);
//                tcg_temp_free(tmp2);
//                tcg_temp_free(tmp3);
                break;
            }
        }
        break;
    case pl_cc:
      tcg_gen_brcondi_tl(TCG_COND_LT, arg, 0, otherwise);
      break;
    case se_cc: {
      TCGv tmp = tcg_temp_new();
      tcg_gen_andi_tl(tmp, src_reg, 1);
      tcg_gen_brcondi_tl(TCG_COND_NE, tmp, 0, otherwise);
      tcg_temp_free(tmp);
      break;
    }
    case sh32_cc: {
      assert(op.ctx == CTX_SHIFT && "expecting a shift to resolve this condition");
      bool is_reg;
      TCGv_i32 reg;
      uint64_t value;

      if (op.extract_forgot_6th_bit) {
          if (op.extract_src_is_reg) {
              is_reg = true;
              reg = op.extract_src_reg;
          } else {
              is_reg = false;
              value = op.extract_src_value;
          }
      } else {
          if (op.shift_ctx.is_reg) {
              is_reg = true;
              reg = op.shift_ctx.reg_shift;
          } else {
              is_reg = false;
              value = op.shift_ctx.imm_shift;
          }
      }

      if (is_reg) {
          TCGv tmp = tcg_temp_new();
          tcg_gen_andi_tl(tmp, reg, 32);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
      } else if ((value & 32) == 0) {
        tcg_gen_br(otherwise);
      }
      break;
    }
    case small_cc:
      assert(op.ctx == CTX_MUL && "expecting a mul to resolve this condition");
      tcg_gen_brcondi_tl(TCG_COND_NE, op.mul_ctx.arg0, 0, otherwise);
      break;
    case smi_cc:
      tcg_gen_brcondi_tl(TCG_COND_GE, src_reg, 0, otherwise);
      break;
    case snz_cc:
      tcg_gen_brcondi_tl(TCG_COND_EQ, src_reg, 0, otherwise);
      break;
    case so_cc: {
      TCGv tmp = tcg_temp_new();
      tcg_gen_andi_tl(tmp, src_reg, 1);
      tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
      tcg_temp_free(tmp);
      break;
    }
    case spl_cc:
      tcg_gen_brcondi_tl(TCG_COND_LT, src_reg, 0, otherwise);
      break;
    case sz_cc:
      tcg_gen_brcondi_tl(TCG_COND_NE, src_reg, 0, otherwise);
      break;
    case true_cc:
      break;
    case xgts_cc: {
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_GE, tmp, arg, 0);
          tcg_gen_xor_tl(tmp, tmp, overflow);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_and_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_not_tl(tmp2, tmp2);
          tcg_gen_and_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      } else {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcond_tl(TCG_COND_GE, tmp, op.sub_ctx.arg1, op.sub_ctx.arg2);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_nand_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_and_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      }
      break;
    }
    case xgtu_cc: {
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp, arg, 0);
          tcg_gen_and_tl(tmp, tmp, cpu_zf);
          tcg_gen_not_tl(tmp, tmp);
          tcg_gen_and_tl(tmp, tmp, carry);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
      } else {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcond_tl(TCG_COND_GEU, tmp, op.sub_ctx.arg1, op.sub_ctx.arg2);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_nand_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_and_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      }
      break;
    }
    case xles_cc: {
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_LT, tmp, arg, 0);
          tcg_gen_xor_tl(tmp, tmp, overflow);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_and_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_or_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      } else {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcond_tl(TCG_COND_LT, tmp, op.sub_ctx.arg1, op.sub_ctx.arg2);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_and_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_or_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      }
      break;
    }
    case xleu_cc: {
      assert(((op.ctx == CTX_ADD) || (op.ctx == CTX_SUB)) && "expecting an add/sub to resolve this condition");
      if (op.ctx == CTX_ADD) {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp, carry, 0);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_and_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_or_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      } else {
          TCGv tmp = tcg_temp_new();
          TCGv tmp2 = tcg_temp_new();
          tcg_gen_setcond_tl(TCG_COND_LTU, tmp, op.sub_ctx.arg1, op.sub_ctx.arg2);
          tcg_gen_setcondi_tl(TCG_COND_EQ, tmp2, arg, 0);
          tcg_gen_and_tl(tmp2, tmp2, cpu_zf);
          tcg_gen_or_tl(tmp, tmp, tmp2);
          tcg_gen_brcondi_tl(TCG_COND_EQ, tmp, 0, otherwise);
          tcg_temp_free(tmp);
          tcg_temp_free(tmp2);
      }
      break;
    }
    case xnz_cc: {
      TCGv tmp = tcg_temp_new();
      tcg_gen_setcondi_tl(TCG_COND_EQ, tmp, arg, 0);
      tcg_gen_and_tl(tmp, tmp, cpu_zf);
      tcg_gen_brcondi_tl(TCG_COND_NE, tmp, 0, otherwise);
      tcg_temp_free(tmp);
      break;
    }
    case xz_cc:
      tcg_gen_brcondi_tl(TCG_COND_NE, arg, 0, otherwise);
      tcg_gen_brcondi_tl(TCG_COND_NE, cpu_zf, 1, otherwise);
      break;
    case z_cc:
      tcg_gen_brcondi_tl(TCG_COND_NE, arg, 0, otherwise);
      break;
    }

    tcg_temp_free(carry);
    tcg_temp_free(overflow);
    free_if_value(op, arg);
    free_if_value(src_reg_op, src_reg);
}

#define evaluate_condition(cond, op, label) _evaluate_condition(ctx, cond, op, label, src_reg)

// LABELS

static inline void _label_new(operand_t *dst) {
    dst->kind = OP_KIND_LABEL;
    dst->label = gen_new_label();
}

static inline void _label_set(operand_t op) {
    assert_label(op);
    gen_set_label(op.label);
}

static inline void _label_jump(operand_t op) {
    assert_label(op);
    tcg_gen_br(op.label);
}

#define label_new(dst) _label_new(dst)
#define label_set(op) _label_set(op)
#define label_jump(op) _label_jump(op)

// JUMP & CALL

static inline uint32_t insn_to_byte_address(uint32_t pc) {
    return IRAM_ADDR_OFFSET + (pc << 3);
}

static inline uint32_t byte_to_insn_address(uint32_t offset) {
    return (offset - IRAM_ADDR_OFFSET) >> 3;
}

static inline void _cond_jump(DisasContext *ctx, operand_t cc, operand_t op, operand_t target, operand_t src_reg) {
    assert_val(target);
    operand_t otherwise, end;
    _label_new(&otherwise);
    _label_new(&end);

    _evaluate_condition(ctx, cc, op, otherwise, src_reg);
    tcg_gen_movi_tl(cpu_pc, insn_to_byte_address(target.value % (ctx->iram_size >> 3)));
    _label_jump(end);
    _label_set(otherwise);
    target_ulong next = ctx->base.pc_next + 8;
    if (next == (IRAM_ADDR_OFFSET + ctx->iram_size)) {
        next = IRAM_ADDR_OFFSET;
    }
    tcg_gen_movi_tl(cpu_pc, next);
    _label_set(end);

    ctx->base.is_jmp = DISAS_JUMP;
}

static inline void _call(operand_t *dst, DisasContext *ctx, operand_t op) {
    assert_reg32(op);
    init_reg32(dst);

    target_ulong next = ctx->base.pc_next + 8;
    if (next == (IRAM_ADDR_OFFSET + ctx->iram_size)) {
        next = IRAM_ADDR_OFFSET;
    }
    tcg_gen_movi_tl(dst->reg, byte_to_insn_address(next));
    tcg_gen_andi_tl(cpu_pc, op.reg, (ctx->iram_size >> 3) - 1);
    tcg_gen_shli_tl(cpu_pc, cpu_pc, 3);
    tcg_gen_ori_tl(cpu_pc, cpu_pc, IRAM_ADDR_OFFSET);
    ctx->base.is_jmp = DISAS_JUMP;
}

#define cond_jump(cc, op, target) _cond_jump(ctx, cc, op, target, src_reg)
#define call(op, dst) _call(dst, ctx, op)

// THREAD OPERATIONS

static inline void _boot(operand_t *dst, DisasContext *ctx, operand_t op) {
    init_reg32(dst);
    assert_reg32(op);

    TCGv one = tcg_const_tl(1);
    gen_helper_start_thread(dst->reg, cpu_env, op.reg, one);
    tcg_temp_free(one);
}

static inline void _resume(operand_t *dst, DisasContext *ctx, operand_t op) {
    init_reg32(dst);
    assert_reg32(op);

    TCGv zero = tcg_const_tl(0);
    gen_helper_start_thread(dst->reg, cpu_env, op.reg, zero);
    tcg_temp_free(zero);
}

static inline void _read_run(operand_t *dst, DisasContext *ctx, operand_t op) {
    init_reg32(dst);
    assert_reg32(op);

    gen_helper_read_thread(dst->reg, cpu_env, op.reg);
}

static inline void _clear_run(operand_t *dst, DisasContext *ctx, operand_t op) {
    init_reg32(dst);
    assert_reg32(op);

    gen_helper_clear_thread(dst->reg, cpu_env, op.reg);
}

static inline void _stop(operand_t *dst, DisasContext *ctx) {
    init_reg32(dst);
    tcg_gen_movi_tl(dst->reg, 1);
    gen_helper_stop(cpu_env);
}

#define boot(op, dst) _boot(dst, ctx, op)
#define resume(op, dst) _resume(dst, ctx, op)
#define read_run(op, dst) _read_run(dst, ctx, op)
#define clear_run(op, dst) _clear_run(dst, ctx, op)
#define stop(dst) _stop(dst, ctx)

// FAULT

void gen_fault(DisasContext *ctx, uint32_t id) {
    tcg_gen_movi_tl(cpu_pc, ctx->base.pc_next);
    TCGv_i32 tmp = tcg_const_i32(id);
    gen_helper_raise_exception(cpu_env, tmp);
    tcg_temp_free_i32(tmp);
}

static inline void _fault(DisasContext *ctx) {
    gen_fault(ctx, FAULT_ID_BKP);
}

static inline void _raise_memory_fault(DisasContext *ctx, operand_t *dst) {
    if (dst != NULL) {
        TCGv_i32 tmp = tcg_temp_new();
        assert_reg32(*dst);
        tcg_gen_andi_tl(dst->reg, dst->reg, 0x00FFFFFF);
        tcg_gen_shli_tl(tmp, cpu_tid, 25);
        tcg_gen_or_tl(dst->reg, dst->reg, tmp);
        tcg_temp_free(tmp);
    }

    gen_fault(ctx, FAULT_ID_MEM);
}

#define fault() _fault(ctx)
#define raise_memory_fault() _raise_memory_fault(ctx, NULL)
#define raise_memory_fault_with(dst) _raise_memory_fault(ctx, dst)

// WRAM OPERATIONS

static inline void _load(operand_t *dst, DisasContext *ctx, operand_t address, operand_t endianness, uint32_t length) {
    assert_reg32(address);
    assert_val(endianness);

    TCGv provided_addr = tcg_temp_local_new();
    TCGv valid_addr = tcg_temp_local_new();
    tcg_gen_mov_tl(provided_addr, address.reg);
    tcg_gen_andi_tl(valid_addr, address.reg, (ctx->wram_size - 1) & ~((length >> 3) - 1));

    switch (length) {
        case 8:
            init_reg32(dst);
            tcg_gen_qemu_ld8u(dst->reg, valid_addr, 0);
            break;
        case 16:
            init_reg32(dst);
            tcg_gen_qemu_ld16u(dst->reg, valid_addr, 0);
            if (endianness.value == 1) {
                tcg_gen_bswap16_tl(dst->reg, dst->reg);
            }
            break;
        case 32:
            init_reg32(dst);
            tcg_gen_qemu_ld32u(dst->reg, valid_addr, 0);
            if (endianness.value == 1) {
                tcg_gen_bswap32_tl(dst->reg, dst->reg);
            }
            break;
        case 64:
            init_reg64(dst);
            tcg_gen_qemu_ld64(dst->dreg, valid_addr, 0);
            if (endianness.value == 1) {
                tcg_gen_bswap64_i64(dst->dreg, dst->dreg);
            }
            break;
    }

    ctx->gen_mem_fault_check = true;
    ctx->expected = provided_addr;
    ctx->used = valid_addr;
}

static inline void _store(DisasContext *ctx, operand_t address, operand_t value, operand_t endianness, uint32_t length) {
    assert_reg32(address);
    assert_val(endianness);

    TCGv valid_addr = tcg_temp_new();
    tcg_gen_andi_tl(valid_addr, address.reg, (ctx->wram_size - 1) & ~((length >> 3) - 1));

    switch (length) {
        case 8: {
            TCGv val = promote_value(value);
            tcg_gen_qemu_st8(val, valid_addr, 0);
            free_if_value(value, val);
            break;
        }
        case 16: {
            TCGv val = promote_value(value);
            if (endianness.value == 1) {
                TCGv tmp = tcg_temp_new();
                tcg_gen_bswap16_tl(tmp, val);
                tcg_gen_qemu_st16(tmp, valid_addr, 0);
                tcg_temp_free(tmp);
            } else {
                tcg_gen_qemu_st16(val, valid_addr, 0);
            }
            free_if_value(value, val);
            break;
        }
        case 32: {
            TCGv val = promote_value(value);
            if (endianness.value == 1) {
                TCGv tmp = tcg_temp_new();
                tcg_gen_bswap32_tl(tmp, val);
                tcg_gen_qemu_st32(tmp, valid_addr, 0);
                tcg_temp_free(tmp);
            } else {
                tcg_gen_qemu_st32(val, valid_addr, 0);
            }
            free_if_value(value, val);
            break;
        }
        case 64: {
            TCGv_i64 val = promote_value64(value);
            if (endianness.value == 1) {
                TCGv_i64 tmp = tcg_temp_new_i64();
                tcg_gen_bswap64_i64(tmp, val);
                tcg_gen_qemu_st64(tmp, valid_addr, 0);
                tcg_temp_free_i64(tmp);
            } else {
                tcg_gen_qemu_st64(val, valid_addr, 0);
            }
            free_if_value64(value, val);
            break;
        }
    }

    operand_t exit_label;
    label_new(&exit_label);
    tcg_gen_brcond_tl(TCG_COND_EQ, address.reg, valid_addr, exit_label.label);
    gen_fault(ctx, FAULT_ID_MEM);
    label_set(exit_label);
    tcg_temp_free(valid_addr);
}

#define load_8(op1, op2, dst) _load(dst, ctx, op1, op2, 8)
#define load_16(op1, op2, dst) _load(dst, ctx, op1, op2, 16)
#define load_32(op1, op2, dst) _load(dst, ctx, op1, op2, 32)
#define load_64(op1, op2, dst) _load(dst, ctx, op1, op2, 64)
#define store_8(op1, op2, op3) _store(ctx, op1, op2, op3, 8)
#define store_16(op1, op2, op3) _store(ctx, op1, op2, op3, 16)
#define store_32(op1, op2, op3) _store(ctx, op1, op2, op3, 32)
#define store_64(op1, op2, op3) _store(ctx, op1, op2, op3, 64)

// MRAM OPERATIONS

typedef enum {
    DPU_XRAM_IRAM,
    DPU_XRAM_WRAM,
} dpu_xram_t;

static inline void _mram_read(DisasContext *ctx, operand_t from, operand_t to, operand_t length, dpu_xram_t memory) {
    assert_reg32(from);
    assert_reg32(to);
    assert_reg32(length);

    if (memory == DPU_XRAM_IRAM) {
        gen_helper_ldmai_transfer(cpu_env, to.reg, from.reg, length.reg);
    } else {
        gen_helper_ldma_transfer(cpu_env, to.reg, from.reg, length.reg);
    }
}

static inline void _mram_write(DisasContext *ctx, operand_t from, operand_t to, operand_t length, dpu_xram_t memory) {
    assert_reg32(from);
    assert_reg32(to);
    assert_reg32(length);
    assert((memory == DPU_XRAM_WRAM) && "cannot write MRAM from IRAM");

    gen_helper_sdma_transfer(cpu_env, to.reg, from.reg, length.reg);
}

#define mram_read_to_wram_XXX(op1, op2, op3) _mram_read(ctx, op2, op3, op1, DPU_XRAM_WRAM)
#define mram_read_to_iram_XXX(op1, op2, op3) _mram_read(ctx, op2, op3, op1, DPU_XRAM_IRAM)
#define mram_write_from_wram_XXX(op1, op2, op3) _mram_write(ctx, op2, op3, op1, DPU_XRAM_WRAM)

// TIME

static inline void _time(operand_t *dst, DisasContext *ctx) {
    init_reg64(dst);

    TCGv addend = tcg_const_local_tl(ctx->base.num_insns - 1);
    gen_io_start();
    gen_helper_time(dst->dreg, cpu_env, addend);
    gen_io_end();
    tcg_temp_free(addend);
}

static inline void _time_cfg(DisasContext *ctx, operand_t op) {
    assert_reg32(op);

    TCGv addend = tcg_const_local_tl(ctx->base.num_insns - 1);
    gen_io_start();
    gen_helper_time_cfg(cpu_env, op.reg, addend);
    gen_io_end();
    tcg_temp_free(addend);
}

#define get_time(dst) _time(dst, ctx)
#define set_time_config(op) _time_cfg(ctx, op)

// TELL

static inline void _tell(operand_t *dst, operand_t op1, operand_t op2) {
    (void) dst;
    assert_reg32(op1);
    TCGv tmp = promote_value(op2);

    gen_helper_tell(cpu_env, op1.reg, tmp);
    free_if_value(op2, tmp);
}

#define tell(op1, op2, dst) _tell(dst, op1, op2)

#endif /* DPU_TRANSLATE_DEFS_H */
