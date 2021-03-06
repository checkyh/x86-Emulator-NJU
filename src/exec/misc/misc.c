#include "exec/helper.h"

#include "ui/ui.h"

#include "nemu.h"

#include "page.h"
extern int break_state;
make_helper(inv) {
	/* invalid opcode */

	uint8_t temp[8];
	((uint32_t *)temp)[0] = instr_fetch(eip, 4);
	((uint32_t *)temp)[1] = instr_fetch(eip + 4, 4);
	printf("invalid opcode(eip = 0x%08x): %02x %02x %02x %02x %02x %02x %02x %02x ...\n", 
			eip, temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);

	assert(0);
}

make_helper(int3) {
	/* A breakpoint is hit! Do something here! */
	break_state=1;
	cpu.eip--;
	return 1;
}
extern uint32_t segment_translater(lnaddr_t addr,size_t len);
make_helper(nemu_trap) {
	if (cpu.eax==2)
	{
			
		int i=0;char temp;
		uint32_t len=cpu.edx;
		uint32_t addr=cpu.ecx;
		for (i=0;i<len;i++)
		{
			temp=(char)swaddr_read(addr+i,2);
			printf("%c", temp);
		}
		return 1;
	}
	else
	{
		printf("nemu: HIT \33[1;31m%s\33[0m TRAP at eip = 0x%08x\n\n", (cpu.eax == 0 ? "GOOD" : "BAD"), cpu.eip);
		nemu_state = END;

		print_asm("nemu trap");
		return 1;
	}
}
extern void raise_intr(uint8_t NO);
make_helper(int_i)
{
	uint8_t imm=instr_fetch(eip+1,1);
	raise_intr(imm);
	return 2;
}
//32  no 16
make_helper(iret)
{
	cpu.eip=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	cpu.CS=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	int i=0;
	for (i=7;i>=0;i--)
	{
		if (i!=4) reg_l(i)=swaddr_read(cpu.esp,4);
		cpu.esp+=4;
	}
	print_asm("iret");
	return 1;
}