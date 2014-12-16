#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint32_t current_sreg;
make_helper(concat(rep_,SUFFIX))
{
	int ins = instr_fetch(eip+1, 1);
	char struction[40];
	while (REG(1)!=0)
	{
		switch (ins){
		case(0xaa):
		case(0xab):
		sprintf(struction,"%s","stos %eax,[esi]");
		if ((cpu.CR0&0x1)==1){current_sreg=ES;MEM_W((7),MEM_R(REG(0)));}
		else MEM_W(REG(7)+(cpu.ES<<16),MEM_R(REG(0)));
			if(cpu.DF==0) {REG(7)+=DATA_BYTE;REG(0)+=DATA_BYTE;}else 
			{REG(7)-=DATA_BYTE;REG(6)-=DATA_BYTE;}break;
		case(0xa4):
		case(0xa5):
		sprintf(struction,"%s","movs [esi] [edi]");
		if ((cpu.CR0&0x1)==1){current_sreg=ES;MEM_W(REG(7),MEM_R(REG(6)));}
		else MEM_W(REG(7)+(cpu.ES<<16),MEM_R(REG(6)));
			if(cpu.DF==0) {REG(7)+=DATA_BYTE;REG(6)+=DATA_BYTE;}else 
			{REG(7)-=DATA_BYTE;REG(6)-=DATA_BYTE;}break;
		}
		REG(1)-=1;
	}
	print_asm("rep"str(SUFFIX)" %s",struction);
	return 2;
}
#include "exec/template-end.h"