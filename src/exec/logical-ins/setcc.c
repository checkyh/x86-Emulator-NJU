#define DATA_BYTE 1
#include "exec/helper.h"
#include "cpu/modrm.h"
#include "exec/template-start.h"
make_helper(setcc)
{
	int set_ins = instr_fetch(eip, 1);
	char set_type[6];
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
	switch (set_ins)
	{	
		case (0x90):sprintf(set_type,"%s","seto");if (cpu.OF==1) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x91):sprintf(set_type,"%s","setno");if (cpu.OF==0) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x92):sprintf(set_type,"%s","setb");if (cpu.CF==1) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x93):sprintf(set_type,"%s","setae");if (cpu.CF==0) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x94):sprintf(set_type,"%s","sete");if (cpu.ZF==1) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x95):sprintf(set_type,"%s","setne");if (cpu.ZF==0) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x96):sprintf(set_type,"%s","setna");if (cpu.ZF==1||cpu.CF==1) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x97):sprintf(set_type,"%s","seta");if (cpu.ZF==0&&cpu.CF==0) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x98):sprintf(set_type,"%s","sets");if (cpu.SF==1) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x99):sprintf(set_type,"%s","setns");if (cpu.SF==0) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x9a):sprintf(set_type,"%s","setp");if (cpu.PF==1) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x9b):sprintf(set_type,"%s","setnp");if (cpu.PF==0) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x9c):sprintf(set_type,"%s","setl");if (cpu.SF!=cpu.OF) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x9d):sprintf(set_type,"%s","setnl");if (cpu.SF==cpu.OF) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x9e):sprintf(set_type,"%s","setle");if (cpu.ZF==1||cpu.OF==cpu.SF) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
		case (0x9f):sprintf(set_type,"%s","setnle");if (cpu.ZF==1&&cpu.OF==cpu.SF) REG(m.R_M)=0xff;else REG(m.R_M)=0x00;break;
	}
	print_asm("%s" str(SUFFIX) " %%%s", set_type, REG_NAME(m.R_M));
	return 1+1;
	}
	else
	{
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		switch (set_ins)
	{	
		case (0x90):sprintf(set_type,"%s","seto");if (cpu.OF==1) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x91):sprintf(set_type,"%s","setno");if (cpu.OF==0) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x92):sprintf(set_type,"%s","setb");if (cpu.CF==1) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x93):sprintf(set_type,"%s","setae");if (cpu.CF==0) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x94):sprintf(set_type,"%s","sete");if (cpu.ZF==1) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x95):sprintf(set_type,"%s","setne");if (cpu.ZF==0) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x96):sprintf(set_type,"%s","setna");if (cpu.ZF==1||cpu.CF==1) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x97):sprintf(set_type,"%s","seta");if (cpu.ZF==0&&cpu.CF==0) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x98):sprintf(set_type,"%s","sets");if (cpu.SF==1) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x99):sprintf(set_type,"%s","setns");if (cpu.SF==0) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x9a):sprintf(set_type,"%s","setp");if (cpu.PF==1) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x9b):sprintf(set_type,"%s","setnp");if (cpu.PF==0) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x9c):sprintf(set_type,"%s","setl");if (cpu.SF!=cpu.OF) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x9d):sprintf(set_type,"%s","setnl");if (cpu.SF==cpu.OF) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x9e):sprintf(set_type,"%s","setle");if (cpu.ZF==1||cpu.OF==cpu.SF) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
		case (0x9f):sprintf(set_type,"%s","setnle");if (cpu.ZF==1&&cpu.OF==cpu.SF) MEM_W(addr,0xff);else MEM_W(addr,0x00);break;
	}
	print_asm("%s" str(SUFFIX) " %s", set_type, ModR_M_asm);
	return len+1;
	}
}
#include "exec/template-end.h"
#undef DATA_BYTE
