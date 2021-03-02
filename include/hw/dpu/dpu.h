#ifndef HW_DPU_H
#define HW_DPU_H

#include "hw/sysbus.h"
#include "qemu/typedefs.h"
#include <stdint.h>

#define TYPE_DPU "dpu"
#define DPU(obj) \
    OBJECT_CHECK(DpuState, (obj), TYPE_DPU)

#define NR_THREADS (24)
#define NR_WORK_REGISTERS (24)
#define NR_NOTIFY_BITS (40)

#define DEFAULT_IRAM_SIZE (8 << 12)
#define DEFAULT_WRAM_SIZE (1 << 16)
#define DEFAULT_MRAM_SIZE (1 << 26)
#define ATOMIC_SIZE (1 << 8)
#define RUN_BITS_SIZE (NR_THREADS + NR_NOTIFY_BITS)

#define WRAM_ADDR_OFFSET (0x00000000)
#define IRAM_ADDR_OFFSET (0x80000000)
#define MRAM_ADDR_OFFSET (0x08000000)
#define ATOMIC_ADDR_OFFSET (0xF0000000)
#define RUN_BITS_ADDR_OFFSET (ATOMIC_ADDR_OFFSET + ATOMIC_SIZE)

typedef struct DpuThreadState DpuThreadState;
typedef struct DpuState DpuState;

struct DpuThreadState {
    uint32_t thread_idx;
    uint32_t regs[NR_WORK_REGISTERS];
    uint32_t pc;
    uint32_t cf;
    uint32_t zf;

    DpuState *dpu;
};

struct PerfCounter {
    bool enabled;
    uint64_t start;
    uint64_t duration;
};

struct DpuDesc {
    uint32_t iram_size;
    uint32_t mram_size;
    uint32_t wram_size;
};

typedef struct DpuThreadCPU {
    CPUState parent_obj;

    CPUNegativeOffsetState neg;
    DpuThreadState env;
} DpuThreadCPU;

typedef struct DpuThreadCPUClass {
    CPUClass parent_class;

    DeviceRealize parent_realize;
    DeviceReset parent_reset;
} DpuThreadCPUClass;

struct DpuState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    HostMemoryBackend *hostmem;
    void *iram;
    void *mram;
    void *wram;

    DpuThreadCPU threads[NR_THREADS];
    uint8_t run_bits[RUN_BITS_SIZE];
    uint8_t atomic_bits[ATOMIC_SIZE];
    uint32_t fault;

    bool step_enabled;
    uint8_t step_thread;

    uint8_t bkp_thread;
    uint8_t dma_thread;
    uint8_t mem_thread;

    struct DpuDesc desc;
    struct PerfCounter perfcounter;

    QemuMutex state_lock;
    QemuMutex mram_lock;
};

typedef struct DpuSystemState {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    DpuState dpu;
} DpuSystemState;

#endif
