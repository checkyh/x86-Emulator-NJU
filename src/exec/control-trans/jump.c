#include "exec/helper.h"
#include "common.h"
#include "memory.h"
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	int lens=0;
	char jump_type[5]={'J',0};
	int short_addr=lens+=instr_fetch(eip+1,1);
	switch (jump_ins)
	{
		case (0x74):if(cpu.ZF==1){ jump_type[1]='E';lens+=short_addr; }break;//JE/JZ
		default:break;
	}
	lens+=2;
	print_asm("%s" ,jump_type);	
	return lens;
}