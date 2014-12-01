#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jumpff_,SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip+1, 1);
	if(m.mod == 3) {
		cpu.eip=REG(m.R_M)-1;
		print_asm("jump" str(SUFFIX) " *%%%s",REG_NAME(m.R_M));
		return 2 ;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 2, &addr);
		cpu.eip=MEM_R(addr)-len-1;
		print_asm("jump" str(SUFFIX) " *%%%s",ModR_M_asm);
		return len + 1;
	}
	return 1;
}
make_helper(concat(jumpff_ad_,SUFFIX))
{
	printf("jumpff_ad\n");
	return 1;
}
#include "exec/template-end.h"
