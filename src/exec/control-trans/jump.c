#include "exec/helper.h"
#include "common.h"
#include "memory.h"
#define ADDR(eip,addr,len)  {switch(len)\
{case 8:if (addr>0x80)eip-=0x100-addr;else eip+=addr;break;\
case 16: if (addr>0x8000)   eip-=0x10000-addr; else eip+=addr; break;\
case 32:if(len==32) {if (addr>0x80000000) eip-=0x100000000-addr;else eip+=addr;}}}
extern char suffix;
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	char jump_type[5];
	uint32_t short_addr=instr_fetch(eip+1,1);
	uint32_t temp_addr=cpu.eip;
	int lens=2;
	switch (jump_ins)
	{	case (0x77):sprintf(jump_type,"%s","ja");ADDR(temp_addr,short_addr,8)  
				if(cpu.CF==0&&cpu.ZF==0) ADDR(cpu.eip,short_addr,8)  break;//ja
		case (0xeb):sprintf(jump_type,"%s","jump");
				ADDR(temp_addr,short_addr,8)
				ADDR(cpu.eip,short_addr,8) break;//jump 8
		case (0xe9):sprintf(jump_type,"%s","jump");
				if (suffix=='l') { short_addr=instr_fetch(eip+1,4);
					ADDR(temp_addr,short_addr,32) ADDR(cpu.eip,short_addr,32) lens+=3;}
					else { short_addr=instr_fetch(eip+1,2);ADDR(temp_addr,short_addr,16) ADDR(cpu.eip,short_addr,16) lens+=1;} break;
		case (0x74):sprintf(jump_type,"%s","je");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.ZF==1) ADDR(cpu.eip,short_addr,8)  break;//JE/JZ
		case (0x75):sprintf(jump_type,"%s","jne");ADDR(temp_addr,short_addr,8)
				if(cpu.ZF==0)  ADDR(cpu.eip,short_addr,8) break;//JNE

		case (0x76):sprintf(jump_type,"%s","jbe");ADDR(temp_addr,short_addr,8)
				if(cpu.ZF==1||cpu.CF==1)  ADDR(cpu.eip,short_addr,8) break;//Jbe

		case (0x7c):sprintf(jump_type,"%s","jl");ADDR(temp_addr,short_addr,8)
				 if(cpu.SF!=cpu.OF) ADDR(cpu.eip,short_addr,8)  break;//Jl
		case (0x7d):sprintf(jump_type,"%s","jge");ADDR(temp_addr,short_addr,8)
				 if(cpu.SF==cpu.OF) ADDR(cpu.eip,short_addr,8)  break;//Jge	 
		case (0x7e):sprintf(jump_type,"%s","jle");ADDR(temp_addr,short_addr,8)
				 if(cpu.ZF==1||cpu.SF!=cpu.OF) ADDR(cpu.eip,short_addr,8)  break;//Jle
		case (0x7f):sprintf(jump_type,"%s","jg");ADDR(temp_addr,short_addr,8)
				 if(cpu.ZF==0 &&cpu.SF==cpu.OF) ADDR(cpu.eip,short_addr,8)  break;//Jle

		default:break;
	}
	print_asm("%s 0x%x",jump_type,temp_addr+lens);
	return lens;
}
make_helper(j_near)
{
	uint32_t temp_addr=cpu.eip;
	uint32_t addr=0;
	int jump_ins = instr_fetch(eip, 1);
	int lens=2;
	char jump_type[5];
	if (suffix=='l') {
		 addr=instr_fetch(eip+1,4);
		ADDR(temp_addr,addr,32)  lens+=3;
	}
	else { 
		addr=instr_fetch(eip+1,2);
		ADDR(temp_addr,addr,16)
		lens+=1;
	}
	int byte=(lens==4)?16:32;
	switch (jump_ins)
	{
		case (0x8f):sprintf(jump_type,"%s","jg");if(cpu.ZF==0 &&cpu.SF==cpu.OF) ADDR(cpu.eip,addr,byte)  break;//Jle
		case(0x8e):sprintf(jump_type,"%s","jle"); if(cpu.ZF==1||cpu.SF!=cpu.OF) ADDR(cpu.eip,addr,byte)  break;//Jle
	}
	print_asm("%s 0x%x",jump_type,temp_addr+lens);
	return  lens;
}
make_helper(jumpff)
{
	return 1;
}

