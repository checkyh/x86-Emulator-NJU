#if (logical_chooser==0)
make_helper(concat(test_i2r_,SUFFIX)) {
	return 0;
}
#endif

#if (logical_chooser==5)//imul  	i*rm->r 	ei*rm->rm
make_helper(concat(imul_i2r_, SUFFIX)) {
	logical_give(logical_chooser);
	DATA_TYPE imm,src=0,result=0;
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		src=imm;
		DATA_TYPE *dst=&REG(m.reg);
		concat(imul,DATA_BYTE)(dst,src,REG(m.R_M));
		Unused(result)
		print_asm("%s"str(SUFFIX) "  $0x%x,%%%s,%%%s",ins_name,imm,REG_NAME(m.R_M),REG_NAME(m.reg));
		return DATA_BYTE+1+1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		src=imm;
		DATA_TYPE *dst=&REG(m.reg);
		concat(imul,DATA_BYTE)(dst,src,MEM_R(addr));
		Unused(result) 		
		print_asm("%s"str(SUFFIX) "  $0x%x,%s,%%%s",ins_name,imm, ModR_M_asm,REG_NAME(m.reg));
		return len + DATA_BYTE+1;
	}
}
make_helper(concat(imul_ei2rm_,SUFFIX)) {				//x6b /r ib 
	logical_give(logical_chooser);
	ModR_M m;
	DATA_TYPE imm,src=0,result=0;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.reg);
		concat(imul,DATA_BYTE)(dst,src,REG(m.R_M));
		Unused(result)
		print_asm("%s"str(SUFFIX) "  $0x%x,%%%s,%%%s",ins_name,imm,REG_NAME(m.R_M),REG_NAME(m.reg));
		return 1 + 1 + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		EX_I(src,imm)
		DATA_TYPE *dst=&REG(m.reg);
		concat(imul,DATA_BYTE)(dst,src,MEM_R(addr));
		Unused(result)
		print_asm("%s"str(SUFFIX) "  $0x%x,%s,%%%s",ins_name,imm, ModR_M_asm,REG_NAME(m.reg));
		return len + 1 + 1;
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
make_helper(concat(concat(logical,_r2rm_), SUFFIX)) {
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