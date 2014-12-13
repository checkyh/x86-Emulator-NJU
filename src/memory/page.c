#include "cpu/reg.h"
#include "common.h"
#include "page.h"
bool page_enable()
{
	if ((cpu.CR0&0x1)&&(cpu.CR0>>31)) return true;
	return false;
}
bool page_cross(uint32_t addr,int len)
{
	if (page_enable()&&addr>>3!=(addr+len)>>3) return true;
	return false;
}
hwaddr_t page_translate(lnaddr_t addr)
{
	if(page_enable()) return addr;
	return addr;
}