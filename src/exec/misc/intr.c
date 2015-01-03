#include "common.h"
#include <setjmp.h>
extern jmp_buf jbuf;
 
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
 
 	printf("%d\n",NO );
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
}