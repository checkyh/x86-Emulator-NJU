#ifndef __PAGE_H__
#define __PAGE_H__
#include "common.h"
bool page_enable();
bool page_cross(uint32_t addr,int len);
hwaddr_t page_translate(lnaddr_t addr);
typedef struct {
	bool valid;
	uint32_t addr;
	uint32_t asid;// unused
	uint32_t mark;
}TLBSTR;
#define TLB_SIZE 64
TLBSTR TLB[TLB_SIZE];
void maptlb();
#endif