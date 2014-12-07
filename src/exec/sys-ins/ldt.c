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
	uint32_t imm = instr_fetch(eip + 2, 4);
	cpu.GDTR.limit=swaddr_read(imm,2);
	cpu.GDTR.base=swaddr_read(imm,4);
	print_asm("lgdtl $0x%x",imm);
	return 1+1+4;
	}
	else{
	uint32_t imm=instr_fetch(eip+2,4);
	cpu.GDTR.limit=swaddr_read(imm,2);;
	cpu.GDTR.base=swaddr_read(imm,4)&0xffffff;
	print_asm("lgdtw $0x%x",imm);
	return 1+1+2;
	}
}