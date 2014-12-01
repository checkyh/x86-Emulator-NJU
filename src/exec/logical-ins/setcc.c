#define DATA_BYTE 1
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "exec/template-start.h"
make_helper(setcc)
{
	int set_ins = instr_fetch(eip, 1);
	char set_type[6];
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
	switch (set_ins)
	{	
		case (0x90):sprintf(set_type,"%s","setne");if (cpu.ZF==0) REG(m.R_M)=0xff;break;
	}}
	return 1+1;
}
#include "exec/template-end.h"
#undef DATA_BYTE
