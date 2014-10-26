#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,REG(reg_code) );
	print_asm("push" str(SUFFIX) " %%%s", REG_NAME(reg_code));
	return 1;
}

make_helper(concat(push_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		cpu.esp-=DATA_BYTE;
		MEM_W(cpu.esp,REG(m.R_M) );
		print_asm("push" str(SUFFIX) " %%%s", REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		cpu.esp-=DATA_BYTE;
		printf("OK1\n");
		MEM_W(cpu.esp,MEM_R(addr) );
		printf("OK2\n");
		print_asm("push" str(SUFFIX) " %s", ModR_M_asm);
		return len + 1;
	}
}

#include "exec/template-end.h"
