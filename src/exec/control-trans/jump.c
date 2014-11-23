#include "exec/helper.h"
#include "common.h"
#include "memory.h"
#define ADDR(eip,addr,len)  {switch(len)\
{case 8:if (addr>=0x80)eip-=0x100-addr;else eip+=addr;break;\
case 16: if (addr>=0x8000)   eip-=0x10000-addr; else eip+=addr; break;\
case 32:if(len==32) {if (addr>=0x80000000) eip-=0x100000000-addr;else eip+=addr;}}}
extern char suffix;
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	char jump_type[5];
	uint32_t short_addr=instr_fetch(eip+1,1);
	uint32_t temp_addr=cpu.eip;
	int lens=2;
	switch (jump_ins)
	{	case (0xe3):
		if (suffix=='l')   {  sprintf(jump_type,"%s","jecx");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.ecx==1) ADDR(cpu.eip,short_addr,8) }
		else {	sprintf(jump_type,"%s","jcx");
			ADDR(temp_addr,short_addr,8) 
			if(reg_w(1)==1) ADDR(cpu.eip,short_addr,8)}break;
		case (0xeb):sprintf(jump_type,"%s","jump");ADDR(temp_addr,short_addr,8)
				ADDR(cpu.eip,short_addr,8) break;//jump 8
		case (0xe9):sprintf(jump_type,"%s","jump");
				if (suffix=='l') { short_addr=instr_fetch(eip+1,4);
					ADDR(temp_addr,short_addr,32) ADDR(cpu.eip,short_addr,32) lens+=3;}
					else { short_addr=instr_fetch(eip+1,2);ADDR(temp_addr,short_addr,16) ADDR(cpu.eip,short_addr,16) lens+=1;} break;
		case (0x70):sprintf(jump_type,"%s","jo");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.OF==1) ADDR(cpu.eip,short_addr,8)  break;
		case (0x71):sprintf(jump_type,"%s","jno");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.OF==0) ADDR(cpu.eip,short_addr,8)  break;
		case (0x72):sprintf(jump_type,"%s","jnae");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.CF==1) ADDR(cpu.eip,short_addr,8)  break;
		case (0x73):sprintf(jump_type,"%s","jae");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.CF==0) ADDR(cpu.eip,short_addr,8)  break;//JAE
		case (0x74):sprintf(jump_type,"%s","je");
				ADDR(temp_addr,short_addr,8) 
				if(cpu.ZF==1) ADDR(cpu.eip,short_addr,8)  break;//JE/JZ
		case (0x75):sprintf(jump_type,"%s","jne");ADDR(temp_addr,short_addr,8)
				if(cpu.ZF==0)  ADDR(cpu.eip,short_addr,8) break;//JNE
		case (0x76):sprintf(jump_type,"%s","jbe");ADDR(temp_addr,short_addr,8)
				if(cpu.ZF==1||cpu.CF==1)  ADDR(cpu.eip,short_addr,8) break;//Jbe
		case (0x77):sprintf(jump_type,"%s","ja");ADDR(temp_addr,short_addr,8)  
				if(cpu.CF==0&&cpu.ZF==0) ADDR(cpu.eip,short_addr,8)  break;//ja
		case (0x78):sprintf(jump_type,"%s","js");ADDR(temp_addr,short_addr,8)  
				if(cpu.SF==1) ADDR(cpu.eip,short_addr,8)  break;
		case (0x79):sprintf(jump_type,"%s","jns");ADDR(temp_addr,short_addr,8)  
				if(cpu.SF==0) ADDR(cpu.eip,short_addr,8)  break;
		case (0x7a):sprintf(jump_type,"%s","jp");ADDR(temp_addr,short_addr,8)
				 if(cpu.PF==1) ADDR(cpu.eip,short_addr,8)  break;
		case (0x7b):sprintf(jump_type,"%s","jpo");ADDR(temp_addr,short_addr,8)
				 if(cpu.PF==0) ADDR(cpu.eip,short_addr,8)  break;
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
		case(0x80):sprintf(jump_type,"%s","jo"); if(cpu.OF==1) ADDR(cpu.eip,addr,byte)  break;
		case(0x81):sprintf(jump_type,"%s","jno"); if(cpu.OF==0) ADDR(cpu.eip,addr,byte)  break;
		case(0x82):sprintf(jump_type,"%s","jnae"); if(cpu.CF==1) ADDR(cpu.eip,addr,byte)  break;
		case(0x83):sprintf(jump_type,"%s","jnb"); if(cpu.CF==0) ADDR(cpu.eip,addr,byte)  break;
		case(0x84):sprintf(jump_type,"%s","jz"); if(cpu.ZF==1) ADDR(cpu.eip,addr,byte)  break;
		case(0x85):sprintf(jump_type,"%s","jne"); if(cpu.ZF==0) ADDR(cpu.eip,addr,byte)  break;
		case(0x86):sprintf(jump_type,"%s","jna"); if(cpu.CF==1||cpu.ZF==1) ADDR(cpu.eip,addr,byte)  break;
		case(0x87):sprintf(jump_type,"%s","ja"); if(cpu.CF==0&&cpu.ZF==0) ADDR(cpu.eip,addr,byte)  break;
		case(0x88):sprintf(jump_type,"%s","js"); if(cpu.SF==1) ADDR(cpu.eip,addr,byte)  break;
		case(0x89):sprintf(jump_type,"%s","jns"); if(cpu.SF==0) ADDR(cpu.eip,addr,byte)  break;
		case(0x8a):sprintf(jump_type,"%s","jp"); if(cpu.PF==1) ADDR(cpu.eip,addr,byte)  break;
		case(0x8b):sprintf(jump_type,"%s","jpo"); if(cpu.PF==0) ADDR(cpu.eip,addr,byte)  break;
		case(0x8f):sprintf(jump_type,"%s","jg");if(cpu.ZF==0 &&cpu.SF==cpu.OF) ADDR(cpu.eip,addr,byte)  break;//Jg
		case(0x8e):sprintf(jump_type,"%s","jle"); if(cpu.ZF==1||cpu.SF!=cpu.OF) ADDR(cpu.eip,addr,byte)  break;//Jle
		case(0x8c):sprintf(jump_type,"%s","jl"); if(cpu.SF!=cpu.OF) ADDR(cpu.eip,addr,byte)  break;//Jl
	}
	print_asm("%s 0x%x",jump_type,temp_addr+lens);
	return  lens;
}
#undef ADDR
