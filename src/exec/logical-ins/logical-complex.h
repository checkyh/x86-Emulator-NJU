make_helper(concat(concat(logical,_i2r_), SUFFIX)) {
	int reg_code = instr_fetch(eip, 1) & 0x7;
	DATA_TYPE imm = instr_fetch(eip + 1, DATA_BYTE);
	DATA_TYPE result=(REG(reg_code)&imm);
	if ( result==0) cpu.ZF=1;else cpu.ZF=0;
	if (MSB(result)) cpu.SF=1;else cpu.SF=0;
	PF_check(result)
	cpu.OF=0;
	cpu.CF=0;
	print_asm("logical" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(reg_code));
	return DATA_BYTE + 1;
}

make_helper(concat(concat(logical,_r2rm_), SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=(REG(m.R_M)&REG(m.reg));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("logical" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.reg), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE result=(REG(m.reg)&MEM_R(addr));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("logical" str(SUFFIX) " %%%s,%s", REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
#if logical_chooser==4	
make_helper(concat(concat(logical,_ei2rm_),SUFFIX)) {
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE result=(REG(m.R_M)&imm);
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;	
		print_asm("logical" str(SUFFIX) " $0x%x,%%%s", imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE result=(MEM_R(addr)&imm);
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("logical" str(SUFFIX) " $0x%x,%s", imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}

make_helper(concat(concat(logical,_rm2r_), SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=(REG(m.reg)&REG(m.R_M));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("logical" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		DATA_TYPE result=(REG(m.reg)&MEM_R(addr));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("logical" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}	
#endif	