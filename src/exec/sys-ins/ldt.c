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
#include "device/i8259.h"
#include "cpu/reg.h"
extern char suffix;
make_helper(ldt){
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	swaddr_t addr;
	int len = read_ModR_M(eip + 1, &addr);
	if (m.reg==2)
	{
	if (suffix=='l'){
		cpu.GDTR.limit=swaddr_read(addr,2);
		cpu.GDTR.base=swaddr_read(addr+2,4);
		print_asm("lgdtl %s",ModR_M_asm);
		return 1+len;
		}
	else{
	cpu.GDTR.limit=swaddr_read(addr,2);;
	cpu.GDTR.base=swaddr_read(addr+2,4)&0xffffff;
	print_asm("lgdtw %s",ModR_M_asm);
	return 1+len;
	}
	}
	else
	{
		if (suffix=='l'){
		cpu.IDTR.limit=swaddr_read(addr,2);
		cpu.IDTR.base=swaddr_read(addr+2,4);
		print_asm("lidtl %s",ModR_M_asm);
		return 1+len;
		}
	else{
	cpu.IDTR.limit=swaddr_read(addr,2);;
	cpu.IDTR.base=swaddr_read(addr+2,4)&0xffffff;
	print_asm("lidtw %s",ModR_M_asm);
	return 1+len;
	}
}
}
void raise_intr(uint8_t);
make_helper(hlt){
	print_asm("hlt");
	while (cpu.INTR & cpu.IF){
		uint32_t intr_no = i8259_query_intr();
		i8259_ack_intr();
		raise_intr(intr_no);
	}
	return 1;
}