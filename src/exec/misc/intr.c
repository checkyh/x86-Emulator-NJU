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
 	uint32_t temp_eip=cpu.eip;
 	cpu.eip=base+offset;
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
	cpu.eip=temp_eip;
}