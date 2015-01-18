#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
//cmovcc r2rm
#define CMOV_R REG(m.reg)=REG(m.R_M)
#define CMOV_RM len=read_ModR_M(eip+1,&addr);REG(m.reg)=MEM_R(addr)
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
		}
		print_asm("%s"str(SUFFIX)" %%%s %%%s",ins_name,REG_NAME(m.reg),REG_NAME(m.R_M));
		return  2;
	}
	else{
		swaddr_t addr;
		int len=0;
		switch(mov_ins)
		{
			case(0x44):sprintf(ins_name,"%s","cmove");if(cpu.ZF==1) CMOV_RM;break;
		}
		print_asm("%s"str(SUFFIX)" %%%s %s",ins_name,REG_NAME(m.reg),ModR_M_asm);
		return  len+1;
	}
}
#undef CMOV_R
#undef CMOV_RM
#include "exec/template-end.h"