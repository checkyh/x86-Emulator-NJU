#include "common.h"
#include <setjmp.h>
#include "cpu/reg.h"
extern jmp_buf jbuf;
 
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
 	lnaddr_t addr=cpu.IDTR.base+NO*4;
 	printf("base=%x index=%d %x\n",cpu.IDTR.base,NO,addr);
 	assert(0);
 	uint32_t temp_eip=cpu.eip;
 	cpu.eip=addr;
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
	cpu.eip=temp_eip;
}