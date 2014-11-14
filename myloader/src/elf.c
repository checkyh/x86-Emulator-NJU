#include <elf.h>

#include "trap.h"

void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
	

	/* Here we go! */
	((void(*)(void)) elf->e_entry) ();
	/* When returning from the program, it is executed successfully */

}