#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "binlogical-run.h"

make_helper(concat(concat(binlogical,_i2rm_),SUFFIX)) {
	binlogical_give(binlogical_chooser);
	ModR_M m;
	DATA_TYPE imm=1;
	 DATA_TYPE src=1;
	 int len_i=0;
	int instes=instr_fetch(eip,1);
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result=0;
	if(m.mod == 3) {
		if (instes!=0xd1&&instes!=0xd0) {imm = instr_fetch(eip + 1 + 1, 1);len_i++;}
		src=imm;
		DATA_TYPE *dst=&REG(m.R_M);		
		switch_r
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(m.R_M));
		return 1 + len_i+1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		if (instes!=0xd1&&instes!=0xd0) {imm = instr_fetch(eip + 1 + 1, 1);len_i++;}
		src=imm;
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		switch_rm
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name,imm, ModR_M_asm);
		return 1+len_i + len;
	}
}
make_helper(concat(concat(binlogical,_cl2rm_),SUFFIX)) {
	binlogical_give(binlogical_chooser);
	ModR_M m;
	 DATA_TYPE src=1;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result=0;
	if(m.mod == 3) {
		src =REG(m.reg);
		DATA_TYPE *dst=&REG(m.R_M);		
		switch_r
		print_asm("%s" str(SUFFIX) " %%%s,%%%s",ins_name,REG_NAME(1), REG_NAME(m.R_M));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		src=REG(m.reg);
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		switch_rm
		print_asm("%s" str(SUFFIX) " %%%s,%s",ins_name,REG_NAME(1), ModR_M_asm);
		return 2+len;
	}
}
#include "exec/template-end.h"
#undef switch_r
#undef switch_rm