#include "qemu/osdep.h"
#include "qapi/error.h"
#include "hw/sysbus.h"
#include "hw/boards.h"
#include "hw/core/cpu.h"
#include "hw/loader.h"
#include "hw/qdev-core.h"
#include "hw/qdev-properties.h"
#include "exec/address-spaces.h"
#include "exec/exec-all.h"
#include "exec/memory.h"
#include "cpu.h"
#include "elf.h"
#include "migration/vmstate.h"
#include "qapi/error.h"
#include "qapi/qapi-commands-misc-target.h"
#include "qapi/qapi-types-misc-target.h"

#include "qemu/thread.h"
#include "sysemu/cpus.h"
#include "sysemu/hostmem.h"
#include "sysemu/reset.h"

#include "hw/dpu/dpu.h"

#define DPU_MEMDEV_PROP "memdev"
#define DPU_IRAM_SIZE_PROP "isize"
#define DPU_MRAM_SIZE_PROP "msize"
#define DPU_WRAM_SIZE_PROP "wsize"

DeviceState *THE_DPU = NULL;

static void dpu_load_kernel(const char *kernel_filename) {
    uint64_t kernel_entry, kernel_high;

    if (load_elf_ram_sym(kernel_filename, NULL, NULL, NULL,
                         &kernel_entry, NULL, &kernel_high, NULL, 0,
                         EM_DPU, 1, 0, NULL, true, NULL) > 0) {
        return;
    }

    if (load_uimage_as(kernel_filename, &kernel_entry, NULL, NULL,
                       NULL, NULL, NULL) > 0) {
        return;
    }

    if (load_image_targphys_as(kernel_filename, IRAM_ADDR_OFFSET,
                               ram_size, NULL) > 0) {
        return;
    }

    error_report("could not load kernel '%s'", kernel_filename);
    exit(1);
}

static void dpu_system_init(MachineState *ms) {
    DpuSystemState *s = g_new(DpuSystemState, 1);

    object_initialize_child(OBJECT(ms), "dpu.pipeline", &s->dpu, TYPE_DPU);
    qdev_realize(DEVICE(&s->dpu), NULL, &error_abort);

    if (ms->kernel_filename) {
        dpu_load_kernel(ms->kernel_filename);
        s->dpu.run_bits[0] = 1;
        cpu_resume(CPU(&s->dpu.threads[0]));
    }
}

static void dpu_system_class_init(MachineClass *mc) {
    mc->desc = "DPU system";
    mc->init = dpu_system_init;
    mc->is_default = true;
}

DEFINE_MACHINE("dpu-system", dpu_system_class_init)

static void dpu_init(Object *obj) {
    DpuState *s = DPU(obj);

    s->perfcounter.enabled = false;
    s->fault = 0;
    s->step_enabled = false;
    s->bkp_thread = NR_THREADS;
    s->dma_thread = NR_THREADS;
    s->mem_thread = NR_THREADS;

    for (uint8_t each_thread = 0; each_thread < NR_THREADS; ++each_thread) {
        object_initialize_child(obj, "dpu.threads[*]", &s->threads[each_thread], TYPE_DPU_CPU);
    }
}

static void dpu_realize(DeviceState *dev, Error **errp) {
    Object *obj = OBJECT(dev);
    DpuState *s = DPU(dev);

    qemu_mutex_init(&s->state_lock);
    qemu_mutex_init(&s->mram_lock);

    MemoryRegion *iram = g_new(MemoryRegion, 1);
    MemoryRegion *mram = g_new(MemoryRegion, 1);
    MemoryRegion *wram = g_new(MemoryRegion, 1);
    MemoryRegion *atomics = g_new(MemoryRegion, 1);
    MemoryRegion *run_bits = g_new(MemoryRegion, 1);
    MemoryRegion *system_memory = get_system_memory();

    MemoryRegion *memories;
    if (s->hostmem == NULL) {
        memories = g_new(MemoryRegion, 1);
        uint32_t memory_size = s->desc.iram_size + s->desc.mram_size + s->desc.wram_size;
        memory_region_init_ram(memories, obj, "dpu.memories", memory_size, &error_fatal);
    } else {
        if (host_memory_backend_is_mapped(s->hostmem)) {
            char *path = object_get_canonical_path_component(OBJECT(s->hostmem));
            error_setg(&error_fatal, "can't use already busy memdev: %s", path);
            g_free(path);
            return;
        }

        memories = host_memory_backend_get_memory(s->hostmem);
        host_memory_backend_set_mapped(s->hostmem, true);
    }

    memory_region_init_alias(iram, obj, "dpu.iram", memories, 0, s->desc.iram_size);
    memory_region_add_subregion(system_memory, IRAM_ADDR_OFFSET, iram);
    s->iram = memory_region_get_ram_ptr(iram);

    memory_region_init_alias(mram, obj, "dpu.mram", memories, s->desc.iram_size, s->desc.mram_size);
    memory_region_add_subregion(system_memory, MRAM_ADDR_OFFSET, mram);
    s->mram = memory_region_get_ram_ptr(mram);

    memory_region_init_alias(wram, obj, "dpu.wram", memories, s->desc.iram_size + s->desc.mram_size, s->desc.wram_size);
    memory_region_add_subregion(system_memory, WRAM_ADDR_OFFSET, wram);
    s->wram = memory_region_get_ram_ptr(wram);

    memory_region_init_ram_ptr(atomics, obj, "dpu.atomics", ATOMIC_SIZE, s->atomic_bits);
    memory_region_add_subregion(system_memory, ATOMIC_ADDR_OFFSET, atomics);
    vmstate_register_ram(atomics, DEVICE(obj));

    memory_region_init_ram_ptr(run_bits, obj, "dpu.run_bits", RUN_BITS_SIZE, s->run_bits);
    memory_region_add_subregion(system_memory, RUN_BITS_ADDR_OFFSET, run_bits);
    vmstate_register_ram(run_bits, DEVICE(obj));

    for (uint8_t each_thread = 0; each_thread < NR_THREADS; ++each_thread) {
        s->threads[each_thread].env.dpu = s;
        s->threads[each_thread].env.thread_idx = each_thread;
        qdev_realize(DEVICE(&s->threads[each_thread]), NULL, errp);
    }

    THE_DPU = dev;
}

static Property dpu_properties[] = {
    DEFINE_PROP_LINK(DPU_MEMDEV_PROP, DpuState, hostmem,
                     TYPE_MEMORY_BACKEND, HostMemoryBackend *),
    DEFINE_PROP_UINT32(DPU_IRAM_SIZE_PROP, DpuState, desc.iram_size, DEFAULT_IRAM_SIZE),
    DEFINE_PROP_UINT32(DPU_MRAM_SIZE_PROP, DpuState, desc.mram_size, DEFAULT_MRAM_SIZE),
    DEFINE_PROP_UINT32(DPU_WRAM_SIZE_PROP, DpuState, desc.wram_size, DEFAULT_WRAM_SIZE),
    DEFINE_PROP_END_OF_LIST(),
};

static void dpu_class_init(ObjectClass *oc, void *data) {
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize = dpu_realize;
    device_class_set_props(dc, dpu_properties);
}

static const TypeInfo dpu_type_info[] = {
    {
        .name = TYPE_DPU,
        .parent = TYPE_DEVICE,
        .instance_size = sizeof(DpuState),
        .instance_init = dpu_init,
        .class_init = dpu_class_init,
    }
};

DEFINE_TYPES(dpu_type_info)

DpuStartThreadResult* qmp_dpu_start_thread(int64_t thread, int64_t resume, Error **errp) {
    DpuStartThreadResult* result = g_new(DpuStartThreadResult, 1);
    DpuState *s = DPU(THE_DPU);

    qemu_mutex_lock(&s->state_lock);

    bool dpu_running = false;
    for (uint8_t each_thread = 0; each_thread < NR_THREADS; ++each_thread) {
        if (s->run_bits[each_thread] != 0) {
            dpu_running = true;
            break;
        }
    }

    if (!dpu_running) {
        for (uint8_t each_thread = 0; each_thread < NR_THREADS; ++each_thread) {
            tb_flush(CPU(&s->threads[each_thread]));
        }
        tlb_flush_all_cpus_synced(CPU(&s->threads[thread]));
    }

    uint8_t running = s->run_bits[thread];
    result->previous = running & 1;

    if (result->previous == 0) {
        if (resume == 0) {
            s->threads[thread].env.pc = IRAM_ADDR_OFFSET;
        }
        s->run_bits[thread] = 1;
        cpu_resume(CPU(&s->threads[thread]));
    }
    qemu_mutex_unlock(&s->state_lock);

    return result;
}

DpuPollResult *qmp_dpu_poll(Error **errp) {
    DpuPollResult* result = g_new(DpuPollResult, 1);
    DpuState *s = DPU(THE_DPU);

    result->fault = s->fault != 0;
    result->run = 0;

    for (uint8_t each_thread = 0; each_thread < NR_THREADS; ++each_thread) {
        if ((s->run_bits[each_thread] & 1) != 0) {
            result->run = 1;
            break;
        }
    }

    return result;
}

void qmp_dpu_trigger_fault(Error **errp) {
    DpuState *s = DPU(THE_DPU);

    s->fault = 1;
    pause_all_vcpus();
}

DpuFaultInfo *qmp_dpu_fault_info(Error **errp) {
    DpuFaultInfo* result = g_new(DpuFaultInfo, 1);
    DpuState *s = DPU(THE_DPU);

    result->bkp = s->bkp_thread;
    result->dma = s->dma_thread;
    result->mem = s->mem_thread;

    for (uint8_t thread = 0; thread < NR_THREADS; ++thread) {
        s->run_bits[thread] = 0;
    }

    s->bkp_thread = NR_THREADS;
    s->dma_thread = NR_THREADS;
    s->mem_thread = NR_THREADS;
    s->fault = 0;

    return result;
}

DpuStepThreadResult *qmp_dpu_step_thread(int64_t thread, Error **errp) {
    DpuStepThreadResult* result = g_new(DpuStepThreadResult, 1);
    DpuState *s = DPU(THE_DPU);

    CPUState *cpu = CPU(&s->threads[thread]);
    cpu_single_step(cpu, true);

    tlb_flush(cpu);

    s->step_enabled = true;
    s->step_thread = thread;
    s->run_bits[thread] = 1;

    cpu_resume(cpu);

    while (!cpu_is_stopped(cpu)) {}

    cpu_single_step(cpu, false);
    s->step_enabled = false;
    result->started = NR_THREADS;
    for (uint8_t each_thread = 0; each_thread < NR_THREADS; ++each_thread) {
        if ((s->run_bits[each_thread] != 0) && (each_thread != thread)) {
            result->started = each_thread;
            break;
        }
    }

    return result;
}

void qmp_dpu_set_state(const char *element, int64_t thread, int64_t idx, int64_t value, Error **errp) {
    DpuState *s = DPU(THE_DPU);

    if (strcmp("pc", element) == 0) {
        s->threads[thread].env.pc = (value << 3) | IRAM_ADDR_OFFSET;
    } else if (strcmp("cf", element) == 0) {
        s->threads[thread].env.cf = value;
    } else if (strcmp("zf", element) == 0) {
        s->threads[thread].env.zf = value;
    } else if (strcmp("reg", element) == 0) {
        s->threads[thread].env.regs[idx] = value;
    } else if (strcmp("atomic", element) == 0) {
        s->atomic_bits[idx] = value;
    } else {
        error_setg(errp, "the element '%s' is not allowed", element);
        return;
    }
}

DpuStateValue *qmp_dpu_get_state(const char *element, int64_t thread, int64_t idx, Error **errp) {
    DpuState *s = DPU(THE_DPU);
    int64_t value;

    if (strcmp("pc", element) == 0) {
        value = (s->threads[thread].env.pc & ~IRAM_ADDR_OFFSET) >> 3;
    } else if (strcmp("cf", element) == 0) {
        value = s->threads[thread].env.cf & 1;
    } else if (strcmp("zf", element) == 0) {
        value = s->threads[thread].env.zf & 1;
    } else if (strcmp("reg", element) == 0) {
        value = s->threads[thread].env.regs[idx] & 0xffffffffl;
    } else if (strcmp("atomic", element) == 0) {
        value = s->atomic_bits[idx] & 1;
    } else if (strcmp("run", element) == 0) {
        value = s->run_bits[thread] & 1;
    } else {
        error_setg(errp, "the element '%s' is not allowed", element);
        return NULL;
    }

    DpuStateValue* result = g_new(DpuStateValue, 1);
    result->value = value;
    return result;
}
