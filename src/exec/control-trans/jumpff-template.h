#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(jumpff_,SUFFIX))
{
	ModR_M m;
	m.val = instr_fetch(eip, 1);
	if(m.mod == 3) {
		ADDR(cpu.eip,REG(m.R_M),DATA_BYTE*8) 
		print_asm("jump" str(SUFFIX) " *%%%s",REG_NAME(m.R_M));
		return 1 ;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		ADDR(cpu.eip,MEM_R(addr),DATA_BYTE*8);
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
