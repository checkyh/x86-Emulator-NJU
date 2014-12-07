#include "exec/helper.h"

#define DATA_BYTE 1
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "mov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "mov-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(mov_i2r_v) {
	return (suffix == 'l' ? mov_i2r_l(eip) : mov_i2r_w(eip));
}

make_helper(mov_i2rm_v) {
	return (suffix == 'l' ? mov_i2rm_l(eip) : mov_i2rm_w(eip));
}

make_helper(mov_r2rm_v) {
	return (suffix == 'l' ? mov_r2rm_l(eip) : mov_r2rm_w(eip));
}

make_helper(mov_rm2r_v) {
	return (suffix == 'l' ? mov_rm2r_l(eip) : mov_rm2r_w(eip));
}

make_helper(mov_a2moffs_v) {
	return (suffix == 'l' ? mov_a2moffs_l(eip) : mov_a2moffs_w(eip));
}

make_helper(mov_moffs2a_v) {
	return (suffix == 'l' ? mov_moffs2a_l(eip) : mov_moffs2a_w(eip));
}

make_helper(movsb_v) {
	return (suffix == 'l' ? movsb_l(eip) : movsb_w(eip));
}
make_helper(movzb_v) {
	return (suffix == 'l' ? movzb_l(eip) : movzb_w(eip));
}
make_helper(movs_v) {
	return (suffix == 'l' ? movs_l(eip) : movs_w(eip));
}

//mov to/from special registers
#define DATA_BYTE 4
#include "exec/template-start.h"
make_helper(mov_c2r)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.R_M)
	{
		case (0x0):REG(m.reg)=cpu.CR0;break;
		case (0x1):REG(m.reg)=cpu.CR1;break;
		case (0x2):REG(m.reg)=cpu.CR2;break;
		case (0x3):REG(m.reg)=cpu.CR3;break;
	}
	print_asm("mov %%cr%x,%%%s",m.R_M,REG_NAME(m.reg));
	return 2;
}
make_helper(mov_r2c)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.R_M)
	{
		case (0x0):cpu.CR0=REG(m.reg);break;
		case (0x1):cpu.CR1=REG(m.reg);break;
		case (0x2):cpu.CR2=REG(m.reg);break;
		case (0x3):cpu.CR3=REG(m.reg);break;
	}
	print_asm("mov %%%s,%%cr%x",REG_NAME(m.reg),m.R_M);
	return 2;
}
make_helper(mov_r2s)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	char seg_name[2];
	uint32_t base=base_read(REG(m.R_M)>>3);
	switch(m.reg)
	{
		case (ES):sprintf(seg_name,"%s","es");segments[ES].base=base;cpu.ES=REG(m.R_M);break;
		case (CS):sprintf(seg_name,"%s","cs");segments[CS].base=base;cpu.CS=REG(m.R_M);break;
		case (SS):sprintf(seg_name,"%s","ss");segments[SS].base=base;cpu.SS=REG(m.R_M);break;
		case (DS):sprintf(seg_name,"%s","ds");segments[DS].base=base;cpu.DS=REG(m.R_M);break;
	}
	print_asm("mov %%%s,%%%s",REG_NAME(m.R_M),seg_name);
	return 2;
}

#include "exec/template-end.h"
#undef DATA_BYTE