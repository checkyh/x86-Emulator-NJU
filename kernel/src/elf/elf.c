#include "common.h"
#include "memory.h"
#include <string.h>

#include <elf.h>

#ifdef HAS_DEVICE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)
void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();
uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;
	int i = 0;
	uint32_t addr=0;
#ifdef HAS_DEVICE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
#else
	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif

#ifdef IA32_PAGE
	i=0;uint32_t memsz=0;
	ph = (void *)elf->e_phoff;
	for(; i < elf->e_phnum; i ++)
		memsz+=ph[i].p_memsz;
	addr=mm_malloc(0x8048000,memsz);
	addr-=0x8048000;
#endif
	/* Load program header table */
	ph = (void *)elf->e_phoff;
	i=0;
	for(; i < elf->e_phnum; i ++) {
		if(ph[i].p_type == PT_LOAD) {
			memcpy((void *)(addr+ph[i].p_vaddr), (void *)elf + ph[i].p_offset, ph[i].p_memsz);
			memset((void *)(addr+ph[i].p_vaddr + ph[i].p_filesz), 0, ph[i].p_memsz - ph[i].p_filesz);
		}
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	

	
	volatile uint32_t entry = elf->e_entry;


#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);////分配堆栈
	write_cr3(get_ucr3());
#ifdef HAS_DEVICE
	create_video_mapping();
#endif
#endif

	return entry;
}
