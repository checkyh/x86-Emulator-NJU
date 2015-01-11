#include "common.h"
#include <setjmp.h>
#include "cpu/reg.h"

extern jmp_buf jbuf;
extern uint32_t lnaddr_read(lnaddr_t addr, size_t len);
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
 	lnaddr_t addr=cpu.IDTR.base+NO*8;
 	uint32_t offset=(lnaddr_read(addr+6,2)<<16)+lnaddr_read(addr,2);
 	uint16_t selector=lnaddr_read(addr+2,2);
 	printf("offset=%x selector=%d\n",offset,selector);
 	assert(0);
 	uint32_t temp_eip=cpu.eip;
 	cpu.eip=addr;
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
	cpu.eip=temp_eip;
}