#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(call_, SUFFIX)) {
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
	return 1;
}
#include "exec/template-end.h"