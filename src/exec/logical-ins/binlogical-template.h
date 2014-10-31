#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "binlogical-run.h"

make_helper(concat(concat(binlogical,_i2rm_),SUFFIX)) {
	binlogical_give(binlogical_chooser);
	ModR_M m;
	DATA_TYPE imm=0;
	 DATA_TYPE src=0;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result=0;
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		src=imm;
		DATA_TYPE *dst=&REG(m.R_M);		
		switch_r
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(m.R_M));
		return 1 + 1+1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		src=imm;
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		switch_rm
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name,imm, ModR_M_asm);
		return 1+1 + len;
	}
}
#include "exec/template-end.h"
#undef switch_r
#undef switch_rm