#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(rep_,SUFFIX))
{
	int ins = instr_fetch(eip+1, 1);
	while (REG(1)!=0)
	{
		switch (ins)
		{
		case (0xa5):MEM_W(REG(7),MEM_R(REG(6)));
			if(cpu.DF==0) {REG(7)+=DATA_BYTE;REG(6)+=DATA_BYTE;}else 
			{REG(7)-=DATA_BYTE;REG(6)-=DATA_BYTE;}break;
		case (0xa4):MEM_W(REG(7),MEM_R(REG(6)));
			if(cpu.DF==0) {REG(7)+=DATA_BYTE;REG(6)+=DATA_BYTE;}else 
			{REG(7)-=DATA_BYTE;REG(6)-=DATA_BYTE;}break;

		}
		REG(1)-=1;
	}
	print_asm("rep movs" str(SUFFIX) "[esi] [edi]");
	return 2;
}
#include "exec/template-end.h"