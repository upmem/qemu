#ifndef DPU_CTXT_H
#define DPU_CTXT_H

#include "exec/translator.h"

typedef struct DisasContext {
    DisasContextBase base;
    uint32_t iram_size;
    uint32_t wram_size;

    struct {
        bool gen_mem_fault_check;
        void *expected;
        void *used;
    };
} DisasContext;

void gen_fault(DisasContext *ctx, uint32_t id);

#endif /* DPU_CTXT_H */
