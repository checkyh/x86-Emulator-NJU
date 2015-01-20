#include "exec/helper.h"
#include "cpu/modrm.h"

make_helper(xdd)//xdd xdc
{
	ModR_M m;
	int len=0;
	swaddr_t addr;
	m.val = instr_fetch(eip + 1, 1);
	if (m.mod==3)	len=2;
	else len=read_ModR_M(eip+1,&addr)+1;
	print_asm("nop *%d",len);
	return len;
}
make_helper(xd9)//xde xd8
{
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	print_asm("nop *2");
	if (m.reg!=0) return 2;
	assert(0);
}

