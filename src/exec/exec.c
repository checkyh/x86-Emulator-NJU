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
/* 0x40 */	inv, inv, inv, inv, 
/* 0x44 */	inv, inv, inv, inv,
/* 0x48 */	inv, inv, inv, inv, 
/* 0x4c */	inv, inv, inv, inv, 
/* 0x50 */	push_r_v, push_r_v, push_r_v ,push_r_v, 
/* 0x54 */	push_r_v, push_r_v, push_r_v, push_r_v,
/* 0x58 */	pop_r_v, pop_r_v,pop_r_v,pop_r_v,
/* 0x5c */	pop_r_v,pop_r_v,pop_r_v,pop_r_v,
/* 0x60 */	inv, inv, inv, inv,
/* 0x64 */	inv, inv, data_size, inv,
/* 0x68 */	push_i_v,imul_i2r_v, push_i_b,imul_ei2rm_v, 
/* 0x6c */	inv, inv, inv, inv, 
/* 0x70 */	inv, inv, inv, inv,
/* 0x74 */	j_short, j_short, j_short, j_short,
/* 0x78 */	inv, inv, inv, inv, 
/* 0x7c */	j_short, j_short, j_short, j_short, 
/* 0x80 */	x80_switcher, x81_switcher, nemu_trap, x83_switcher, 
/* 0x84 */	test_r2rm_b, test_r2rm_v, inv, inv, 
/* 0x88 */	mov_r2rm_b, mov_r2rm_v, mov_rm2r_b, mov_rm2r_v,
/* 0x8c */	inv, lea_rm2r_v, inv, inv, 
/* 0x90 */	nop, inv, inv, inv,
/* 0x94 */	inv, inv, inv, inv,
/* 0x98 */	inv, cwd_v, inv, inv, 
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
/* 0xcc */	int3, inv, inv, inv,
/* 0xd0 */	inv, inv, inv, inv,
/* 0xd4 */	inv, inv, inv, inv,
/* 0xd8 */	inv, inv, inv, inv,
/* 0xdc */	inv, inv, inv, inv,
/* 0xe0 */	inv, inv, inv, inv,
/* 0xe4 */	inv, inv, inv, inv,
/* 0xe8 */	call_rel_v, j_short, inv, j_short,
/* 0xec */	inv, inv, inv, inv,
/* 0xf0 */	inv, inv, inv, rep,
/* 0xf4 */	inv, inv, xf6_switcher, xf7_switcher,
/* 0xf8 */	inv, inv, inv, inv,
/* 0xfc */	inv, inv, inv, xff_switcher
};

make_helper(exec) {
	return opcode_table[ instr_fetch(eip, 1) ](eip);
}
