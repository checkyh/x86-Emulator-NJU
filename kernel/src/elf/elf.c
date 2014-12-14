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
void memocpy(void *dst, void *src, int size) {
	asm volatile("rep movsl" : : "D"(dst), "S"(src), "c"(size));
}

void memoset(void *dst, int value, int size) {
	asm volatile("rep stosl" : : "D"(dst), "a"(value), "c"(size));
}
uint32_t loader() {
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph = NULL;

#ifdef HAS_DEVICE
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
#else
	/* The ELF file is located at memory address 0 */
	elf = (void *)0x0;
#endif
	ph = (void *)elf->e_phoff;
	/* Load each program segment */
	int i=0;
#ifdef IA32_PAGE
	for(; i < elf->e_phnum; i ++) {
		 uint32_t current_addr;
		/* Scan the program header table, load each segment into memory */
		if(ph[i].p_type == PT_LOAD) {

			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
			current_addr=mm_malloc(ph[i].p_vaddr,ph[i].p_memsz);
			memcpy((void *)current_addr, (void *)elf + ph[i].p_offset, ph[i].p_filesz);
			memset((void *)(current_addr + ph[i].p_filesz), 0, ph[i].p_memsz - ph[i].p_filesz);
			 
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */ 		


			/* Record the prgram break for future use. */
			extern uint32_t brk;
			uint32_t new_brk = current_addr + ph[i].p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	}

	volatile uint32_t entry = elf->e_entry;
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);////分配堆栈

#ifdef HAS_DEVICE
	create_video_mapping();
#endif

	write_cr3(get_ucr3());
#else 
	for(; i < elf->e_phnum; i ++) {
		/* Scan the program header table, load each segment into memory */
		if(ph[i].p_type == PT_LOAD) {

			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
			memocpy((void *)ph[i].p_vaddr, (void *)elf + ph[i].p_offset, ph[i].p_filesz);
			memoset((void *)(ph[i].p_vaddr + ph[i].p_filesz), 0, ph[i].p_memsz - ph[i].p_filesz);
			 
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */


			/* Record the prgram break for future use. */
			extern uint32_t brk;
			uint32_t new_brk = ph[i].p_vaddr + ph[i].p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
		}
	}

	volatile uint32_t entry = elf->e_entry;
#endif

	return entry;
}
