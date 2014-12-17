#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "logical-run.h"

make_helper(concat(concat(logical,_i2rm_),SUFFIX)) {
	logical_give(logical_chooser);
	ModR_M m;
	DATA_TYPE imm=0;
	 DATA_TYPE src=0;
	 DATA_TYPE *dst=NULL;
	m.val = instr_fetch(eip + 1, 1);
	DATA_TYPE result=0;
	int lens=1;
	if(m.mod == 3) {
		if (logical_chooser==0)
		{
			imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
			src=imm;
			lens+=DATA_BYTE;
		}
		else 
		{
		src=REG(m.R_M);
		dst=&REG(m.R_M);
		}		
		switch_r
		if (logical_chooser==0)
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(m.R_M));
		else print_asm("%s" str(SUFFIX) " %%%s",ins_name,REG_NAME(m.R_M));
		return 1 + lens;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		if (logical_chooser==0)
		{
			imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
			src=imm;
			len+=DATA_BYTE;
		}
		else src=MEM_R(addr);
		DATA_TYPE dst_v=MEM_R(addr);
		DATA_TYPE *dst=&dst_v;
		switch_rm
		if (logical_chooser==0)
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name,imm, ModR_M_asm);
		else  print_asm("%s" str(SUFFIX) " %%%s",ins_name,ModR_M_asm);
		return len + 1 ;
	}
}

#if (logical_chooser==0||logical_chooser==5)
#include "logical-complex.h"
#endif

#include "exec/template-end.h"
#undef switch_r
#undef switch_rm
