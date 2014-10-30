#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

#define switch_r switch(logical_chooser)\
{case 0:result=src&(*dst);*dst=src&*dst;cpu.CF=0;cpu.OF=0;PF_check(result)  break;}
make_helper(concat(concat(logical,_i2rm_),SUFFIX)) {
	logical_give(logical_chooser);
	ModR_M m;
	DATA_TYPE imm;
	m.val = instr_fetch(eip + 1, 1);
	if(m.mod == 3) {
		imm = instr_fetch(eip + 1 + 1, DATA_BYTE);
		DATA_TYPE src=imm;
		DATA_TYPE result=0;
		DATA_TYPE *dst=&REG(m.R_M);		
		switch_r
		print_asm("%s" str(SUFFIX) " $0x%x,%%%s",ins_name,imm, REG_NAME(m.R_M));
		return 1 + DATA_BYTE + 1;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		imm = instr_fetch(eip + 1 + len, DATA_BYTE);
		DATA_TYPE result=(MEM_R(addr)&imm);
		PF_check(result) 
		print_asm("%s" str(SUFFIX) " $0x%x,%s",ins_name,imm, ModR_M_asm);
		return len + DATA_BYTE + 1;
	}
}
	
#if (logical,_chooser==0)||(logical_chooser==4)
#include "logical-complex.h"
#endif

#include "exec/template-end.h"
#undef logical_give