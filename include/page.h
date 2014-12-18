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
}TLBSTR;
TLBSTR TLB[64];
void maptlb();
#endif