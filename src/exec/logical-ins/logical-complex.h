make_helper(concat(concat(logical,_r2rm_), SUFFIX)) {
	logical_give(logical_chooser);
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=(REG(m.R_M)&REG(m.reg));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("%s"str(SUFFIX) " %%%s,%%%s",ins_name, REG_NAME(m.reg), REG_NAME(m.R_M));
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
		print_asm("%s"str(SUFFIX) " %%%s,%s",ins_name, REG_NAME(m.reg), ModR_M_asm);
		return len + 1;
	}
}
#if (logical_chooser==5)	
make_helper(concat(concat(logical,_ei2rm_),SUFFIX)) {				//x6b /r ib 
	logical_give(logical_chooser);
	ModR_M m;
	DATA_TYPE imm,src=0,result=0;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.R_M);
		ei_rm2r
		print_asm("%s"str(SUFFIX) " $0x%x,%%%s",ins_name, src, REG_NAME(m.R_M));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		EX_I(src,imm)
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		ei_rm2rm
		print_asm("%s"str(SUFFIX) " $0x%x,%s", ins_name,imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
#endif
make_helper(concat(concat(logical,_rm2r_), SUFFIX)) {
	logical_give(logical_chooser);
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=(REG(m.reg)&REG(m.R_M));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("%s"str(SUFFIX) " %%%s,%%%s",ins_name, REG_NAME(m.R_M), REG_NAME(m.reg));
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
		print_asm("%s"str(SUFFIX) " %s,%%%s",ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}	
make_helper(concat(concat(logical,_i2r_), SUFFIX)) {
	logical_give(logical_chooser);
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		DATA_TYPE result=(REG(m.reg)&REG(m.R_M));
		if ( result==0) cpu.ZF=1;else cpu.ZF=0;
		if (MSB(result)) cpu.SF=1;else cpu.SF=0;
		PF_check(result)
		cpu.OF=0;
		cpu.CF=0;
		print_asm("%s"str(SUFFIX) " %%%s,%%%s",ins_name, REG_NAME(m.R_M), REG_NAME(m.reg));
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
		print_asm("%s"str(SUFFIX) " %s,%%%s",ins_name, ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}	