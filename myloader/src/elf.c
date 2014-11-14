#include <elf.h>

#include "trap.h"

void loader() {
	/* The ELF file is located at memory address 0 */
	int a=1;
	nemu_assert(a);
	HIT_GOOD_TRAP;
	/* When returning from the program, it is executed successfully */

}