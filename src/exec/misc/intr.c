#include "common.h"
#include <setjmp.h>
#include "cpu/reg.h"
#include "memory.h"
extern jmp_buf jbuf;

void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
 	lnaddr_t addr=cpu.IDTR.base+NO*8;
 	uint32_t offset=(lnaddr_read(addr+6,2)<<16)+lnaddr_read(addr,2);
 	uint16_t selector=lnaddr_read(addr+2,2);
 	uint32_t base=base_read(selector);
 	cpu.eip=base+offset;
 	int i=0;
	uint32_t origin_esp=cpu.esp;
	for (i=0;i<=7;i++)
	{
		cpu.esp-=4;
		if (i!=4) swaddr_write(cpu.esp,reg_l(i),4);
		else swaddr_write(cpu.esp,origin_esp,4);
	}
	cpu.esp-=4;
	swaddr_write(cpu.esp,cpu.CS,4);
	cpu.esp-=4;
	swaddr_write(cpu.esp,cpu.eip,4);
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
}