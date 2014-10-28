#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#define switch_r switch(arith_chooser)\
{case 0:sprintf(ins_name,"%s","add");result=*dst+src; if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;*dst=*dst+src;break;\
 case 1:sprintf(ins_name,"%s","or");result=*dst|src;*dst=*dst|src;break;\
 case 2:sprintf(ins_name,"%s","adc");src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;*dst=*dst+src;break;\
 case 3:sprintf(ins_name,"%s","sbb");src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+(~src);}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}break;\
 case 4:sprintf(ins_name,"%s","and");result=(*dst)&(src);*dst=(*dst)&(src);break;\
 case 5:sprintf(ins_name,"%s","sub");if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+~src;}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}break;\
 case 6:sprintf(ins_name,"%s","xor");result=*dst^src;*dst=*dst^src;break;\
 case 7:sprintf(ins_name,"%s","cmp");if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}break;}
#define switch_r_m switch(arith_chooser)\
{case 0:sprintf(ins_name,"%s","add");result=*dst+src;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;MEM_W(addr,*dst+src);break;\
 case 1:sprintf(ins_name,"%s","or");result=*dst|src;MEM_W(addr,*dst|src);break;\
 case 2:sprintf(ins_name,"%s","adc");src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;MEM_W(addr,*dst+src);break;\
 case 3:sprintf(ins_name,"%s","sbb");src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}break;\
 case 4:sprintf(ins_name,"%s","and");result=(*dst)&(src);MEM_W(addr,*dst&src);break;\
 case 5:sprintf(ins_name,"%s","sub");if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}break;\
 case 6:sprintf(ins_name,"%s","xor");result=*dst^src;MEM_W(addr,*dst^src);break;\
 case 7:sprintf(ins_name,"%s","cmp");if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}break;}


make_helper(concat(concat(arith,_i2r_), SUFFIX)) {
	DATA_TYPE result=0;
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	DATA_TYPE src=imm;
	DATA_TYPE *dst=&REG(reg_code) ;
	switch_r
	print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}
make_helper(concat(concat(arith,_i2rm_), SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name, imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("%s" str(SUFFIX) " $0x%x,%s", ins_name,imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(concat(arith,_ei2rm_), SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s", ins_name,imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		MEM_W(addr, imm);
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name, imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(concat(arith,_r2rm_), SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("%s" str(SUFFIX) " %%%s,%%%s", ins_name,REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("%s" str(SUFFIX) " %%%s,%s", ins_name,REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(concat(arith,_rm2r_), SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("%s" str(SUFFIX) " %%%s,%%%s", ins_name,REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);
		
		print_asm("%s" str(SUFFIX) " %s,%%%s",ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
#include "exec/template-end.h"