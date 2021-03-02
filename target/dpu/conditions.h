#ifndef DPU_CONDITIONS_H
#define DPU_CONDITIONS_H

typedef enum {
	c_cc = 0,
	e_cc = 1,
	eq_cc = 2,
	false_cc = 3,
	ges_cc = 4,
	geu_cc = 5,
	gts_cc = 6,
	gtu_cc = 7,
	large_cc = 8,
	les_cc = 9,
	leu_cc = 10,
	lts_cc = 11,
	ltu_cc = 12,
	max_cc = 13,
	mi_cc = 14,
	nc_cc = 15,
	nc10_cc = 16,
	nc11_cc = 17,
	nc12_cc = 18,
	nc13_cc = 19,
	nc14_cc = 20,
	nc5_cc = 21,
	nc6_cc = 22,
	nc7_cc = 23,
	nc8_cc = 24,
	nc9_cc = 25,
	neq_cc = 26,
	nmax_cc = 27,
	nov_cc = 28,
	nsh32_cc = 29,
	nz_cc = 30,
	o_cc = 31,
	ov_cc = 32,
	pl_cc = 33,
	se_cc = 34,
	sh32_cc = 35,
	small_cc = 36,
	smi_cc = 37,
	snz_cc = 38,
	so_cc = 39,
	spl_cc = 40,
	sz_cc = 41,
	true_cc = 42,
	xgts_cc = 43,
	xgtu_cc = 44,
	xles_cc = 45,
	xleu_cc = 46,
	xnz_cc = 47,
	xz_cc = 48,
	z_cc = 49,
} unique_condition_code_e;

#define get_acquire_cc(cc) _get_acquire_cc(ctx, cc) 

static inline unique_condition_code_e _get_acquire_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		default:
			return false_cc;
	}
}

#define get_add_cc(cc) _get_add_cc(ctx, cc) 

static inline unique_condition_code_e _get_add_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 18: return ov_cc;
		case 19: return nov_cc;
		case 20: return c_cc;
		case 21: return nc_cc;
		case 22: return nc5_cc;
		case 23: return nc6_cc;
		case 24: return nc7_cc;
		case 25: return nc8_cc;
		case 26: return nc9_cc;
		case 27: return nc10_cc;
		case 28: return nc11_cc;
		case 29: return nc12_cc;
		case 30: return nc13_cc;
		case 31: return nc14_cc;
		default:
			return false_cc;
	}
}

#define get_add_nz_cc(cc) _get_add_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_add_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 18: return ov_cc;
		case 19: return nov_cc;
		case 20: return c_cc;
		case 21: return nc_cc;
		case 22: return nc5_cc;
		case 23: return nc6_cc;
		case 24: return nc7_cc;
		case 25: return nc8_cc;
		case 26: return nc9_cc;
		case 27: return nc10_cc;
		case 28: return nc11_cc;
		case 29: return nc12_cc;
		case 30: return nc13_cc;
		case 31: return nc14_cc;
		default:
			return false_cc;
	}
}

#define get_boot_cc(cc) _get_boot_cc(ctx, cc) 

static inline unique_condition_code_e _get_boot_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_const_cc_ge0(cc) _get_const_cc_ge0(ctx, cc) 

static inline unique_condition_code_e _get_const_cc_ge0(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return pl_cc;
		default:
			return false_cc;
	}
}

#define get_const_cc_geu(cc) _get_const_cc_geu(ctx, cc) 

static inline unique_condition_code_e _get_const_cc_geu(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return geu_cc;
		default:
			return false_cc;
	}
}

#define get_const_cc_zero(cc) _get_const_cc_zero(ctx, cc) 

static inline unique_condition_code_e _get_const_cc_zero(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return z_cc;
		default:
			return false_cc;
	}
}

#define get_count_cc(cc) _get_count_cc(ctx, cc) 

static inline unique_condition_code_e _get_count_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return max_cc;
		case 9: return nmax_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_count_nz_cc(cc) _get_count_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_count_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return max_cc;
		case 9: return nmax_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_div_cc(cc) _get_div_cc(ctx, cc) 

static inline unique_condition_code_e _get_div_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_div_nz_cc(cc) _get_div_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_div_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_ext_sub_set_cc(cc) _get_ext_sub_set_cc(ctx, cc) 

static inline unique_condition_code_e _get_ext_sub_set_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 6: return z_cc;
		case 7: return nz_cc;
		case 10: return xz_cc;
		case 11: return xnz_cc;
		case 33: return true_cc;
		case 34: return z_cc;
		case 35: return nz_cc;
		case 36: return xz_cc;
		case 37: return xnz_cc;
		case 40: return pl_cc;
		case 41: return mi_cc;
		case 44: return sz_cc;
		case 45: return snz_cc;
		case 46: return spl_cc;
		case 47: return smi_cc;
		case 50: return ov_cc;
		case 51: return nov_cc;
		case 52: return ltu_cc;
		case 53: return geu_cc;
		case 54: return lts_cc;
		case 55: return ges_cc;
		case 56: return les_cc;
		case 57: return gts_cc;
		case 58: return leu_cc;
		case 59: return gtu_cc;
		case 60: return xles_cc;
		case 61: return xgts_cc;
		case 62: return xleu_cc;
		case 63: return xgtu_cc;
		default:
			return false_cc;
	}
}

#define get_false_cc(cc) _get_false_cc(ctx, cc) 

static inline unique_condition_code_e _get_false_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		default:
			return false_cc;
	}
}

#define get_imm_shift_cc(cc) _get_imm_shift_cc(ctx, cc) 

static inline unique_condition_code_e _get_imm_shift_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 24: return e_cc;
		case 25: return o_cc;
		case 30: return se_cc;
		case 31: return so_cc;
		default:
			return false_cc;
	}
}

#define get_imm_shift_nz_cc(cc) _get_imm_shift_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_imm_shift_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 24: return e_cc;
		case 25: return o_cc;
		case 30: return se_cc;
		case 31: return so_cc;
		default:
			return false_cc;
	}
}

#define get_log_cc(cc) _get_log_cc(ctx, cc) 

static inline unique_condition_code_e _get_log_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_log_nz_cc(cc) _get_log_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_log_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		default:
			return false_cc;
	}
}

#define get_log_set_cc(cc) _get_log_set_cc(ctx, cc) 

static inline unique_condition_code_e _get_log_set_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 6: return z_cc;
		case 7: return nz_cc;
		case 10: return xz_cc;
		case 11: return xnz_cc;
		default:
			return false_cc;
	}
}

#define get_mul_cc(cc) _get_mul_cc(ctx, cc) 

static inline unique_condition_code_e _get_mul_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 30: return small_cc;
		case 31: return large_cc;
		default:
			return false_cc;
	}
}

#define get_mul_nz_cc(cc) _get_mul_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_mul_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 30: return small_cc;
		case 31: return large_cc;
		default:
			return false_cc;
	}
}

#define get_no_cc(cc) _get_no_cc(ctx, cc) 

static inline unique_condition_code_e _get_no_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		default:
			return false_cc;
	}
}

#define get_release_cc(cc) _get_release_cc(ctx, cc) 

static inline unique_condition_code_e _get_release_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return nz_cc;
		default:
			return false_cc;
	}
}

#define get_shift_cc(cc) _get_shift_cc(ctx, cc) 

static inline unique_condition_code_e _get_shift_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 24: return e_cc;
		case 25: return o_cc;
		case 28: return nsh32_cc;
		case 29: return sh32_cc;
		case 30: return se_cc;
		case 31: return so_cc;
		default:
			return false_cc;
	}
}

#define get_shift_nz_cc(cc) _get_shift_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_shift_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 24: return e_cc;
		case 25: return o_cc;
		case 28: return nsh32_cc;
		case 29: return sh32_cc;
		case 30: return se_cc;
		case 31: return so_cc;
		default:
			return false_cc;
	}
}

#define get_sub_cc(cc) _get_sub_cc(ctx, cc) 

static inline unique_condition_code_e _get_sub_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 18: return ov_cc;
		case 19: return nov_cc;
		case 20: return ltu_cc;
		case 21: return geu_cc;
		case 22: return lts_cc;
		case 23: return ges_cc;
		case 24: return les_cc;
		case 25: return gts_cc;
		case 26: return leu_cc;
		case 27: return gtu_cc;
		case 28: return xles_cc;
		case 29: return xgts_cc;
		case 30: return xleu_cc;
		case 31: return xgtu_cc;
		default:
			return false_cc;
	}
}

#define get_sub_nz_cc(cc) _get_sub_nz_cc(ctx, cc) 

static inline unique_condition_code_e _get_sub_nz_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		case 2: return z_cc;
		case 3: return nz_cc;
		case 4: return xz_cc;
		case 5: return xnz_cc;
		case 8: return pl_cc;
		case 9: return mi_cc;
		case 12: return sz_cc;
		case 13: return snz_cc;
		case 14: return spl_cc;
		case 15: return smi_cc;
		case 18: return ov_cc;
		case 19: return nov_cc;
		case 20: return ltu_cc;
		case 21: return geu_cc;
		case 22: return lts_cc;
		case 23: return ges_cc;
		case 24: return les_cc;
		case 25: return gts_cc;
		case 26: return leu_cc;
		case 27: return gtu_cc;
		case 28: return xles_cc;
		case 29: return xgts_cc;
		case 30: return xleu_cc;
		case 31: return xgtu_cc;
		default:
			return false_cc;
	}
}

#define get_sub_set_cc(cc) _get_sub_set_cc(ctx, cc) 

static inline unique_condition_code_e _get_sub_set_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 6: return z_cc;
		case 7: return nz_cc;
		case 10: return xz_cc;
		case 11: return xnz_cc;
		default:
			return false_cc;
	}
}

#define get_true_cc(cc) _get_true_cc(ctx, cc) 

static inline unique_condition_code_e _get_true_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 1: return true_cc;
		default:
			return false_cc;
	}
}

#define get_true_false_cc(cc) _get_true_false_cc(ctx, cc) 

static inline unique_condition_code_e _get_true_false_cc(DisasContext *ctx, uint32_t condition_code) {
	switch (condition_code) {
		case 0: return false_cc;
		case 1: return true_cc;
		default:
			return false_cc;
	}
}

#endif /* DPU_CONDITIONS_H */
