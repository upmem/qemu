#ifndef DPU_DECODE_H
#define DPU_DECODE_H

#include <stdbool.h>
#include "ctxt.h"

bool decode_instruction(DisasContext *ctx, uint64_t instruction);

#endif /* DPU_DECODE_H */
