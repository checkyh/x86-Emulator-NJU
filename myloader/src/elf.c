#include <elf.h>
#include "trap.h"

void memcpy(void *dest, void *src, int size) {
	int i=0;
	while (i<size)
	{
		*((uint32_t *)dest+i)=*((uint32_t *)src+i);
		i=i+4;
	}
}
void memset(void *dest, void *src, int size) {
	int i=0;
	while (i<size)
	{
		*((uint32_t *)dest+i)=0;
		i=i+4;
	}
}
void loader() {
	Elf32_Ehdr *elf = (void *)0;

	/* Load program header table */
	Elf32_Phdr *ph = (void *)elf->e_phoff;

	int i = 0;
	for(; i < elf->e_phnum; i ++) {
		if(ph[i].p_type == PT_LOAD) {
			memcpy((void *)ph[i].p_vaddr, (void *)(elf + ph[i].p_offset), ph[i].p_filesz);
			memset((void *)(ph[i].p_vaddr + ph[i].p_filesz), 0, ph[i].p_memsz - ph[i].p_filesz);
		}
	}

	((void(*)(void)) elf->e_entry)();

	HIT_GOOD_TRAP;
}

