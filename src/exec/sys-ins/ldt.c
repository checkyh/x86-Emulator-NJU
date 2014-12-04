/*(* instruction is LGDT *)
IF OperandSize  16
THEN 
GDTR(Limit)  SRC[0:15];
GDTR(Base)  SRC[16:47] AND 00FFFFFFH; 
ELSE (* 32-bit Operand Size *)
GDTR(Limit)  SRC[0:15];
GDTR(Base)  SRC[16:47]; 
FI; FI;*/
#include "common.h"
#include "memory.h"
#include "exec/helper.h"
#include "cpu/modrm.h"

extern char suffix;
make_helper(ldt){
	if (suffix=='l'){
	uint32_t imm1 = instr_fetch(eip + 2, 2);
	cpu.GDTR.limit=imm1&0xffff;
	uint32_t imm2 = instr_fetch(eip + 4, 2);
	cpu.GDTR.base=imm2;
	print_asm("lgdtl $0x%x",imm1);
	return 1+1+4;
	}
	else{
	uint32_t imm1=instr_fetch(eip+2,2);
	cpu.GDTR.limit=imm1&0xffff;
	uint32_t imm2 = instr_fetch(eip + 4, 2);
	cpu.GDTR.base=imm2&0xffffff;
	print_asm("lgdtw $0x%x",imm1);
	return 1+1+4;
	}

}