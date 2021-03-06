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

	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif

	/* Load program header table */
	ph = (void *)elf->e_phoff;
	i=0;
#ifdef IA32_PAGE 
	for(; i < elf->e_phnum; i ++) {
		if(ph[i].p_type == PT_LOAD) {
			addr=mm_malloc(ph[i].p_vaddr,ph[i].p_memsz);
			memcpy((void *)(addr), (void *)elf + ph[i].p_offset, ph[i].p_memsz);
			//maybe instuctions in memset are still unfinished maybe some other wrong
			extern uint32_t brk;
			uint32_t new_brk = ph[i].p_vaddr + ph[i].p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	}
	
#else
	for(; i < elf->e_phnum; i ++) {
		if(ph[i].p_type == PT_LOAD) {
			memcpy((void *)ph[i].p_vaddr, (void *)elf + ph[i].p_offset, ph[i].p_memsz);
			extern uint32_t brk;
			uint32_t new_brk = ph[i].p_vaddr + ph[i].p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	}
#endif
	
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
