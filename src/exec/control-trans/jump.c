#include "exec/helper.h"
#include "common.h"
#include "memory.h"
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	int lens=0;
	char jump_type[5]={'j',0};
	int short_addr=instr_fetch(eip+1,1);
	switch (jump_ins)
	{
		case (0xeb):jump_type[1]='u';jump_type[2]='m';jump_type[3]='p';cpu.eip+=short_addr; //jump 8

		case (0x74):jump_type[1]='e';if(cpu.ZF==1) cpu.eip+=short_addr; break;//JE/JZ

		case (0x76):jump_type[1]='b';jump_type[2]='e'; if(cpu.ZF==1||cpu.CF==1) cpu.eip+=short_addr; break;//JE/JZ
		default:break;
	}
	print_asm("%s 0x%x",jump_type,cpu.eip+2);	
	lens+=2;
	return lens;
}