   /*        
   typedef struct {
               unsigned char e_ident[EI_NIDENT];
               uint16_t      e_type;
               uint16_t      e_machine;
               uint32_t      e_version;
               Elf32_Addr     e_entry;
               Elf32_Off      e_phoff;
               Elf32_Off      e_shoff;
               uint32_t      e_flags;
               uint16_t      e_ehsize;
               uint16_t      e_phentsize;
               uint16_t      e_phnum;
               uint16_t      e_shentsize;
               uint16_t      e_shnum;
               uint16_t      e_shstrndx;
           } Elf32_Ehdr;
*/
#include <elf.h>
 
void loader() {
	/* The ELF file is located at memory address 0 */
	Elf32_Ehdr *elf = (void *)0;
 
	foreach ph in ph_table {
		/* Scan the program header table, load each segment into memory */
		if(ph->p_type == PT_LOAD) {
 
			/* TODO: read the content of the segment from the ELF file 
			 * to the memory region [VirtAddr, VirtAddr + FileSiz)
			 */
 
 
			/* TODO: zero the memory region 
			 * [VirtAddr + FileSiz, VirtAddr + MemSiz)
			 */
 
		}
	}
 
	/* Here we go! */
	((void(*)(void)) elf->entry) ();
 
	/* When returning from the program, it is executed successfully */
	HIT_GOOD_TRAP;
}