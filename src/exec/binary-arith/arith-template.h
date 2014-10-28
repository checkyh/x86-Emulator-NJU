#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#ifndef _INS_START_
#define _INS_START_
void ins_give()
{
	switch(arith_chooser)
	{
		case 0:sprintf(ins_name,"%s","add");
		case 1:sprintf(ins_name,"%s","or");
		case 2:sprintf(ins_name,"%s","adc");
		case 3:sprintf(ins_name,"%s","sbb");
		case 4:sprintf(ins_name,"%s","and");
		case 5:sprintf(ins_name,"%s","sub");
		case 6:sprintf(ins_name,"%s","xor");
		case 7:sprintf(ins_name,"%s","cmp");
	}
}
#endif
make_helper(concat(concat(arith,_i2r_), SUFFIX)) {
	ins_give();
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	REG(reg_code) = imm;
	print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}
make_helper(concat(concat(arith,_i2rm_), SUFFIX)) {
	ins_give();
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name, imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("%s" str(SUFFIX) " $0x%x,%s", ins_name,imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(concat(arith,_ei2rm_), SUFFIX)) {
	ins_give();
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s", ins_name,imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name, imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(concat(arith,_r2rm_), SUFFIX)) {
	ins_give();
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("%s" str(SUFFIX) " %%%s,%%%s", ins_name,REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("%s" str(SUFFIX) " %%%s,%s", ins_name,REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(concat(arith,_rm2r_), SUFFIX)) {
	ins_give();
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("%s" str(SUFFIX) " %%%s,%%%s", ins_name,REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);
		
		print_asm("%s" str(SUFFIX) " %s,%%%s",ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
#include "exec/template-end.h"