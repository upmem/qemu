#include "qemu/osdep.h"

#include "qemu/main-loop.h"
#include "qemu/typedefs.h"
#include "exec/cpu-defs.h"
#include "exec/exec-all.h"
#include "exec/helper-proto.h"

#include "cpu.h"
#include "tcg/tcg.h"

static uint64_t get_global_time_count(void);

void helper_stop(DpuThreadState *env) {
    CPUState *cs = env_cpu(env);

    cs->halted = 1;
    cs->exception_index = EXCP_HALTED;
    env->dpu->run_bits[env->thread_idx] = 0;
    cpu_loop_exit(cs);
}

void helper_raise_exception(DpuThreadState *env, uint32_t id) {
    CPUState *cs = env_cpu(env);

    target_ulong *pc = &(env->pc);

    *pc += 8;
    if (*pc == (IRAM_ADDR_OFFSET + env->dpu->desc.iram_size)) {
        *pc = IRAM_ADDR_OFFSET;
    }
    cs->halted = 1;
    cs->exception_index = EXCP_HLT;

    switch (id) {
        default:
            break;
        case FAULT_ID_BKP:
            env->dpu->bkp_thread = env->thread_idx;
            break;
        case FAULT_ID_DMA:
            env->dpu->dma_thread = env->thread_idx;
            break;
        case FAULT_ID_MEM:
            env->dpu->mem_thread = env->thread_idx;
            break;
    }

    env->dpu->fault = 1;
    cpu_loop_exit(cs);
}

target_ulong helper_read_thread(DpuThreadState *env, target_ulong id) {
    DpuState *dpu = env->dpu;

    qemu_mutex_lock(&dpu->state_lock);
    target_ulong res = dpu->run_bits[id];
    qemu_mutex_unlock(&dpu->state_lock);

    return res;
}

target_ulong helper_clear_thread(DpuThreadState *env, target_ulong id) {
    DpuState *dpu = env->dpu;

    qemu_mutex_lock(&dpu->state_lock);
    target_ulong res = dpu->run_bits[id];
    dpu->run_bits[id] = 0;
    qemu_mutex_unlock(&dpu->state_lock);

    return res;
}

target_ulong helper_start_thread(DpuThreadState *env, target_ulong id, uint32_t reset_pc) {
    DpuState *dpu = env->dpu;

    qemu_mutex_lock(&dpu->state_lock);
    target_ulong res = dpu->run_bits[id];
    dpu->run_bits[id] = 1;

    if ((res == 0) && (id < NR_THREADS)) {
        if (reset_pc != 0) {
            dpu->threads[id].env.pc = IRAM_ADDR_OFFSET;
        }
        cpu_resume(CPU(&dpu->threads[id]));
    }
    qemu_mutex_unlock(&dpu->state_lock);

    return res;
}

void helper_tell(DpuThreadState *env, target_ulong reg_value, uint32_t imm) {
    uint8_t thread = env->thread_idx;
    target_ulong pc = env->pc;
    // TODO add current time
    qemu_log_mask(CPU_LOG_EXEC, "TELL: thread=%02d @PC=0x%04x - imm=0x%08x rX=0x"TARGET_FMT_lx"\n",
            thread, pc, imm, reg_value);
}

static uint64_t get_global_time_count(void) {
    return cpu_get_icount_raw();
}

uint64_t helper_time(DpuThreadState *env, uint32_t insn_addend) {
    DpuState *dpu = env->dpu;
    uint64_t duration = dpu->perfcounter.duration;

    if (dpu->perfcounter.enabled) {
        uint64_t start = dpu->perfcounter.start;
//        uint64_t current = get_global_time_count() + insn_addend;
        uint64_t current = get_global_time_count();
        duration += current - start;
    }

    printf("JORDI %ld %ld %d\n", duration, get_global_time_count(), insn_addend);
    return duration;
}

void helper_time_cfg(DpuThreadState *env, target_ulong config, uint32_t insn_addend) {
    DpuState *dpu = env->dpu;
    bool reset = config & 1;
    config >>= 1;

//    uint64_t current = get_global_time_count() + insn_addend + 1;
    uint64_t current = get_global_time_count();
    if (config != 0) {
        bool enable = config != 3;

        if (enable && !dpu->perfcounter.enabled) {
            dpu->perfcounter.start = current;
        } else if (!enable && dpu->perfcounter.enabled) {
            uint64_t start = dpu->perfcounter.start;
            dpu->perfcounter.duration += current - start;
        }

        dpu->perfcounter.enabled = enable;
    }

    if (reset) {
        printf("JORDI cfg %ld %ld %d\n", current, get_global_time_count(), insn_addend);
        dpu->perfcounter.duration = 0;
        dpu->perfcounter.start = current;

    }
}

static void check_transfer_bound(DpuThreadState *env, uint32_t fault, uint32_t bound, uint32_t offset, uint32_t length) {
    if ((offset >= bound) || ((offset + length) > bound)) {
        helper_raise_exception(env, fault);
    }
}

static void dma_transfer(QemuMutex *dma_lock, void *dst, const void *src, size_t length) {
    qemu_mutex_lock(dma_lock);
    memcpy(dst, src, length);
    qemu_mutex_unlock(dma_lock);
}

void helper_ldma_transfer(DpuThreadState *env, target_ulong dst, target_ulong from, target_ulong length) {
    check_transfer_bound(env, FAULT_ID_MEM, env->dpu->desc.wram_size, dst, length);
    check_transfer_bound(env, FAULT_ID_DMA, env->dpu->desc.mram_size, from, length);
    dma_transfer(&env->dpu->mram_lock, env->dpu->wram + dst, env->dpu->mram + from, length);
}

void helper_ldmai_transfer(DpuThreadState *env, target_ulong dst, target_ulong from, target_ulong length) {
    check_transfer_bound(env, FAULT_ID_MEM, env->dpu->desc.iram_size, dst, length);
    check_transfer_bound(env, FAULT_ID_DMA, env->dpu->desc.mram_size, from, length);
    dma_transfer(&env->dpu->mram_lock, env->dpu->iram + dst, env->dpu->mram + from, length);
}

void helper_sdma_transfer(DpuThreadState *env, target_ulong dst, target_ulong from, target_ulong length) {
    check_transfer_bound(env, FAULT_ID_DMA, env->dpu->desc.mram_size, dst, length);
    check_transfer_bound(env, FAULT_ID_MEM, env->dpu->desc.wram_size, from, length);
    dma_transfer(&env->dpu->mram_lock, env->dpu->mram + dst, env->dpu->wram + from, length);
}
