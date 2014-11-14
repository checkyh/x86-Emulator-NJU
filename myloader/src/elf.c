#include <elf.h>

#include "trap.h"

void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
	Elf32_Phdr *ph =(void *)elf+elf->e_phoff;
	Elf32_Phdr *eph=ph+elf->e_phnum;
	uint32_t *pa,*i;
 	unsigned int j=1;
 	for (;ph<eph;ph++)
 	{
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) {
		pa=(void *)ph->p_vaddr;		
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
 		for (j=0;j<(ph->p_filesz+3)/4;j++)pa[j]=((uint32_t *)ph->p_offset)[j];
 			

			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
 		for (i=(void *)pa+ph->p_filesz;i<pa+ph->p_memsz;i++) i=0;
 	}
	}

	/* Here we go! */
	((void(*)(void)) elf->e_entry) ();
	/* When returning from the program, it is executed successfully */

}