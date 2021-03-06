#include "exec/helper.h"

#include "all-instr.h"

typedef int (*helper_fun)(swaddr_t);


/* TODO: Add more instructions!!! */

helper_fun opcode_table [256] = {
/* 0x00 */	add_r2rm_b, add_r2rm_v, add_rm2r_b, add_rm2r_v,
/* 0x04 */	add_i2r_b, add_i2r_v, inv, inv, 
/* 0x08 */	or_r2rm_b, or_r2rm_v, or_rm2r_b, or_rm2r_v, 
/* 0x0c */	or_i2r_b, or_i2r_v,inv, x0f_switcher, 
/* 0x10 */	adc_r2rm_b, adc_r2rm_v, adc_rm2r_b, adc_rm2r_v, 
/* 0x14 */	adc_i2r_b, adc_i2r_v, inv, inv, 
/* 0x18 */	sbb_r2rm_b, sbb_r2rm_v,sbb_rm2r_b, sbb_rm2r_v, 
/* 0x1c */	sbb_i2r_b, sbb_i2r_v,  inv, inv, 
/* 0x20 */	and_r2rm_b, and_r2rm_v, and_rm2r_b, and_rm2r_v, 
/* 0x24 */	and_i2r_b, and_i2r_v, inv, inv,
/* 0x28 */	sub_r2rm_b, sub_r2rm_v,sub_rm2r_b,sub_rm2r_v, 
/* 0x2c */	sub_i2r_b, sub_i2r_v, inv, inv,
/* 0x30 */	xor_r2rm_b,xor_r2rm_v,xor_rm2r_b,xor_rm2r_v, 
/* 0x34 */	xor_i2r_b,xor_i2r_v, inv, inv,
/* 0x38 */	cmp_r2rm_b, cmp_r2rm_v,cmp_rm2r_b,cmp_rm2r_v, 
/* 0x3c */	cmp_i2r_b, cmp_i2r_v, inv, inv,
/* 0x40 */	inc_r_v, inc_r_v, inc_r_v, inc_r_v, 
/* 0x44 */	inc_r_v, inc_r_v, inc_r_v, inc_r_v,
/* 0x48 */	dec_r_v, dec_r_v, dec_r_v, dec_r_v, 
/* 0x4c */	dec_r_v, dec_r_v, dec_r_v, dec_r_v, 
/* 0x50 */	push_r_v, push_r_v, push_r_v ,push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v, pop_r_v,pop_r_v,pop_r_v,
/* 0x5c */	pop_r_v,pop_r_v,pop_r_v,pop_r_v,
/* 0x60 */	pusha_v, popa_v, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v,imul_i2r_v, push_i_v,imul_ei2rm_v, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	j_short, j_short, j_short, j_short,
/* 0x74 */	j_short, j_short, j_short, j_short,
/* 0x78 */	j_short, j_short,j_short, j_short, 
/* 0x7c */	j_short, j_short, j_short, j_short, 
/* 0x80 */	x80_switcher, x81_switcher, nemu_trap, x83_switcher, 
/* 0x84 */	test_r2rm_b, test_r2rm_v, xchg_r2rm_v, xchg_r2rm_b, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, lea_rm2r_v, mov_r2s, inv, 
/* 0x90 */	nop, xchg_r_v, xchg_r_v, xchg_r_v,
/* 0x94 */	xchg_r_v, xchg_r_v, xchg_r_v, xchg_r_v,
/* 0x98 */	xchg_r_v, cwd_v, inv, inv, 
/* 0x9c */	inv, inv, inv, inv, 
/* 0xa0 */	mov_moffs2a_b, mov_moffs2a_v, mov_a2moffs_b, mov_a2moffs_v,
/* 0xa4 */	movs_b, movs_v, inv, inv,
/* 0xa8 */	test_i2r_b, test_i2r_v, inv, inv,
/* 0xac */	inv, inv, inv, inv,
/* 0xb0 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb4 */	mov_i2r_b, mov_i2r_b, mov_i2r_b, mov_i2r_b,
/* 0xb8 */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xbc */	mov_i2r_v, mov_i2r_v, mov_i2r_v, mov_i2r_v, 
/* 0xc0 */	xc0_switcher, xc1_switcher, ret_i_w, ret_v,
/* 0xc4 */	inv, inv, mov_i2rm_b, mov_i2rm_v,
/* 0xc8 */	inv, leave_v, inv, inv,
/* 0xcc */	int3, int_i, inv, iret,
/* 0xd0 */	inv, xd1_switcher, inv, xd3_switcher,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	xd9, xd9, inv, inv,
/* 0xdc */	xdd, xdd, xd9, inv,
/* 0xe0 */	inv, inv, inv, j_short,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	call_rel_v, j_near, jump_far, j_short,
/* 0xec */	in_d2a_b, in_d2a_v, out_a2d_b, out_a2d_v,
/* 0xf0 */	inv, inv, inv, rep,
/* 0xf4 */	hlt, inv, xf6_switcher, xf7_switcher,
/* 0xf8 */	inv, inv, cli, inv,
/* 0xfc */	cld, std, xfe_switcher, xff_switcher
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
