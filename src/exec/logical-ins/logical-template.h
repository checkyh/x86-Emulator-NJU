#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"

make_helper(concat(concat(logical,_i2rm_),SUFFIX)) {
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
	
#if (logical,_chooser==0)||(logical_chooser==4)
#include "logical-complex.h"
#endif

#include "exec/template-end.h"
