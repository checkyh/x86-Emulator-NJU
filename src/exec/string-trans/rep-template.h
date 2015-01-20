#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
extern uint32_t current_sreg;
make_helper(concat(rep_,SUFFIX))
{
	int ins = instr_fetch(eip+1, 1);
	while (REG(1)!=0)
	{
		switch (ins){
		case(0xaa):
		swaddr_write(reg_l(7),1,reg_b(0));
		reg_l(7)+=1;break;
		case(0xab):
		 MEM_W(REG(7),REG(0));
		REG(7)+=DATA_BYTE;break;
			
		case(0xa4):
		swaddr_write(reg_l(7),1,swaddr_read(reg_l(6),1));
		if(cpu.DF==0) {reg_l(7)-=1;reg_l(6)-=1;}
		else{reg_l(7)+=1;reg_l(6)+=1;}
		break;
		
		case(0xa5):
		MEM_W(REG(7),MEM_R(REG(6)));
		if(cpu.DF==0) {REG(7)-=DATA_BYTE;REG(6)-=DATA_BYTE;}
		else{REG(7)+=DATA_BYTE;REG(6)+=DATA_BYTE;}break;
		}
		REG(1)-=1;
	}
	switch(ins){
		case(0xaa):case(0xab):	print_asm("rep stos"str(SUFFIX)" eax,[edi]");break;
		case(0xa4):case(0xa5):	print_asm("rep movs"str(SUFFIX)" [esi],[edi]");break;
		default:assert(0);
	}
	return 2;
}
#include "exec/template-end.h"