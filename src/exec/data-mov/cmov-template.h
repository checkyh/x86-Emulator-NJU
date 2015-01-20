#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
//cmovcc r2rm
#define CMOV_R REG(m.reg)=REG(m.R_M)
#define CMOV_RM REG(m.reg)=MEM_R(addr)
make_helper(concat(cmov_,SUFFIX)){
	int mov_ins = instr_fetch(eip, 1);
	char ins_name[6];
	ModR_M m;
	m.val=instr_fetch(eip+1,1);
	if(m.mod==3)
	{
		switch(mov_ins)
		{
			case(0x44):sprintf(ins_name,"%s","cmove");if(cpu.ZF==1) CMOV_R;break;
			case(0x45):sprintf(ins_name,"%s","cmovne");if(cpu.ZF==0) CMOV_R;break;
			case(0x46):sprintf(ins_name,"%s","cmovbe");if(cpu.CF==1||cpu.ZF==0) CMOV_R;break;
			case(0x47):sprintf(ins_name,"%s","cmova");if (cpu.CF==0&&cpu.ZF==0) CMOV_R;break;
			case(0x48):sprintf(ins_name,"%s","cmovs");if (cpu.SF==1) CMOV_R;break;
			case(0x49):sprintf(ins_name,"%s","cmovns");if (cpu.SF==0) CMOV_R;break;
			case(0x4d):sprintf(ins_name,"%s","cmovge");if (cpu.SF==cpu.OF) CMOV_R;break;
			case(0x4e):sprintf(ins_name,"%s","cmovle");if (cpu.ZF==1||cpu.SF!=cpu.OF) CMOV_R;break;
			case(0x4f):sprintf(ins_name,"%s","cmovg");if (cpu.ZF==0&&cpu.SF==cpu.OF) CMOV_R;break;
			default:printf("%x",cpu.eip);assert(0);
		}
		print_asm("%s"str(SUFFIX)" %%%s %%%s",ins_name,REG_NAME(m.R_M),REG_NAME(m.reg));
		return  2;
	}
	else{
		swaddr_t addr;
		int len=read_ModR_M(eip+1,&addr);
		switch(mov_ins)
		{
			case(0x44):sprintf(ins_name,"%s","cmove");if(cpu.ZF==1) CMOV_RM;break;
			case(0x45):sprintf(ins_name,"%s","cmovne");if(cpu.ZF==0) CMOV_RM;break;
			case(0x46):sprintf(ins_name,"%s","cmovbe");if(cpu.CF==1||cpu.ZF==0) CMOV_RM;break;
			case(0x47):sprintf(ins_name,"%s","cmova");if (cpu.CF==0&&cpu.ZF==0) CMOV_RM;break;
			case(0x48):sprintf(ins_name,"%s","cmovs");if (cpu.SF==1) CMOV_RM;break;
			case(0x49):sprintf(ins_name,"%s","cmovns");if (cpu.SF==0) CMOV_RM;break;
			case(0x4d):sprintf(ins_name,"%s","cmovge");if (cpu.SF==cpu.OF) CMOV_RM;break;
			case(0x4e):sprintf(ins_name,"%s","cmovle");if (cpu.ZF==1||cpu.SF!=cpu.OF) CMOV_RM;break;
			case(0x4f):sprintf(ins_name,"%s","cmovg");if (cpu.ZF==0&&cpu.SF==cpu.OF) CMOV_RM;break;
			default:printf("%x",cpu.eip);assert(0);
		}
		print_asm("%s"str(SUFFIX)" %%%s %s",ins_name,ModR_M_asm,REG_NAME(m.reg));
		return  len+1;
	}
}
#undef CMOV_R
#undef CMOV_RM
#include "exec/template-end.h"