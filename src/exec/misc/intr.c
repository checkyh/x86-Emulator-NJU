#include "common.h"
#include <setjmp.h>
#include "cpu/reg.h"
extern jmp_buf jbuf;
 
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
 
 	printf("%x %d\n",cpu.IDTR.base,NO );
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
}