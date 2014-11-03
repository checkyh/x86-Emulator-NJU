#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_i_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,imm);
	print_asm("push" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(reg_code));
	return 1+DATA_BYTE;
}

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,REG(reg_code));
	print_asm("push" str(SUFFIX) " %%%s", REG_NAME(reg_code));
	return 1;
}
#if DATA_BYTE!=1
make_helper(concat(push_rm_, SUFFIX)) {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		cpu.esp-=DATA_BYTE;
		if (addr<0x8000000)
		MEM_W(cpu.esp,MEM_R(addr));
		else MEM_W(cpu.esp,0);
		print_asm("push" str(SUFFIX) " %s", ModR_M_asm);
		return len + 1+1;
}
#endif
make_helper(concat(pop_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	REG(reg_code)=MEM_R(cpu.esp);
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
