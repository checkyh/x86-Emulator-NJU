#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "arith-run.h"

#define RESULT_check	{ZF_check(result) SF_check(result) PF_check(result)}
make_helper(concat(concat(arith,_i2r_), SUFFIX)) {
	arith_give(arith_chooser);
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	DATA_TYPE result=0;
	DATA_TYPE src=imm;
	DATA_TYPE *dst=&REG(0);
	switch_r
	RESULT_check
	print_asm( "%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(0));
	return DATA_BYTE + 1;
}
make_helper(concat(concat(arith,_i2rm_), SUFFIX)) {
	arith_give(arith_chooser);
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE result=0;
		DATA_TYPE src=imm;
		DATA_TYPE *dst=&REG(m.R_M);
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
		switch_rm
		RESULT_check
		print_asm( "%s" str(SUFFIX) " $0x%x,%s", ins_name,imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(concat(arith,_ei2rm_), SUFFIX)) {
	arith_give(arith_chooser);
	ModR_M m;
	uint8_t imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE result=0;
		DATA_TYPE src=0;
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.R_M);
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
		switch_rm
		RESULT_check
		print_asm( "%s" str(SUFFIX) " $0x%x,%s",ins_name, src, ModR_M_asm);
		return len +  2;
	}
}
make_helper(concat(concat(arith,_r2rm_), SUFFIX)) {
	arith_give(arith_chooser);
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=0;
		DATA_TYPE src=REG(m.reg);
		DATA_TYPE *dst=&REG(m.R_M);
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
		switch_rm
		RESULT_check
		print_asm( "%s" str(SUFFIX) " %%%s,%s", ins_name,REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
make_helper(concat(concat(arith,_rm2r_), SUFFIX)) {
	arith_give(arith_chooser);
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=0;
		DATA_TYPE src=REG(m.R_M);
		DATA_TYPE *dst=&REG(m.reg);
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
		switch_r
		printf("%x\n",result );
		RESULT_check		
		print_asm( "%s" str(SUFFIX) " %s,%%%s",ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
#include "exec/template-end.h"
#undef switch_r
#undef switch_rm
#undef RESULT_check