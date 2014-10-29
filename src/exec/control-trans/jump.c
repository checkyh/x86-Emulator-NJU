#include "exec/helper.h"
#include "common.h"
#include "memory.h"
#include "trans-template-start.h"
extern char suffix;
make_helper (j_short)
{
	int jump_ins = instr_fetch(eip, 1);
	char jump_type[5];
	uint32_t short_addr=instr_fetch(eip+1,1);
	uint32_t temp_addr=cpu.eip;
	int lens=2;
	switch (jump_ins)
	{
		case (0xeb):	printf("OK1\n");sprintf(jump_type,"%s","jump");
				ADDR(temp_addr,short_addr,8)
				ADDR(cpu.eip,short_addr,8) break;//jump 8
		case (0xe9):	printf("OK2\n");sprintf(jump_type,"%s","jump");
				if (suffix=='l') {ADDR(temp_addr,short_addr,32) ADDR(cpu.eip,short_addr,32) lens+=3;}
					else {ADDR(temp_addr,short_addr,16) ADDR(cpu.eip,short_addr,16) lens+=1;} break;
		case (0x74):	printf("OK3\n");sprintf(jump_type,"%s","je");
				if(cpu.ZF==1) { ADDR(temp_addr,short_addr,8) ADDR(cpu.eip,short_addr,8) }break;//JE/JZ
		case (0x75):	printf("OK4\n");sprintf(jump_type,"%s","jne");
				if(cpu.ZF==0) {ADDR(temp_addr,short_addr,8) ADDR(cpu.eip,short_addr,8) }break;//JNE

		case (0x76):	printf("OK5\n");sprintf(jump_type,"%s","jbe");
				if(cpu.ZF==1||cpu.CF==1) {ADDR(temp_addr,short_addr,8) ADDR(cpu.eip,short_addr,8)} break;//Jbe

		case (0x7c):	printf("OK6\n");sprintf(jump_type,"%s","jl");
				 if(cpu.SF!=cpu.OF){ ADDR(temp_addr,short_addr,8) ADDR(cpu.eip,short_addr,8)  }break;//Jl
				 
		case (0x7e):	printf("OK7\n");sprintf(jump_type,"%s","jle");
				 if(cpu.ZF==1||cpu.SF!=cpu.OF){ ADDR(temp_addr,short_addr,8) ADDR(cpu.eip,short_addr,8)  }break;//Jle

		default:break;
	}
	print_asm("%s 0x%x",jump_type,temp_addr+lens);
	return lens;
}
#include "trans-template-end.h"