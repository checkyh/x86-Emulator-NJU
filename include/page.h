#ifndef __PAGE_H__
#define __PAGE_H__
#include "common.h"
#define PAGE_SIZE	4096
#define align_to_page              __attribute((aligned(PAGE_SIZE)))
#define NR_PDE	1024
#define PHY_MEM   (128 * 1024 * 1024)
typedef union PageDirectoryEntry {
	struct {
		uint32_t present             : 1;
		uint32_t read_write          : 1; 
		uint32_t user_supervisor     : 1;
		uint32_t page_write_through  : 1;
		uint32_t page_cache_disable  : 1;
		uint32_t accessed            : 1;
		uint32_t pad0                : 6;
		uint32_t page_frame          : 20;
	};
	uint32_t val;
} PDE;
/* the 32bit Page Table Entry(second level page table) data structure */
typedef union PageTableEntry {
	struct {
		uint32_t present             : 1;
		uint32_t read_write          : 1;
		uint32_t user_supervisor     : 1;
		uint32_t page_write_through  : 1;
		uint32_t page_cache_disable  : 1;
		uint32_t accessed            : 1;
		uint32_t dirty               : 1;
		uint32_t pad0                : 1;
		uint32_t global              : 1;
		uint32_t pad1                : 3;
		uint32_t page_frame          : 20;
	};
	uint32_t val;
} PTE;
PDE kpdir[NR_PDE] align_to_page;
PTE kptable[PHY_MEM / PAGE_SIZE] align_to_page;
bool page_enable();
bool page_cross(uint32_t addr,int len);
hwaddr_t page_translate(lnaddr_t addr);
#endif