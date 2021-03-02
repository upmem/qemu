/*
 * Copyright (c) 2020 - UPMEM
 */

#include "qemu/osdep.h"
#include "cpu.h"
#include "decode.h"
#include "desc.h"
#include "translate.h"

bool decode_instruction(DisasContext *ctx, uint64_t instruction) {
	InstructionDescriptor desc = { .ra = DPU_REG_ZERO };

	if ((((instruction >> 44) & 0xfL))==(0x7L)) {
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			if ((((instruction >> 42) & 0x3L))==(0x3L)) {
				if (((((instruction >> 28) & 0xfL))&(0x8L))==(0x8L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.pc = (((instruction >> 0) & 65535) << 0);
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 26) & 31) << 8) | (((instruction >> 39) & 7) << 13);
					if ((((instruction >> 24) & 0x3L))!=(0x0L)) {
						desc.cc = (((instruction >> 24) & 3) << 0);
						return translate_acquire_rici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x3L))==(0x0L)) {
						desc.cc = (((instruction >> 24) & 3) << 0);
						return translate_release_rici(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
					if (((((instruction >> 39) & 0x1fL))&(0x1bL))==(0x1bL)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_boot_rici(ctx, &desc);
						}
					}
					if (((((instruction >> 39) & 0x1fL))&(0x1fL))==(0x19L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_clr_run_rici(ctx, &desc);
						}
					}
					if (((((instruction >> 39) & 0x1fL))&(0x1fL))==(0x1cL)) {
						if ((((instruction >> 34) & 0x1fL))==(0x18L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
								return translate_fault_i(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 39) & 0x1fL))&(0x1fL))==(0x18L)) {
						if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x3L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
								return translate_read_run_rici(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 39) & 0x1fL))&(0x1bL))==(0x1aL)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_resume_rici(ctx, &desc);
						}
					}
					if (((((instruction >> 39) & 0x1fL))&(0x1fL))==(0x1dL)) {
						if ((((instruction >> 34) & 0x1fL))==(0x1cL)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_stop_ci(ctx, &desc);
							}
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x0L)) {
					if (((((instruction >> 39) & 0x1fL))&(0x1fL))==(0x18L)) {
						if ((((instruction >> 34) & 0x1fL))==(0x18L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x0L)) {
									if (((((instruction >> 0) & 0xffffL))&(0xffffL))==(0x0L)) {
										return translate_nop_(ctx, &desc);
									}
								}
							}
						}
						if ((((instruction >> 37) & 0x3L))!=(0x3L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
								return translate_tell_ri(ctx, &desc);
							}
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
					if ((((instruction >> 28) & 0x1L))==(0x0L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11);
						desc.endian = (((instruction >> 27) & 1) << 0);
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x0L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 15) << 4);
							return translate_sb_erii(ctx, &desc);
						}
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
							return translate_sd_erii(ctx, &desc);
						}
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x2L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
							return translate_sh_erii(ctx, &desc);
						}
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
							return translate_sw_erii(ctx, &desc);
						}
					}
					if ((((instruction >> 28) & 0x1L))==(0x1L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11);
						desc.endian = (((instruction >> 27) & 1) << 0);
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x0L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 15) << 4);
							return translate_sb_esii(ctx, &desc);
						}
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
							return translate_sd_esii(ctx, &desc);
						}
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x2L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
							return translate_sh_esii(ctx, &desc);
						}
						if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
							desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
							return translate_sw_esii(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11);
					desc.endian = (((instruction >> 27) & 1) << 0);
					if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x0L)) {
						desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 15) << 4);
						return translate_sb_id_erii(ctx, &desc);
					}
					if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
						desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
						return translate_sd_id_erii(ctx, &desc);
					}
					if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x2L)) {
						desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
						return translate_sh_id_erii(ctx, &desc);
					}
					if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
						desc.imm = (((instruction >> 16) & 15) << 0) | (((instruction >> 0) & 4095) << 4);
						return translate_sw_id_erii(ctx, &desc);
					}
				}
			}
			if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
				if ((((instruction >> 25) & 0x3L))!=(0x3L)) {
					if (((((instruction >> 28) & 0xfL))&(0xcL))==(0x4L)) {
						if ((((instruction >> 28) & 0x1L))==(0x0L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x1L)) {
								if (((((instruction >> 29) & 0x1L))==(0x1L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
									desc.dc = (((instruction >> 40) & 15) << 1);
									return translate_lbs_s_erri(ctx, &desc);
								}
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lbs_erri(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x0L)) {
								if (((((instruction >> 29) & 0x1L))==(0x1L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
									desc.dc = (((instruction >> 40) & 15) << 1);
									return translate_lbu_u_erri(ctx, &desc);
								}
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lbu_erri(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x3L)) {
								if (((((instruction >> 29) & 0x1L))==(0x1L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
									desc.dc = (((instruction >> 40) & 15) << 1);
									return translate_lhs_s_erri(ctx, &desc);
								}
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lhs_erri(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x2L)) {
								if (((((instruction >> 29) & 0x1L))==(0x1L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
									desc.dc = (((instruction >> 40) & 15) << 1);
									return translate_lhu_u_erri(ctx, &desc);
								}
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lhu_erri(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
								if (((((instruction >> 29) & 0x1L))==(0x1L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
									desc.dc = (((instruction >> 40) & 15) << 1);
									return translate_lw_s_erri(ctx, &desc);
								}
								if (((((instruction >> 29) & 0x1L))==(0x1L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
									desc.dc = (((instruction >> 40) & 15) << 1);
									return translate_lw_u_erri(ctx, &desc);
								}
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lw_erri(ctx, &desc);
								}
							}
						}
						if ((((instruction >> 28) & 0x1L))==(0x1L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x1L)) {
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lbs_ersi(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x0L)) {
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lbu_ersi(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x3L)) {
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lhs_ersi(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x7L))==(0x2L)) {
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lhu_ersi(ctx, &desc);
								}
							}
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
								if ((((instruction >> 29) & 0x1L))==(0x0L)) {
									desc.rc = (((instruction >> 39) & 31) << 0);
									return translate_lw_ersi(ctx, &desc);
								}
							}
						}
					}
				}
				if ((((instruction >> 25) & 0x3L))==(0x3L)) {
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
						if ((((instruction >> 28) & 0x1L))==(0x0L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
								desc.dc = (((instruction >> 39) & 31) << 0);
								return translate_ld_erri(ctx, &desc);
							}
						}
						if ((((instruction >> 28) & 0x1L))==(0x1L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
								desc.dc = (((instruction >> 39) & 31) << 0);
								return translate_ld_ersi(ctx, &desc);
							}
						}
					}
				}
			}
		}
		if ((((instruction >> 32) & 0x3L))!=(0x3L)) {
			if (((((instruction >> 39) & 0x1fL))&(0x1fL))==(0x0L)) {
				desc.immDma = (((instruction >> 24) & 255) << 0);
				desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 0) & 0xffffL))&(0xffffL))==(0x0L)) {
					return translate_ldma_rri(ctx, &desc);
				}
				if (((((instruction >> 0) & 0xffffL))&(0xffffL))==(0x1L)) {
					return translate_ldmai_rri(ctx, &desc);
				}
				if (((((instruction >> 0) & 0xffffL))&(0xffffL))==(0x2L)) {
					return translate_sdma_rri(ctx, &desc);
				}
			}
			if ((((instruction >> 42) & 0x3L))==(0x3L)) {
				if ((((instruction >> 16) & 0x1L))==(0x0L)) {
					desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 28) & 0xfL))&(0xcL))==(0x4L)) {
						if ((((instruction >> 28) & 0x1L))==(0x0L)) {
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x0L)) {
								return translate_sb_erir(ctx, &desc);
							}
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x2L)) {
								return translate_sh_erir(ctx, &desc);
							}
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
								return translate_sw_erir(ctx, &desc);
							}
						}
						if ((((instruction >> 28) & 0x1L))==(0x1L)) {
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x0L)) {
								return translate_sb_esir(ctx, &desc);
							}
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x2L)) {
								return translate_sh_esir(ctx, &desc);
							}
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x4L)) {
								return translate_sw_esir(ctx, &desc);
							}
						}
					}
				}
				if ((((instruction >> 16) & 0x1L))==(0x1L)) {
					desc.db = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 28) & 0xfL))&(0xcL))==(0x4L)) {
						if ((((instruction >> 28) & 0x1L))==(0x0L)) {
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
								return translate_sd_erir(ctx, &desc);
							}
						}
						if ((((instruction >> 28) & 0x1L))==(0x1L)) {
							desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 39) & 7) << 4) | (((instruction >> 24) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							desc.endian = (((instruction >> 27) & 1) << 0);
							if (((((instruction >> 24) & 0xfL))&(0x6L))==(0x6L)) {
								return translate_sd_esir(ctx, &desc);
							}
						}
					}
				}
			}
		}
	}
	if (((((instruction >> 45) & 0x7L))==(0x0L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x0L))) {
			desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
			if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
				desc.dc = (((instruction >> 40) & 15) << 1);
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 44) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_add_s_rri(ctx, &desc);
				}
			}
			if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
				desc.dc = (((instruction >> 40) & 15) << 1);
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 44) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_add_u_rri(ctx, &desc);
				}
			}
		}
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			if (((((instruction >> 44) & 0xfL))==(0x0L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_add_rri(ctx, &desc);
				}
			}
			if (((((instruction >> 44) & 0xfL))==(0x1L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_addc_rri(ctx, &desc);
				}
			}
		}
	}
	if ((((((instruction >> 47) & 0x1L))==(0x0L))&&((((instruction >> 44) & 0x7L))!=(0x7L)))&&((((instruction >> 42) & 0x3L))==(0x3L))) {
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
				desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_add_s_rric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_add_s_rrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_add_s_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_addc_s_rric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_addc_s_rrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_addc_s_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_sub_s_rirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_sub_s_rirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_sub_s_rirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_sub_s_rric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_sub_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_sub_s_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_subc_s_rirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_subc_s_rirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_subc_s_rirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_subc_s_rric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_subc_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_subc_s_rrif(ctx, &desc);
						}
					}
				}
			}
			if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
				desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_add_u_rric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_add_u_rrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_add_u_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_addc_u_rric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_addc_u_rrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_addc_u_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_sub_u_rirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_sub_u_rirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_sub_u_rirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_sub_u_rric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_sub_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_sub_u_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_subc_u_rirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_subc_u_rirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_subc_u_rirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_subc_u_rric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_subc_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_subc_u_rrif(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
				desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_add_rric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_add_rrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_add_rrif(ctx, &desc);
						}
					}
					if (((((instruction >> 28) & 0x1L))==(0x1L))&&((((instruction >> 24) & 0xfL))==(0x0L))) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 31) << 12) | (((instruction >> 5) & 1) << 16) | (((instruction >> 6) & 1) << 16) | (((instruction >> 7) & 1) << 16) | (((instruction >> 8) & 1) << 16) | (((instruction >> 9) & 1) << 16) | (((instruction >> 10) & 1) << 16) | (((instruction >> 11) & 1) << 16);
						return translate_add_ssi(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_addc_rric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_addc_rrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_addc_rrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_sub_rirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_sub_rirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_sub_rirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_sub_rric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_sub_rrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_sub_rrif(ctx, &desc);
						}
					}
					if (((((instruction >> 28) & 0x1L))==(0x1L))&&((((instruction >> 24) & 0xfL))==(0x0L))) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 31) << 12) | (((instruction >> 5) & 1) << 16) | (((instruction >> 6) & 1) << 16) | (((instruction >> 7) & 1) << 16) | (((instruction >> 8) & 1) << 16) | (((instruction >> 9) & 1) << 16) | (((instruction >> 10) & 1) << 16) | (((instruction >> 11) & 1) << 16);
						return translate_sub_ssi(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_subc_rirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_subc_rirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_subc_rirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_subc_rric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
							return translate_subc_rrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
							return translate_subc_rrif(ctx, &desc);
						}
					}
				}
			}
			if ((((instruction >> 44) & 0x3L))==(0x3L)) {
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_add_zric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8);
							return translate_add_zrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_add_zrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_addc_zric(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 31) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8);
							return translate_addc_zrici(ctx, &desc);
						}
						if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_addc_zrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
						return translate_sub_zirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8);
						return translate_sub_zirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
						return translate_sub_zirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_sub_zric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8);
							return translate_sub_zrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_sub_zrif(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
						return translate_subc_zirc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8);
						return translate_subc_zirci(ctx, &desc);
					}
					if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
						return translate_subc_zirf(ctx, &desc);
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
					if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
						if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_subc_zric(ctx, &desc);
						}
						if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8);
							return translate_subc_zrici(ctx, &desc);
						}
						if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
							desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24);
							return translate_subc_zrif(ctx, &desc);
						}
					}
				}
			}
		}
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x0L))) {
			if (((((instruction >> 20) & 0xfL))&(0xcL))==(0xcL)) {
				if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_add_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_add_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_add_s_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_addc_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_addc_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_addc_s_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsub_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsub_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsub_s_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsubc_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsubc_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsubc_s_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_sub_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_sub_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_sub_s_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_subc_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_subc_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_subc_s_rrrci(ctx, &desc);
							}
						}
					}
				}
				if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_add_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_add_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_add_u_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_addc_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_addc_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_addc_u_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsub_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsub_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsub_u_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsubc_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsubc_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsubc_u_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_sub_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_sub_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_sub_u_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_subc_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_subc_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_subc_u_rrrci(ctx, &desc);
							}
						}
					}
				}
				if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_add_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_add_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_add_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 28) & 0x1L))==(0x1L))&&((((instruction >> 24) & 0xfL))==(0x0L))) {
							if ((((instruction >> 37) & 0x3L))!=(0x3L)) {
								desc.rb = (((instruction >> 34) & 31) << 0);
								desc.ra = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
								return translate_add_sss(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_addc_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_addc_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_addc_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsub_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsub_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsub_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 28) & 0x1L))==(0x1L))&&((((instruction >> 24) & 0xfL))==(0x0L))) {
							if ((((instruction >> 37) & 0x3L))!=(0x3L)) {
								desc.rb = (((instruction >> 34) & 31) << 0);
								desc.ra = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
								return translate_sub_sss(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsubc_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsubc_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsubc_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_sub_rrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_sub_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_sub_rrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_subc_rrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_subc_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_subc_rrrci(ctx, &desc);
							}
						}
					}
				}
				if ((((instruction >> 44) & 0x3L))==(0x3L)) {
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_add_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_add_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_add_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_addc_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_addc_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_addc_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsub_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsub_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsub_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((instruction >> 24) & 0x1fL))==(0x0L)) {
								return translate_rsubc_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								return translate_rsubc_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_rsubc_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0x8L)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_sub_zrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_sub_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_sub_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 28) & 0xfL))&(0xaL))==(0xaL)) {
						if (((((instruction >> 28) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if (((((instruction >> 24) & 0x1fL))==(0x0L))&&((((instruction >> 30) & 0x1L))==(0x0L))) {
								return translate_subc_zrr(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x1L))||((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&(((((instruction >> 25) & 0x1L))==(0x1L))&&((((instruction >> 28) & 0x1L))==(0x0L)))))&&(((((instruction >> 30) & 0x1L))!=(0x1L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								return translate_subc_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 30) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0x1fL))<(0x6L))||(((((instruction >> 24) & 0x1fL))>(0xbL))||(((((instruction >> 24) & 0x1fL))&(0x1eL))==(0x8L)))))&&(((((instruction >> 30) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0x1fL))!=(0x0L)))) {
								desc.cc = (((instruction >> 24) & 31) << 0) | (((instruction >> 30) & 1) << 5);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_subc_zrrci(ctx, &desc);
							}
						}
					}
				}
			}
			if (((((instruction >> 20) & 0xfL))&(0xcL))!=(0xcL)) {
				if (((((instruction >> 28) & 0xfL))&(0x2L))==(0x0L)) {
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x7L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_sh_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_sh_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_sh_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_sh_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_sh_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_sh_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_sh_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_sh_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_sh_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x6L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_sl_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_sl_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_sl_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_sl_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_sl_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_sl_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_sl_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_sl_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_sl_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xbL)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_uh_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_uh_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_uh_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_uh_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_uh_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_uh_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_uh_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_uh_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_uh_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xaL)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_ul_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_ul_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_ul_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_ul_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_ul_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_ul_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sh_ul_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sh_ul_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sh_ul_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x5L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_sh_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_sh_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_sh_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_sh_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_sh_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_sh_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_sh_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_sh_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_sh_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x4L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_sl_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_sl_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_sl_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_sl_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_sl_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_sl_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_sl_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_sl_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_sl_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x9L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_uh_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_uh_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_uh_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_uh_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_uh_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_uh_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_uh_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_uh_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_uh_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_ul_s_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_ul_s_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_ul_s_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_ul_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_ul_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_ul_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_sl_ul_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_sl_ul_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_sl_ul_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x3L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_uh_uh_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_uh_uh_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_uh_uh_u_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_uh_uh_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_uh_uh_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_uh_uh_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_uh_uh_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_uh_uh_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_uh_uh_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x2L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_uh_ul_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_uh_ul_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_uh_ul_u_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_uh_ul_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_uh_ul_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_uh_ul_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_uh_ul_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_uh_ul_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_uh_ul_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x1L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_ul_uh_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_ul_uh_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_ul_uh_u_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_ul_uh_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_ul_uh_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_ul_uh_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_ul_uh_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_ul_uh_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_ul_uh_zrrci(ctx, &desc);
							}
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x0L)) {
						desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
							desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_ul_ul_u_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_ul_ul_u_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_ul_ul_u_rrrci(ctx, &desc);
							}
						}
						if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
							desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_ul_ul_rrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_ul_ul_rrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_ul_ul_rrrci(ctx, &desc);
							}
						}
						if ((((instruction >> 44) & 0x3L))==(0x3L)) {
							if ((((instruction >> 24) & 0xfL))==(0x0L)) {
								return translate_mul_ul_ul_zrr(ctx, &desc);
							}
							if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
								desc.cc = (((instruction >> 24) & 15) << 0);
								return translate_mul_ul_ul_zrrc(ctx, &desc);
							}
							if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0x1fL))!=(0x0L))) {
								desc.cc = (((instruction >> 24) & 31) << 0);
								desc.pc = (((instruction >> 0) & 65535) << 0);
								return translate_mul_ul_ul_zrrci(ctx, &desc);
							}
						}
					}
				}
				if (((((instruction >> 28) & 0xfL))&(0x3L))==(0x2L)) {
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
						if ((((instruction >> 34) & 0x1fL))==(0x18L)) {
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
								desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_s_r(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_s_rci(ctx, &desc);
								}
							}
							if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
								desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_u_r(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_u_rci(ctx, &desc);
								}
							}
							if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
								desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_r(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_rci(ctx, &desc);
								}
							}
							if ((((instruction >> 44) & 0x3L))==(0x3L)) {
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_z(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_zci(ctx, &desc);
								}
							}
						}
						if ((((instruction >> 34) & 0x1fL))==(0x19L)) {
							desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
							desc.ra = (((instruction >> 34) & 31) << 0);
							if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
								desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_cfg_s_rr(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_cfg_s_rrci(ctx, &desc);
								}
							}
							if ((((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
								desc.dc = (((instruction >> 40) & 3) << 1) | (((instruction >> 44) & 3) << 3);
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_cfg_u_rr(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_cfg_u_rrci(ctx, &desc);
								}
							}
							if (((((instruction >> 44) & 0x3L))!=(0x3L))&&((((instruction >> 46) & 0x1L))==(0x0L))) {
								desc.rc = (((instruction >> 39) & 7) << 0) | (((instruction >> 44) & 3) << 3);
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_cfg_rr(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_cfg_rrci(ctx, &desc);
								}
							}
							if ((((instruction >> 44) & 0x3L))==(0x3L)) {
								if ((((instruction >> 24) & 0xfL))==(0x0L)) {
									return translate_time_cfg_zr(ctx, &desc);
								}
								if ((((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
									desc.cc = (((instruction >> 24) & 15) << 0);
									desc.pc = (((instruction >> 0) & 65535) << 0);
									return translate_time_cfg_zrci(ctx, &desc);
								}
							}
						}
					}
				}
			}
		}
	}
	if (((((instruction >> 44) & 0xfL))==(0x6L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x0L))) {
			desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
			if ((((instruction >> 37) & 0x3L))==(0x3L)) {
				desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 39) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0x0L)) {
					return translate_add_zri(ctx, &desc);
				}
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0x2L)) {
					return translate_addc_zri(ctx, &desc);
				}
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0xaL)) {
					return translate_and_zri(ctx, &desc);
				}
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0xcL)) {
					return translate_or_zri(ctx, &desc);
				}
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0x4L)) {
					return translate_sub_zir(ctx, &desc);
				}
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0x6L)) {
					return translate_subc_zir(ctx, &desc);
				}
				if (((((instruction >> 39) & 0x1fL))&(0x1eL))==(0x8L)) {
					return translate_xor_zri(ctx, &desc);
				}
			}
		}
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			desc.ra = (((instruction >> 34) & 31) << 0);
			desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
			if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
				desc.rc = (((instruction >> 39) & 31) << 0);
				return translate_or_rri(ctx, &desc);
			}
		}
	}
	if (((((instruction >> 45) & 0x7L))==(0x2L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			if (((((instruction >> 44) & 0xfL))==(0x5L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
						return translate_and_s_rki(ctx, &desc);
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
						return translate_and_u_rki(ctx, &desc);
					}
				}
				if ((((instruction >> 37) & 0x3L))!=(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
						return translate_and_rri(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 44) & 0xfL))==(0x4L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_xor_rri(ctx, &desc);
				}
			}
		}
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x0L))) {
			desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
			if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
				desc.dc = (((instruction >> 40) & 15) << 1);
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 44) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_or_s_rri(ctx, &desc);
				}
			}
			if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
				desc.dc = (((instruction >> 40) & 15) << 1);
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 44) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_or_u_rri(ctx, &desc);
				}
			}
		}
	}
	if (((((instruction >> 45) & 0x7L))==(0x1L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x0L))) {
			desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
			if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
				desc.dc = (((instruction >> 40) & 15) << 1);
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 44) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_and_s_rri(ctx, &desc);
				}
			}
			if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
				desc.dc = (((instruction >> 40) & 15) << 1);
				if ((((instruction >> 37) & 0x3L))==(0x3L)) {
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 34) & 7) << 4) | (((instruction >> 44) & 1) << 7) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_and_u_rri(ctx, &desc);
				}
			}
		}
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			if (((((instruction >> 44) & 0xfL))==(0x2L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_sub_rir(ctx, &desc);
				}
			}
			if (((((instruction >> 44) & 0xfL))==(0x3L))&&((((instruction >> 42) & 0x3L))!=(0x3L))) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 24) & 255) << 24);
					return translate_subc_rir(ctx, &desc);
				}
			}
		}
	}
	if ((((instruction >> 45) & 0x7L))==(0x4L)) {
		if ((((instruction >> 32) & 0x3L))==(0x3L)) {
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xaL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_and_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_and_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_and_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_and_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_and_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_and_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_and_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_and_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_and_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_and_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_and_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_and_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xcL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_andn_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_andn_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_andn_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_andn_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_andn_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_andn_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_andn_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_andn_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_andn_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_andn_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_andn_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_andn_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xcL))==(0x4L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_s_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_s_rri(ctx, &desc);
						}
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_s_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_s_rric(ctx, &desc);
						}
					}
					if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xdL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
						desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_s_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_s_rrici(ctx, &desc);
						}
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_u_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_u_rri(ctx, &desc);
						}
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_u_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_u_rric(ctx, &desc);
						}
					}
					if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xdL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
						desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_u_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_u_rrici(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_rri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_rri(ctx, &desc);
						}
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_rric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_rric(ctx, &desc);
						}
					}
					if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xdL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
						desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_rrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_rrici(ctx, &desc);
						}
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_zri(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_zri(ctx, &desc);
						}
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							return translate_asr_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							return translate_lsl1_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							return translate_lsl1x_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							return translate_lsl_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							return translate_lslx_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							return translate_lsr1_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							return translate_lsr1x_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							return translate_lsr_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							return translate_lsrx_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							return translate_rol_zric(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							return translate_ror_zric(ctx, &desc);
						}
					}
					if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xdL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
						desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x8L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x6L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x7L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x4L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x5L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xeL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xfL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xcL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xdL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0x2L)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_zrici(ctx, &desc);
						}
						if (((((instruction >> 16) & 0xfL))&(0xfL))==(0xaL)) {
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_zrici(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x0L)) {
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_call_rri(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.off = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_call_zri(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x3L)) {
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x0L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cao_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cao_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cao_s_rrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cao_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cao_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cao_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cao_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cao_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cao_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cao_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cao_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cao_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x1L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clo_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clo_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clo_s_rrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clo_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clo_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clo_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clo_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clo_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clo_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clo_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clo_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clo_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x2L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cls_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cls_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cls_s_rrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cls_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cls_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cls_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cls_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cls_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cls_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_cls_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_cls_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_cls_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x3L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clz_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clz_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clz_s_rrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clz_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clz_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clz_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clz_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clz_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clz_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_clz_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_clz_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_clz_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x5L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extsb_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extsb_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extsb_s_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extsb_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extsb_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extsb_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extsb_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extsb_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extsb_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x7L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extsh_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extsh_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extsh_s_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extsh_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extsh_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extsh_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extsh_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extsh_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extsh_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x4L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extub_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extub_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extub_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extub_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extub_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extub_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extub_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extub_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extub_zrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0x7L))==(0x6L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extuh_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extuh_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extuh_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extuh_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extuh_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extuh_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_extuh_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_extuh_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_extuh_zrci(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x1L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_hash_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_hash_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_hash_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_hash_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_hash_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_hash_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_hash_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_hash_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_hash_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_hash_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_hash_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_hash_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xfL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nand_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nand_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nand_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nand_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nand_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nand_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nand_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nand_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nand_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_nand_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_nand_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_nand_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xeL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nor_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nor_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nor_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nor_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nor_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nor_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nor_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nor_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nor_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_nor_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_nor_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_nor_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x9L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nxor_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nxor_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nxor_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nxor_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nxor_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nxor_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nxor_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_nxor_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_nxor_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_nxor_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_nxor_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_nxor_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xbL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_or_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_or_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_or_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_or_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_or_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_or_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_or_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_or_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_or_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_or_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_or_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_or_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xdL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_orn_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_orn_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_orn_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_orn_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_orn_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_orn_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_orn_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_orn_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_orn_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_orn_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_orn_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_orn_zrif(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x2L)) {
				desc.ra = (((instruction >> 34) & 31) << 0);
				if (((((instruction >> 20) & 0xfL))&(0xcL))==(0x0L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_sats_s_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_sats_s_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_sats_s_rrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_sats_u_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_sats_u_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_sats_u_rrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_sats_rr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_sats_rrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_sats_rrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_sats_zr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_sats_zrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_sats_zrci(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x8L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_xor_s_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_xor_s_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_xor_s_rrif(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_xor_u_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_xor_u_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_xor_u_rrif(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_xor_rric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4);
						return translate_xor_rrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12);
						return translate_xor_rrif(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_xor_zric(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 39) & 7) << 8) | (((instruction >> 44) & 1) << 11);
						return translate_xor_zrici(ctx, &desc);
					}
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.imm = (((instruction >> 20) & 15) << 0) | (((instruction >> 16) & 15) << 4) | (((instruction >> 15) & 1) << 8) | (((instruction >> 14) & 1) << 9) | (((instruction >> 13) & 1) << 10) | (((instruction >> 12) & 1) << 11) | (((instruction >> 0) & 4095) << 12) | (((instruction >> 39) & 7) << 24) | (((instruction >> 44) & 1) << 27);
						return translate_xor_zrif(ctx, &desc);
					}
				}
			}
		}
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x0L))) {
			desc.rb = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xcL)) {
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xaL)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_and_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_and_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_and_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_and_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_and_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_and_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_and_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_and_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_and_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_and_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_and_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_and_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xcL)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_andn_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_andn_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_andn_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_andn_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_andn_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_andn_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_andn_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_andn_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_andn_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_andn_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_andn_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_andn_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x0L)) {
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_call_rrr(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_call_zrr(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x1L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_hash_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_hash_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_hash_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_hash_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_hash_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_hash_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_hash_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_hash_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_hash_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_hash_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_hash_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_hash_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xfL)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nand_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nand_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nand_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nand_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nand_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nand_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nand_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nand_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nand_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nand_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nand_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nand_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xeL)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nor_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nor_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nor_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nor_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nor_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nor_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nor_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nor_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nor_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nor_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nor_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nor_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x9L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nxor_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nxor_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nxor_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nxor_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nxor_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nxor_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nxor_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nxor_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nxor_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_nxor_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_nxor_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_nxor_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xbL)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_or_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_or_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_or_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_or_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_or_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_or_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_or_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_or_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_or_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_or_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_or_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_or_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xdL)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_orn_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_orn_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_orn_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_orn_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_orn_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_orn_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_orn_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_orn_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_orn_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_orn_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_orn_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_orn_zrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_xor_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_xor_s_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_xor_s_rrrci(ctx, &desc);
						}
					}
					if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
						desc.dc = (((instruction >> 40) & 15) << 1);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_xor_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_xor_u_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_xor_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
						desc.rc = (((instruction >> 39) & 31) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_xor_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_xor_rrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_xor_rrrci(ctx, &desc);
						}
					}
					if ((((instruction >> 42) & 0x3L))==(0x3L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if ((((instruction >> 24) & 0xfL))==(0x0L)) {
							return translate_xor_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_xor_zrrc(ctx, &desc);
						}
						if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_xor_zrrci(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xdL))==(0xdL)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_asr_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_asr_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x4L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x6L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x7L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1x_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1x_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x5L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lslx_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lslx_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xcL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xeL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xfL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1x_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1x_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xdL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsrx_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsrx_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x2L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_rol_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_rol_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_s_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xaL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_ror_s_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_ror_s_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_s_rrrci(ctx, &desc);
						}
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_asr_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_asr_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x4L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x6L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x7L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1x_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1x_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x5L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lslx_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lslx_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xcL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xeL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xfL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1x_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1x_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xdL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsrx_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsrx_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x2L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_rol_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_rol_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_u_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xaL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_ror_u_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_ror_u_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_u_rrrci(ctx, &desc);
						}
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_asr_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_asr_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x6L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x7L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1x_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1x_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x4L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x5L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lslx_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lslx_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xeL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xfL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1x_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1x_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xcL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xdL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsrx_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsrx_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x2L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_rol_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_rol_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_rrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xaL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_ror_rrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_ror_rrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_rrrci(ctx, &desc);
						}
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x8L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_asr_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_asr_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_asr_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x6L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x7L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl1x_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl1x_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl1x_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x4L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsl_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsl_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsl_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x5L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lslx_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lslx_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lslx_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xeL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xfL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr1x_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr1x_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr1x_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xcL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsr_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsr_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsr_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xdL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_lsrx_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_lsrx_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_lsrx_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0x2L)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_rol_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_rol_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_rol_zrrci(ctx, &desc);
						}
					}
					if (((((instruction >> 20) & 0xfL))&(0xfL))==(0xaL)) {
						if (((((instruction >> 24) & 0xfL))==(0x0L))&&((((instruction >> 29) & 0x1L))==(0x0L))) {
							return translate_ror_zrr(ctx, &desc);
						}
						if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							return translate_ror_zrrc(ctx, &desc);
						}
						if (((((((instruction >> 29) & 0x1L))==(0x0L))&&(((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))||(((((instruction >> 29) & 0x1L))==(0x1L))&&(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L)))))&&(((((instruction >> 29) & 0x1L))!=(0x0L))||((((instruction >> 24) & 0xfL))!=(0x0L)))) {
							desc.cc = (((instruction >> 24) & 15) << 0) | (((instruction >> 29) & 1) << 4);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_ror_zrrci(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xcL))==(0x8L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						return translate_cmpb4_s_rrr(ctx, &desc);
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						return translate_cmpb4_s_rrrc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						return translate_cmpb4_s_rrrci(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						return translate_cmpb4_u_rrr(ctx, &desc);
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						return translate_cmpb4_u_rrrc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						return translate_cmpb4_u_rrrci(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						return translate_cmpb4_rrr(ctx, &desc);
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						return translate_cmpb4_rrrc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						return translate_cmpb4_rrrci(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						return translate_cmpb4_zrr(ctx, &desc);
					}
					if ((((((instruction >> 26) & 0x1L))^(((instruction >> 27) & 0x1L)))==(0x1L))&&((((instruction >> 25) & 0x1L))==(0x1L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						return translate_cmpb4_zrrc(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x6L))||(((((instruction >> 24) & 0xfL))>(0xbL))||(((((instruction >> 24) & 0xfL))&(0xeL))==(0x8L))))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						return translate_cmpb4_zrrci(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_s_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_s_rrrici(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_u_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_u_rrrici(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_rrrici(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_zrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_add_zrrici(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_s_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_s_rrrici(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_u_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_u_rrrici(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_rrrici(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_zrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsl_sub_zrrici(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x2L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_s_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_s_rrrici(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_u_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_u_rrrici(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_rrrici(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_zrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_lsr_add_zrrici(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x0L)) {
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x1L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_s_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_s_rrrici(ctx, &desc);
					}
				}
				if ((((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x1L)))&&((((instruction >> 39) & 0x1L))==(0x0L))) {
					desc.dc = (((instruction >> 40) & 15) << 1);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_u_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_u_rrrici(ctx, &desc);
					}
				}
				if (((((instruction >> 42) & 0x3L))!=(0x3L))&&((((instruction >> 44) & 0x1L))==(0x0L))) {
					desc.rc = (((instruction >> 39) & 31) << 0);
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_rrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_rrrici(ctx, &desc);
					}
				}
				if ((((instruction >> 42) & 0x3L))==(0x3L)) {
					desc.ra = (((instruction >> 34) & 31) << 0);
					if ((((instruction >> 24) & 0xfL))==(0x0L)) {
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_zrri(ctx, &desc);
					}
					if ((((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL)))&&((((instruction >> 24) & 0xfL))!=(0x0L))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_rol_add_zrrici(ctx, &desc);
					}
				}
			}
		}
		if (((((instruction >> 32) & 0x3L))!=(0x3L))&&((((instruction >> 16) & 0x1L))==(0x1L))) {
			desc.db = (((instruction >> 17) & 7) << 0) | (((instruction >> 32) & 3) << 3);
			if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x6L)) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.dc = (((instruction >> 39) & 31) << 0);
					if (((((instruction >> 24) & 0xfL))<(0x2L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
						desc.cc = (((instruction >> 24) & 15) << 0);
						desc.ra = (((instruction >> 34) & 31) << 0);
						desc.pc = (((instruction >> 0) & 65535) << 0);
						desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
						return translate_div_step_rrrici(ctx, &desc);
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0x2L)) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.dc = (((instruction >> 39) & 31) << 0);
					if ((((instruction >> 34) & 0x1fL))==(0x18L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_movd_rrci(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xeL))==(0x4L)) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.dc = (((instruction >> 39) & 31) << 0);
					if ((((instruction >> 34) & 0x1fL))!=(0x18L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							desc.shift = (((instruction >> 20) & 15) << 0) | (((instruction >> 28) & 1) << 4);
							return translate_mul_step_rrrici(ctx, &desc);
						}
					}
				}
			}
			if (((((instruction >> 28) & 0xfL))&(0xfL))==(0xaL)) {
				if ((((instruction >> 42) & 0x3L))!=(0x3L)) {
					desc.dc = (((instruction >> 39) & 31) << 0);
					if ((((instruction >> 34) & 0x1fL))==(0x18L)) {
						desc.ra = (((instruction >> 34) & 31) << 0);
						if (((((instruction >> 24) & 0xfL))<(0x6L))||((((instruction >> 24) & 0xfL))>(0xbL))) {
							desc.cc = (((instruction >> 24) & 15) << 0);
							desc.pc = (((instruction >> 0) & 65535) << 0);
							return translate_swapd_rrci(ctx, &desc);
						}
					}
				}
			}
		}
	}

	return false;
}
