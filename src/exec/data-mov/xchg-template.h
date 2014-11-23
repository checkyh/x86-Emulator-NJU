#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(xchg_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = REG(0);
	REG(0) = REG(reg_code);
	REG(reg_code)=imm;
	print_asm("xchg" str(SUFFIX) "  %%%s,%%%s",REG_NAME(0),REG_NAME(reg_code));
	return 1;
}

make_helper(concat(xchg_r2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm=REG(m.reg);
		REG(m.reg)=REG(m.R_M);
		REG(m.R_M) = imm;
		print_asm("xchg" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 1  + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = REG(m.reg);
		REG(m.reg)=MEM_R(addr);
		MEM_W(addr, imm);
		print_asm("mov" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1 + 1;
	}
}
#include "exec/template-end.h"