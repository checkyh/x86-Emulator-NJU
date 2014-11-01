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
	if (DATA_BYTE==2) cpu.eip=(cpu.eip+call_addr)&0x0000ffff;
	else cpu.eip+=call_addr;
	print_asm("call 0x%x",cpu.eip+lens);	
	return lens;
}
make_helper(concat(call_rm_, SUFFIX)) {			//unfinished
	DATA_TYPE call_addr;
	int lens=1;
	call_addr=instr_fetch(eip+1,DATA_BYTE);lens+=DATA_BYTE;cpu.eip+=call_addr;
	print_asm("call 0x%x",cpu.eip+lens);	
	return lens;
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
	cpu.eip=MEM_R(cpu.esp)-3;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	ADDR(cpu.eip,imm,32)
	printf("%x\n",cpu.eip );
	print_asm("ret $0x%x",imm);
	return 3;
}
#endif
#include "exec/template-end.h"