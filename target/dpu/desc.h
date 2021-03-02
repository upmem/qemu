/*
 * Copyright (c) 2020 - UPMEM
 */

#ifndef __DPU_DESC_H__
#define __DPU_DESC_H__

#include <stdint.h>

typedef struct {
	uint8_t rc;
	uint8_t dc;
	uint8_t ra;
	uint8_t rb;
	uint8_t db;
	uint16_t pc;
	uint8_t cc;
	uint8_t shift;
	uint32_t imm;
	uint32_t off;
	uint8_t endian;
	uint8_t immDma;
} InstructionDescriptor;

#endif /* __DPU_DESC_H__ */
