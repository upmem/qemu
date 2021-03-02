/*
 * Copyright (c) 2020 - UPMEM
 */

#ifndef __DPU_TRANSLATE_H__
#define __DPU_TRANSLATE_H__

#include <stdbool.h>
#include "ctxt.h"
#include "desc.h"

bool translate_acquire_rici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_ssi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_sss(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_add_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_addc_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rki(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rki(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_and_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_andn_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_asr_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_boot_rici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_call_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_call_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_call_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_call_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cao_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clo_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clr_run_rici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cls_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_clz_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_cmpb4_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_div_step_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsb_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extsh_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extub_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_extuh_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_fault_i(DisasContext *ctx, __attribute__((unused)) const InstructionDescriptor *descriptor);

bool translate_hash_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_hash_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lbs_s_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lbs_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lbs_ersi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lbu_u_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lbu_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lbu_ersi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ld_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ld_ersi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ldma_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ldmai_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lhs_s_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lhs_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lhs_ersi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lhu_u_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lhu_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lhu_ersi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl1x_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_s_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_s_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_u_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_u_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_zrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_add_zrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_s_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_s_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_u_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_u_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_zrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsl_sub_zrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lslx_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr1x_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_s_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_s_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_u_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_u_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_zrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsr_add_zrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lsrx_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lw_s_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lw_u_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lw_erri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_lw_ersi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_movd_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sh_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_sl_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_uh_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sh_ul_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sh_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_sl_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_uh_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_sl_ul_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_step_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_uh_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_uh_ul_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_uh_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_mul_ul_ul_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nand_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nop_(DisasContext *ctx, __attribute__((unused)) const InstructionDescriptor *descriptor);

bool translate_nor_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nor_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_nxor_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_or_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_orn_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_read_run_rici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_release_rici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_resume_rici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_s_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_s_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_u_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_u_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_rrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_rrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_zrri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rol_add_zrrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_s_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_u_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_ror_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsub_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_rsubc_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_s_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_u_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_rrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_zrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sats_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sb_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sb_erir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sb_esii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sb_esir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sb_id_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sd_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sd_erir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sd_esii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sd_esir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sd_id_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sdma_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sh_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sh_erir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sh_esii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sh_esir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sh_id_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_stop_ci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_ssi(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_sss(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sub_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zirc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zirci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zirf(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_subc_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sw_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sw_erir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sw_esii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sw_esir(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_sw_id_erii(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_swapd_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_tell_ri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_s_r(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_s_rci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_u_r(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_u_rci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_r(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_rci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_z(DisasContext *ctx, __attribute__((unused)) const InstructionDescriptor *descriptor);

bool translate_time_zci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_s_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_s_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_u_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_u_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_rr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_rrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_zr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_time_cfg_zrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_s_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_s_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_s_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_s_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_s_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_s_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_u_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_u_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_u_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_u_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_u_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_u_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_rrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zri(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zric(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zrici(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zrif(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zrr(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zrrc(DisasContext *ctx,  const InstructionDescriptor *descriptor);

bool translate_xor_zrrci(DisasContext *ctx,  const InstructionDescriptor *descriptor);

#endif /* __DPU_TRANSLATE_H__*/

