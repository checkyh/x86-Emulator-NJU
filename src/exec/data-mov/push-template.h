#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,REG(reg_code));
	print_asm("push" str(SUFFIX) " %%%s", REG_NAME(reg_code));
	return 1;
}

make_helper(concat(push_rm_, SUFFIX)) {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		cpu.esp-=DATA_BYTE;
		DATA_TYPE value=MEM_R(addr);
		MEM_W(cpu.esp,value);
		print_asm("push" str(SUFFIX) " %s", ModR_M_asm);
		return len + 1;
	
}

make_helper(concat(pop_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	MEM_W(cpu.esp,REG(reg_code));
	cpu.esp+=DATA_BYTE;
	print_asm("pop" str(SUFFIX) " %%%s", REG_NAME(reg_code));
	return 1;
}

make_helper(concat(pop_rm_, SUFFIX)) {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr,MEM_R(cpu.esp));
		cpu.esp+=DATA_BYTE;
		print_asm("pop" str(SUFFIX) " %s", ModR_M_asm);
		return len + 1;	
}


#include "exec/template-end.h"
