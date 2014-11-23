#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(call_rel_, SUFFIX)) {
	DATA_TYPE call_addr;
	int lens=1;
	call_addr=instr_fetch(eip+1,DATA_BYTE);
	lens+=DATA_BYTE;
	cpu.esp-=DATA_BYTE;
	MEM_W(cpu.esp, cpu.eip+lens);	
	ADDR(cpu.eip,call_addr,DATA_BYTE*8)
	print_asm("call 0x%x",cpu.eip+lens);	
	return lens;
}
make_helper(concat(call_rm_, SUFFIX)) {		
	ModR_M m;
	DATA_TYPE call_addr;
	int lens=1;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
	call_addr=REG(m.R_M);
	lens+=DATA_BYTE;
	cpu.eip+=call_addr;
	print_asm("call 0x%x",cpu.eip+lens);
	return lens;
	}
	else{
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		call_addr=MEM_R(addr);
		lens+=len;
		cpu.eip+=call_addr;
		print_asm("call 0x%x",cpu.eip+lens);
		return lens;
	}	
}
make_helper(concat(leave_,SUFFIX))
{
	if (DATA_BYTE==2)
	{
		reg_w(R_SP)=reg_w(R_BP);
		reg_w(R_BP)=MEM_R(reg_w(R_SP));
	}
	else
	{
		cpu.esp=cpu.ebp;
		cpu.ebp=MEM_R(cpu.esp);
	}
	print_asm("leave");
	cpu.esp+=DATA_BYTE;
	return 1;
}
make_helper(concat(ret_, SUFFIX)) {
	if (DATA_BYTE==2)
	{
		cpu.eip=(MEM_R(reg_w(R_SP))&0x0000ffff)-1;
	}
	else	
	{
		cpu.eip=MEM_R(cpu.esp)-1;
	}
	print_asm("ret");
	cpu.esp+=DATA_BYTE;	
	return 1;
}
#if DATA_BYTE==2
make_helper(concat(ret_i_, SUFFIX)) {	
	cpu.eip=(MEM_R(cpu.esp)|0x100000)-3;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	cpu.esp+=2+imm;

	print_asm("ret $0x%x",imm);
	return 3;
}
#endif
#include "exec/template-end.h"