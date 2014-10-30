#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define ins_give switch(arith_chooser)\
{case 0:sprintf(ins_name,"%s","add");break;\
case 1:sprintf(ins_name,"%s","or");break;\
case 2:sprintf(ins_name,"%s","adc");break;\
case 3:sprintf(ins_name,"%s","sbb");break;\
case 4:sprintf(ins_name,"%s","and");break;\
case 5:sprintf(ins_name,"%s","sub");break;\
case 6:sprintf(ins_name,"%s","xor");break;\
case 7:sprintf(ins_name,"%s","cmp");break;}
#define switch_r switch(arith_chooser)\
{case 0:result=*dst+src; if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;*dst=*dst+src;break;\
 case 1:result=*dst|src;*dst=*dst|src;break;\
 case 2:src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;*dst=*dst+src;break;\
 case 3:src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+(~src);}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}break;\
 case 4:result=(*dst)&(src);*dst=(*dst)&(src);break;\
 case 5:if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+~src;}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}break;\
 case 6:result=*dst^src;*dst=*dst^src;break;\
 case 7:if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}break;}
#define switch_r_m switch(arith_chooser)\
{case 0:result=*dst+src;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;MEM_W(addr,*dst+src);break;\
 case 1:result=*dst|src;MEM_W(addr,*dst|src);break;\
 case 2:src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;MEM_W(addr,*dst+src);break;\
 case 3:src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}break;\
 case 4:result=(*dst)&(src);MEM_W(addr,*dst&src);break;\
 case 5:if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}break;\
 case 6:result=*dst^src;MEM_W(addr,*dst^src);break;\
 case 7:if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}break;}
#define RESULT_check	{if (MSB(result)) cpu.SF=1;else cpu.SF=0;if (result==0) cpu.ZF=1;else cpu.ZF=0;PF_check(result) OF_check(result)}


make_helper(concat(concat(arith,_i2r_), SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	DATA_TYPE result=0;
	DATA_TYPE src=imm;
	DATA_TYPE *dst=&REG(reg_code);
	ins_give
	switch_r
	RESULT_check
	print_asm( "%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}
make_helper(concat(concat(arith,_i2rm_), SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE result=0;
		DATA_TYPE src=imm;
		DATA_TYPE *dst=&REG(m.R_M);
		
	ins_give
	switch_r
		RESULT_check
		print_asm( "%s" str(SUFFIX) " $0x%x,%%%s",ins_name, imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE result=0;
		DATA_TYPE src=imm;
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		
	ins_give
	switch_r_m
		RESULT_check
		print_asm( "%s" str(SUFFIX) " $0x%x,%s", ins_name,imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(concat(arith,_ei2rm_), SUFFIX)) {
	ModR_M m;
	uint8_t imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE result=0;
		DATA_TYPE src=0;
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.R_M);
		
	ins_give
	switch_r
		RESULT_check
		print_asm( "%s" str(SUFFIX) " $0x%x,%%%s", ins_name,src, REG_NAME(m.R_M));
		return 2+1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE result=0;
		DATA_TYPE src=0;
		EX_I(src,imm)
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		
	ins_give
	switch_r_m
		RESULT_check
		print_asm( "%s" str(SUFFIX) " $0x%x,%s",ins_name, src, ModR_M_asm);
		return len +  2;
	}
}
make_helper(concat(concat(arith,_r2rm_), SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=0;
		DATA_TYPE src=REG(m.reg);
		DATA_TYPE *dst=&REG(m.R_M);
		
	ins_give
	switch_r
		RESULT_check
		print_asm( "%s" str(SUFFIX) " %%%s,%%%s", ins_name,REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE result=0;
		DATA_TYPE src=REG(m.reg);
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		
	ins_give
	switch_r_m
		RESULT_check
		print_asm( "%s" str(SUFFIX) " %%%s,%s", ins_name,REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(concat(arith,_rm2r_), SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=0;
		DATA_TYPE src=REG(m.R_M);
		DATA_TYPE *dst=&REG(m.reg);
		
	ins_give
	switch_r
		RESULT_check		
		print_asm( "%s" str(SUFFIX) " %%%s,%%%s", ins_name,REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE result=0;
		DATA_TYPE src=MEM_R(addr);
		DATA_TYPE *dst=&REG(m.reg);
		
	ins_give
	switch_r
		RESULT_check		
		print_asm( "%s" str(SUFFIX) " %s,%%%s",ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
#include "exec/template-end.h"