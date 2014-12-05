#include "exec/helper.h"
#include "cpu/modrm.h"
#include "common.h"
#include "memory.h"

make_helper(jump_far)
{
	uint32_t addr = instr_fetch(eip + 1, 4);
	uint16_t selector=instr_fetch(eip+5,2);
	cpu.eip=addr-7;
	cpu.CS=addr>>4;
	print_asm("ljmp $%x,$%x",selector,addr);
	return 7;
}