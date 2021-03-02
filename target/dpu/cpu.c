#include "qemu/osdep.h"
#include "qemu/typedefs.h"
#include "tcg/tcg-op.h"
#include "exec/cpu-all.h"
#include "exec/exec-all.h"
#include "exec/translator.h"
#include "exec/log.h"
#include "qapi/error.h"
#include "hw/qdev-properties.h"

#include "cpu.h"
#include "ctxt.h"
#include "decode.h"

int dpu_cpu_mmu_index(DpuThreadState *env, bool ifetch) {
    return 0;
}

static void dpu_tr_init_disas_context(DisasContextBase *dcbase, CPUState *cs) {

}

static void dpu_tr_tb_start(DisasContextBase *db, CPUState *cpu)
{
}

static void dpu_tr_insn_start(DisasContextBase *dcbase, CPUState *cpu)
{
    DisasContext *ctx = container_of(dcbase, DisasContext, base);

    tcg_gen_insn_start(ctx->base.pc_next);
}

static bool dpu_tr_breakpoint_check(DisasContextBase *dcbase, CPUState *cpu, const CPUBreakpoint *bp) {
    // TODO
    return true;
}

static void gen_mem_fault_check(DisasContext *ctx, TCGv expected, TCGv used) {
    TCGLabel *exit = gen_new_label();
    tcg_gen_brcond_tl(TCG_COND_EQ, expected, used, exit);
    gen_fault(ctx, FAULT_ID_MEM);
    gen_set_label(exit);
    tcg_temp_free(expected);
    tcg_temp_free(used);
}

static void dpu_tr_translate_insn(DisasContextBase *dcbase, CPUState *cpu) {
    DisasContext *ctx = container_of(dcbase, DisasContext, base);
    DpuThreadState *env = cpu->env_ptr;
    uint64_t instruction = translator_ldq(env, ctx->base.pc_next);
    ctx->gen_mem_fault_check = false;
    decode_instruction(ctx, instruction);
    if (ctx->gen_mem_fault_check) {
        gen_mem_fault_check(ctx, ctx->expected, ctx->used);
    }

    ctx->base.pc_next += sizeof(instruction);
    if (ctx->base.pc_next == (IRAM_ADDR_OFFSET + env->dpu->desc.iram_size)) {
        ctx->base.pc_next = IRAM_ADDR_OFFSET;
    }
}

static void dpu_tr_tb_stop(DisasContextBase *dcbase, CPUState *cpu) {
    DisasContext *ctx = container_of(dcbase, DisasContext, base);

    // TODO singlestepping

    switch (ctx->base.is_jmp) {
        case DISAS_TOO_MANY:
            gen_goto_tb(ctx->base.tb, 0, ctx->base.pc_next);
            break;
        case DISAS_NORETURN:
            break;
        case DISAS_JUMP:
            tcg_gen_exit_tb(NULL, 0);
            break;
        default:
            g_assert_not_reached();
    }
}

static void dpu_tr_disas_log(const DisasContextBase *dcbase, CPUState *cpu) {
    qemu_log("IN: %s\n", lookup_symbol(dcbase->pc_first));
    log_target_disas(cpu, dcbase->pc_first, dcbase->tb->size);
}

static const TranslatorOps dpu_tr_ops = {
    .init_disas_context = dpu_tr_init_disas_context,
    .tb_start           = dpu_tr_tb_start,
    .insn_start         = dpu_tr_insn_start,
    .breakpoint_check   = dpu_tr_breakpoint_check,
    .translate_insn     = dpu_tr_translate_insn,
    .tb_stop            = dpu_tr_tb_stop,
    .disas_log          = dpu_tr_disas_log,
};

void gen_intermediate_code(CPUState *cpu, TranslationBlock *tb, int max_insns) {
    DisasContext dc;
    dc.iram_size = DPU_CPU(cpu)->env.dpu->desc.iram_size;
    dc.wram_size = DPU_CPU(cpu)->env.dpu->desc.wram_size;

    translator_loop(&dpu_tr_ops, &dc.base, cpu, tb, max_insns);
}

static void dpu_cpu_dump_state(CPUState *cs, FILE *f, int flags) {
    // TODO
}

static void dpu_cpu_set_pc(CPUState *cs, vaddr value) {
    DpuThreadCPU *cpu = DPU_CPU(cs);
    DpuThreadState *env = &cpu->env;
    env->pc = value;
}

static void dpu_cpu_synchronize_from_tb(CPUState *cs, TranslationBlock *tb) {
    dpu_cpu_set_pc(cs, tb->pc);
}

static bool dpu_cpu_has_work(CPUState *cs) {
    DpuThreadCPU *cpu = DPU_CPU(cs);
    DpuThreadState *env = &cpu->env;

    uint8_t run = env->dpu->run_bits[env->thread_idx];
    bool fault = env->dpu->fault != 0;

    return (run != 0) && !fault && (!env->dpu->step_enabled || (env->dpu->step_thread == env->thread_idx));
}

void restore_state_to_opc(DpuThreadState *env, TranslationBlock *tb, target_ulong *data) {
    env->pc = data[0];
}

static void dpu_cpu_reset(DeviceState *dev) {
    CPUState *cs = CPU(dev);
    DpuThreadCPU *cpu = DPU_CPU(cs);
    DpuThreadCPUClass *mcc = DPU_CPU_GET_CLASS(cpu);
    DpuThreadState *env = &cpu->env;

    mcc->parent_reset(dev);

    env->pc = IRAM_ADDR_OFFSET;
    env->dpu->run_bits[env->thread_idx] = 0;
    env->dpu->fault = 0;
    cs->halted = true;
}

static void dpu_cpu_realize(DeviceState *dev, Error **errp) {
    CPUState *cs = CPU(dev);
    DpuThreadCPU *cpu = DPU_CPU(cs);
    DpuThreadCPUClass *mcc = DPU_CPU_GET_CLASS(cpu);

    Error *local_err = NULL;

    cpu_exec_realizefn(cs, &local_err);
    if (local_err != NULL) {
        error_propagate(errp, local_err);
        return;
    }

    qemu_init_vcpu(cs);
    cpu_reset(cs);

    mcc->parent_realize(dev, errp);
}

static void dpu_cpu_init(Object *obj) {
    DpuThreadCPU *cpu = DPU_CPU(obj);

    cpu_set_cpustate_pointers(cpu);
}

static Property dpu_cpu_properties[] = {
    DEFINE_PROP_END_OF_LIST(),
};

static hwaddr dpu_get_phys_page(vaddr addr) {
    return addr & TARGET_PAGE_MASK;
}

static hwaddr dpu_get_phys_page_debug(CPUState *cs, vaddr addr) {
    return dpu_get_phys_page(addr);
}

static bool dpu_tlb_fill(CPUState *cs, vaddr address, int size, MMUAccessType access_type, int mmu_idx, bool probe, uintptr_t retaddr) {
    DpuThreadCPU *cpu = DPU_CPU(cs);
    int prot = PAGE_READ | PAGE_WRITE;
    address = dpu_get_phys_page(address);

    if ((address >= IRAM_ADDR_OFFSET) && (address < (IRAM_ADDR_OFFSET + cpu->env.dpu->desc.iram_size))) {
        prot |= PAGE_EXEC;
    }

    tlb_set_page(cs, address, address, prot, mmu_idx, TARGET_PAGE_SIZE);

    return true;
}

static void dpu_cpu_do_unaligned_access(CPUState *cs, vaddr addr, MMUAccessType access_type, int mmu_idx, uintptr_t retaddr) {
    DpuThreadCPU *cpu = DPU_CPU(cs);
    helper_raise_exception(&cpu->env, FAULT_ID_MEM);
}

static void dpu_cpu_class_init(ObjectClass *c, void *data) {
    DpuThreadCPUClass *mcc = DPU_CPU_CLASS(c);
    CPUClass *cc = CPU_CLASS(c);
    DeviceClass *dc = DEVICE_CLASS(c);

    device_class_set_parent_realize(dc, dpu_cpu_realize, &mcc->parent_realize);

    device_class_set_parent_reset(dc, dpu_cpu_reset, &mcc->parent_reset);

    device_class_set_props(dc, dpu_cpu_properties);

    cc->has_work = dpu_cpu_has_work;
    cc->dump_state = dpu_cpu_dump_state;
    cc->set_pc = dpu_cpu_set_pc;
    cc->synchronize_from_tb = dpu_cpu_synchronize_from_tb;
    cc->do_unaligned_access = dpu_cpu_do_unaligned_access;

    // TODO
    // cc->disas_set_info = dpu_cpu_disas_set_info;

    cc->get_phys_page_debug = dpu_get_phys_page_debug;
#ifdef CONFIG_TCG
    cc->tcg_initialize = dpu_translate_init;
    cc->tlb_fill = dpu_tlb_fill;
#endif
}

static const TypeInfo dpu_cpu_type_infos[] = {
    {
        .name = TYPE_DPU_CPU,
        .parent = TYPE_CPU,
        .instance_size = sizeof(DpuThreadCPU),
        .instance_init = dpu_cpu_init,
        .class_size = sizeof(DpuThreadCPUClass),
        .class_init = dpu_cpu_class_init,
    }
};

DEFINE_TYPES(dpu_cpu_type_infos);
