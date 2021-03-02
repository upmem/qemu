#ifndef DPU_CPU_H
#define DPU_CPU_H

#include "hw/core/cpu.h"
#include "exec/cpu-defs.h"
#include "exec/tb-context.h"
#include "hw/dpu/dpu.h"
#include <stdint.h>

#define TYPE_DPU_CPU "dpu-thread-cpu"

#define CPU_RESOLVING_TYPE TYPE_DPU_CPU

#define FAULT_ID_BKP 1
#define FAULT_ID_MEM 2
#define FAULT_ID_DMA 3

#define DPU_CPU_CLASS(klass) \
    OBJECT_CLASS_CHECK(DpuThreadCPUClass, (klass), TYPE_DPU_CPU)
#define DPU_CPU(obj) \
    OBJECT_CHECK(DpuThreadCPU, (obj), TYPE_DPU_CPU)
#define DPU_CPU_GET_CLASS(obj) \
    OBJECT_GET_CLASS(DpuThreadCPUClass, (obj), TYPE_DPU_CPU)

int dpu_cpu_mmu_index(DpuThreadState *env, bool ifetch);
#define cpu_mmu_index dpu_cpu_mmu_index

static inline void cpu_get_tb_cpu_state(DpuThreadState *env, target_ulong *pc, target_ulong *cs_base, uint32_t *flags) {
    *pc = env->pc;
    *cs_base = 0;
    *flags = 0;
}

void dpu_translate_init(void);
void gen_goto_tb(TranslationBlock *tb, int n, target_ulong dest);

typedef DpuThreadState CPUArchState;
typedef DpuThreadCPU ArchCPU;

#include "exec/cpu-all.h"

typedef enum {
    DPU_REG_R0,
    DPU_REG_R1,
    DPU_REG_R2,
    DPU_REG_R3,
    DPU_REG_R4,
    DPU_REG_R5,
    DPU_REG_R6,
    DPU_REG_R7,
    DPU_REG_R8,
    DPU_REG_R9,
    DPU_REG_R10,
    DPU_REG_R11,
    DPU_REG_R12,
    DPU_REG_R13,
    DPU_REG_R14,
    DPU_REG_R15,
    DPU_REG_R16,
    DPU_REG_R17,
    DPU_REG_R18,
    DPU_REG_R19,
    DPU_REG_R20,
    DPU_REG_R21,
    DPU_REG_R22,
    DPU_REG_R23,
    DPU_REG_ZERO,
    DPU_REG_ONE,
    DPU_REG_LNEG,
    DPU_REG_MNEG,
    DPU_REG_ID,
    DPU_REG_ID2,
    DPU_REG_ID4,
    DPU_REG_ID8,
} DPUReg;

#define DISAS_JUMP DISAS_TARGET_0

#endif /* DPU_CPU_H */
