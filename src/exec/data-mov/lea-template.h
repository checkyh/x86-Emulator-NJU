#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "cpu/reg.h"
extern uint16_t current_sreg;
make_helper(concat(lea_rm2r_, SUFFIX)) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	if ((cpu.CR0&0x1)==1)
	current_sreg=DS;
	if(m.mod == 3) {
		REG(m.reg) = REG(m.R_M);
		printf("%x\n",REG(m.reg) );
		print_asm("lea" str(SUFFIX) " %%%s,%%%s", REG_NAME(m.R_M), REG_NAME(m.reg));
		return 2;
	}
	else {
		swaddr_t addr;
		int len = read_ModR_M(eip + 1, &addr);
		REG(m.reg) = addr;
		print_asm("lea" str(SUFFIX) " %s,%%%s", ModR_M_asm, REG_NAME(m.reg));
		return len + 1;
	}
}

#include "exec/template-end.h"
