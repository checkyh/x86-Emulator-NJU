#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(push_i_, SUFFIX)) {
	int len=0;DATA_TYPE imm=0;
	uint8_t ins=instr_fetch(eip,1);
	if (ins==0x6a)
	{ imm= instr_fetch(eip+1,1);len=1;}
	else {imm = instr_fetch(eip + 1, DATA_BYTE);len=DATA_BYTE;}
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,imm);
	print_asm("push" str(SUFFIX) " $0x%x", imm);
	return 1+len;
}

make_helper(concat(push_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	if (reg_code!=4){
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp,REG(reg_code));
	}
	else{
		DATA_TYPE temp_esp=cpu.esp;
		cpu.esp-=DATA_BYTE;
		MEM_W(cpu.esp,temp_esp);
	}
	print_asm("push" str(SUFFIX) " %%%s", REG_NAME(reg_code));
	return 1;
}
#if DATA_BYTE!=1
make_helper(concat(push_rm_, SUFFIX)) {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		cpu.esp-=DATA_BYTE;
		MEM_W(cpu.esp,MEM_R(addr));
		print_asm("push" str(SUFFIX) " %s", ModR_M_asm);
		return len + 1;
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

make_helper(concat(pusha_,SUFFIX)){
	int i=0;
	uint32_t origin_esp=cpu.esp;
	for (i=0;i<=7;i++)
	{
		cpu.esp-=DATA_BYTE;
		if (i!=4)MEM_W(cpu.esp,REG(i));
		else MEM_W(cpu.esp,origin_esp);
	}
	print_asm("pusha"str(SUFFIX));
	return 1;
}
make_helper(concat(popa_,SUFFIX)){
	int i=0;
	for (i=7;i>=0;i--)
	{
		if (i!=4) REG(i)=MEM_R(cpu.esp);
		cpu.esp+=DATA_BYTE;
	}
	print_asm("popa"str(SUFFIX));
	return 1;
}
#include "exec/template-end.h"
