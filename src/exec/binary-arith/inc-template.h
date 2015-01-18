#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define RESULT_check	{ZF_check(result) SF_check(result) PF_check(result)}

make_helper(concat(inc_r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE src=1,dst=0,result=0;
	dst=REG(reg_code);
	result=dst+1;
	if(result<dst||result<src) cpu.CF=1;else cpu.CF=0;
	if((MSB(src)&&MSB(dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(dst)==0&&MSB(result)))
	cpu.OF=1;else cpu.OF=0;
	RESULT_check
	REG(reg_code)=result;
	print_asm("inc" str(SUFFIX) " %%%s", REG_NAME(reg_code));
	return 1;
}
make_helper(concat(inc_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE src=1,dst=0,result=0;
		dst=REG(m.R_M);
		result=dst+1;
		if(result<dst||result<src) cpu.CF=1;else cpu.CF=0;
		if((MSB(src)&&MSB(dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(dst)==0&&MSB(result)))
		cpu.OF=1;else cpu.OF=0;
		RESULT_check
		REG(m.R_M)=result;
		print_asm("mov" str(SUFFIX) " %%%s",  REG_NAME(m.R_M));
		return 1  + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE src=1,dst=0,result=0;
		dst=MEM_R(addr);
		result=dst+1;
		if(result<dst||result<src) cpu.CF=1;else cpu.CF=0;
		if((MSB(src)&&MSB(dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(dst)==0&&MSB(result)))
		cpu.OF=1;else cpu.OF=0;
		RESULT_check
		MEM_W(addr, result);
		print_asm("inc" str(SUFFIX) " %s", ModR_M_asm);
		return len  + 1;
	}
}
make_helper(concat(dec_rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE src=1,dst=0,result=0;
		dst=REG(m.R_M);
		result=dst-1;
		if(result<dst||result<src) cpu.CF=1;else cpu.CF=0;
		if((MSB(src)&&MSB(dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(dst)==0&&MSB(result)))
		cpu.OF=1;else cpu.OF=0;
		RESULT_check
		REG(m.R_M)=result;
		print_asm("dec" str(SUFFIX) " %%%s",  REG_NAME(m.R_M));
		return 1  + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE src=1,dst=0,result=0;
		dst=MEM_R(addr);
		result=dst-1;
		if(result<dst||result<src) cpu.CF=1;else cpu.CF=0;
		if((MSB(src)&&MSB(dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(dst)==0&&MSB(result)))
		cpu.OF=1;else cpu.OF=0;
		RESULT_check
		MEM_W(addr, result);
		print_asm("dec" str(SUFFIX) " %s", ModR_M_asm);
		return len  + 1;
	}
}
#include "exec/template-end.h"
