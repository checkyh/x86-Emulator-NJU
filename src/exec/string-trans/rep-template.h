#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint32_t current_sreg;
make_helper(concat(rep_,SUFFIX))
{
	uint32_t temp;
	int ins = instr_fetch(eip+1, 1);
	while (REG(1)!=0)
	{
		switch (ins){
		case(0xaa):
		case(0xab):
		if ((cpu.CR0&0x1)==1){current_sreg=ES;MEM_W((7),REG(0));}
		else MEM_W(REG(7)+(cpu.ES<<16),REG(0));break;
		case(0xa4):
		case(0xa5):
		if ((cpu.CR0&0x1)==1){current_sreg=DS;temp=MEM_R(REG(6));current_sreg=ES;MEM_W(REG(7),temp);}
		else MEM_W(REG(7)+(cpu.ES<<16),MEM_R((cpu.ES<<16)+REG(6)));
			if(cpu.DF==0) {REG(7)+=DATA_BYTE;REG(6)+=DATA_BYTE;}else 
			{REG(7)-=DATA_BYTE;REG(6)-=DATA_BYTE;}break;
		}
		REG(1)-=1;
	}
	switch(ins){
		case(0xaa):case(0xab):	print_asm("rep stos"str(SUFFIX)" eax,[edi]");break;
		case(0xa4):case(0xa5):	print_asm("rep movs"str(SUFFIX)" [esi],[edi]");break;
		assert(0);
	}
	return 2;
}
#include "exec/template-end.h"