#include <elf.h>

#include "trap.h"

void loader() {
	/* The ELF file is located at memory address 0 */
	int m=3,n=2;
	m=m-n;
	nemu_assert(m);
	HIT_GOOD_TRAP;
	/* When returning from the program, it is executed successfully */

}