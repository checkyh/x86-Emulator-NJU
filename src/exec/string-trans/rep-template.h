#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(rep_,SUFFIX))
{
	int ins = instr_fetch(eip+1, 1);
	int IncDec=0;
	while (REG(1)!=0)
	{
		switch (ins)
		{
		case (0xa4):	MEM_W(REG(7),MEM_R(REG(6)));
				if(cpu.DF==0) IncDec=DATA_BYTE;else IncDec=-DATA_BYTE;
				REG(7)+=IncDec;
				REG(6)+=IncDec;break;

		}
		REG(1)-=1;
	}
	print_asm("rep movs" str(SUFFIX) "[esi] [edi]");
	return 2;
}
#include "exec/template-end.h"