#include "exec/helper.h"
#include "common.h"
#include "memory.h"
#include "trans-template-start.h"
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	char jump_type[5]={'j',0};
	uint8_t short_addr=instr_fetch(eip+1,1);
	char temp_addr=eip;
	ADDR(temp_addr,short_addr,8)
	switch (jump_ins)
	{
		case (0xeb):jump_type[1]='u';jump_type[2]='m';jump_type[3]='p';
				ADDR(cpu.eip,short_addr,8) //jump 8

		case (0x74):jump_type[1]='e';
				if(cpu.ZF==1) ADDR(cpu.eip,short_addr,8) break;//JE/JZ

		case (0x76):jump_type[1]='b';jump_type[2]='e';
				if(cpu.ZF==1||cpu.CF==1) ADDR(cpu.eip,short_addr,8) break;//JE/JZ

		case (0x7e):jump_type[1]='l';jump_type[2]='e'; if(cpu.ZF==1||cpu.SF!=cpu.OF) ADDR(cpu.eip,short_addr,8) break;//JE/JZ
		default:break;
	}
	print_asm("%s 0x%x",jump_type,temp_addr);
	return 2;
}
#include "trans-template-end.h"