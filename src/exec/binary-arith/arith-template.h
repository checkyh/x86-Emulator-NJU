#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"



#ifndef _ARITH_FUNC_
#define _ARITH_FUNC_
DATA_TYPE ex_i(uint8_t imm)
{
	if ((imm) >> ((1 << 3) - 1)){
		if (DATA_BYTE==2) return imm|0x1100;
		if (DATA_BYTE==4) return imm|0x11110000;
	}
	else{
		if (DATA_BYTE==2) return imm&&0x0011;
		if (DATA_BYTE==4) return imm&&0x00001111;
		}
	return 0;
	
}
char ins_name[5]={0};
void *arith_switcher(uint8_t ins,DATA_TYPE* src,DATA_TYPE *dst,uint8_t mod)
{
	sprintf(ins_name,"%s","\0");
	switch(ins)
	{
		case 7:
			sprintf(ins_name,"%s","cmp");
			break;
		default:break;
	}
	return ins_name;
}
#endif
// i r   1

make_helper(concat(arith_i2r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	REG(reg_code) = imm;
	print_asm("cmp" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}
// i rm  1 2
make_helper(concat(arith_ei2rm_, SUFFIX)) 
{
	/*ModR_M m;
	uint8_t imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		DATA_TYPE *ex_imm=ex_i(imm);
		DATA_TYPE *dst_reg=REG(m.R_M);
		arith_switcher(m.reg,ex_imm,dst_reg,0);
		return 1 + DATA_BYTE + 1;
	}*/
	return 0;
}

#include "exec/template-end.h"
