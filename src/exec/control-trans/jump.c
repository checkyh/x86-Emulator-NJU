#include "exec/helper.h"
#include "common.h"
#include "memory.h"
#include "trans-template-start.h"
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	char jump_type[5];
	uint8_t short_addr=instr_fetch(eip+1,1);
	uint32_t temp_addr=cpu.eip;
	ADDR(temp_addr,short_addr,8)
	switch (jump_ins)
	{
		case (0xeb):sprintf(jump_type,"%s","jump");
				ADDR(cpu.eip,short_addr,8);break;//jump 8

		case (0x74):sprintf(jump_type,"%s","je");
				if(cpu.ZF==1) ADDR(cpu.eip,short_addr,8) break;//JE/JZ

		case (0x76):sprintf(jump_type,"%s","jbe");
				if(cpu.ZF==1||cpu.CF==1) ADDR(cpu.eip,short_addr,8) break;//Jbe

		case (0x7e):sprintf(jump_type,"%s","jle");
				 if(cpu.ZF==1||cpu.SF!=cpu.OF){ ADDR(cpu.eip,short_addr,8) printf("%x\n",cpu.eip ); break;}//Jle
		default:break;
	}
	print_asm("%s 0x%x",jump_type,temp_addr+2);
	return 2;
}
#include "trans-template-end.h"