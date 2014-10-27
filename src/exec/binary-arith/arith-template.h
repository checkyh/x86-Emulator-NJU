#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
make_helper(concat(arith_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE src=0;
		src=imm;
		DATA_TYPE *dst=&REG(m.R_M);
		r_r=m.reg;
		switch_r	
		RESULT_check
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE src=0;
		src=imm;
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		r_r=m.reg;
		switch_r_m
		RESULT_check
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name, imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(arith_ei2rm_, SUFFIX)) {
	char ins_name[5]={0};
	ModR_M m;
	uint32_t imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		DATA_TYPE src=0;
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.R_M);
		r_r=m.reg;
		switch_r
		RESULT_check
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,src, REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE src=0;
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		EX_I(src,imm)		
		r_r=m.reg;
		switch_r_m
		RESULT_check
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name,src, ModR_M_asm);
		return len + 1 + 1;
	}
}
make_helper(concat(arith_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE src=0;
		src=REG(m.reg);
		DATA_TYPE *dst=&REG(m.R_M);
		r_r=m.reg;
		switch_r
		RESULT_check
		print_asm("%s" str(SUFFIX) " $0x%%%s,%%%s",ins_name, REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE src=0;
		src=REG(m.reg);
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;	
		r_r=m.reg;
		switch_r_m
		RESULT_check
		print_asm("%s" str(SUFFIX) " $0x%%%s,%s",ins_name, REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(arith_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE src=0;
		src=MEM_R(REG(m.R_M));
		DATA_TYPE *dst=&REG(m.reg);
		r_r=m.reg;
		switch_r
		RESULT_check
		print_asm("%s" str(SUFFIX) " %%%s,%%%s",ins_name, REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE src= MEM_R(addr);
		DATA_TYPE *dst=&REG(m.reg);	
		r_r=m.reg;
		switch_r
		RESULT_check
		print_asm("%s" str(SUFFIX) " %s,%%%s", ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}
#include "exec/template-end.h"

