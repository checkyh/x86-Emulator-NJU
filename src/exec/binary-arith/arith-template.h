#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(arith_i2r_, SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	//long result;DATA_TYPE result_c;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	REG(reg_code) = imm;

	print_asm("arith" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}

make_helper(concat(arith_i2rm_, SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	long result;DATA_TYPE result_c;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		REG(m.R_M) = imm;
		print_asm("arith" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE src=imm;
		DATA_TYPE *dst=&REG(m.R_M);
		switch(m.reg)
		{
			case 7:sprintf(ins_name,"%s","cmp");
				result_c=(*dst>>1)-(src>>1);
				result=*dst-src;
				RESULT_check
				break;
		}
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name, src, REG_NAME(m.R_M));
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(arith_ei2rm_, SUFFIX)) {
	char ins_name[5]={0};
	ModR_M m;
	uint32_t imm;
	long result;DATA_TYPE result_c;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, 1);
		DATA_TYPE src=0;
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.R_M);
		switch(m.reg)
		{
			case 0:sprintf(ins_name,"%s","add");
				result_c=(*dst>>1)+(src>>1);
				result=*dst+src;
				RESULT_check
				*dst=*dst+src;
				break;
			case 2:sprintf(ins_name,"%s","adc");
				result_c=(*dst>>1)+((src+cpu.CF)>>1);
				result=*dst+src+cpu.CF;
				RESULT_check
				*dst=*dst+src;
				break;
			case 3:sprintf(ins_name,"%s","sbb");
				result_c=(*dst>>1)-((src+cpu.CF)>>1);
				result=*dst-(src+cpu.CF);
				RESULT_check
				*dst=*dst-(src+cpu.CF);
				break;
			case 5:sprintf(ins_name,"%s","sub");
				result_c=(*dst>>1)-(src>>1);
				result=*dst-src;
				RESULT_check
				*dst=*dst-src;
				break;
			case 7:sprintf(ins_name,"%s","cmp");
				result_c=(*dst>>1)-(src>>1);
				result=*dst-src;
				RESULT_check
				break;
		}
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name, src, REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE src=0;
		EX_I(src,imm)		
		switch(m.reg)
		{
			case 0:sprintf(ins_name,"%s","add");
				result_c=(MEM_R(addr)>>1)+(src>>1);
				result=MEM_R(addr)+src;
				RESULT_check
				break;
			case 2:sprintf(ins_name,"%s","adc");
				result_c=(MEM_R(addr)>>1)+((src+cpu.CF)>>1);
				result=MEM_R(addr)+src+cpu.CF;
				RESULT_check
				MEM_W(addr,MEM_R(addr)+src);
				break;
			case 3:sprintf(ins_name,"%s","sbb");
				result_c=(MEM_R(addr)>>1)-((src+cpu.CF)>>1);
				result=MEM_R(addr)-(src+cpu.CF);
				RESULT_check
				MEM_W(addr,MEM_R(addr)-(src+cpu.CF));
				break;
			case 5:sprintf(ins_name,"%s","sub");
				result_c=(MEM_R(addr)>>1)-(src>>1);
				result=MEM_R(addr)-src;
				RESULT_check
				MEM_W(addr,MEM_R(addr)-src);
				break;
			case 7:sprintf(ins_name,"%s","cmp");
				result_c=(MEM_R(addr)>>1)-(src>>1);
				result=MEM_R(addr)-src;
				RESULT_check
				break;
		}
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name, src, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
make_helper(concat(arith_r2rm_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	//long result;DATA_TYPE result_c;
	if(m.mod == 3) {
		REG(m.R_M) = REG(m.reg);
		print_asm("arith" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		MEM_W(addr, REG(m.reg));

		print_asm("arith" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}

make_helper(concat(arith_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	//long result;DATA_TYPE result_c;
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		print_asm("arith" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = MEM_R(addr);

		print_asm("arith" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

make_helper(concat(arith_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	//long result;DATA_TYPE result_c;
	MEM_W(addr, REG(R_EAX));

	print_asm("arith" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(arith_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	//long result;DATA_TYPE result_c;
	REG(R_EAX) = MEM_R(addr);

	print_asm("arith" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}

#include "exec/template-end.h"

