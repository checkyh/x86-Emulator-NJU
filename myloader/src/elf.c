#include <elf.h>

#include "trap.h"

void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *ph =(void *)elf+elf->e_phoff;
	nemu_assert(ph);
	HIT_GOOD_TRAP;
	/* When returning from the program, it is executed successfully */

}