#include "cpu/reg.h"
#include "common.h"
#include "page.h"
extern uint32_t hwaddr_read(hwaddr_t addr,size_t len);
void maptlb()
{
	int i=0;
	for (i=0;i<TLB_SIZE;i++) TLB[i].valid=false;
}
bool page_enable()
{
	if ((cpu.CR0&0x1)&&(cpu.CR0>>31)) return true;
	return false;
}
bool page_cross(uint32_t addr,int len)
{
	if (page_enable()&&addr>>12!=(addr+len-1)>>12) return true;
	return false;
}
uint32_t TLB_fill(uint32_t addr)
{
	int i=0;
	for (;i<TLB_SIZE;i++) if (TLB[i].valid==false) break;
	if (i==TLB_SIZE) i=0;
	TLB[i].valid=true;
	uint32_t base=cpu.CR3>>12<<12;
	hwaddr_t table_now=hwaddr_read((addr>>22)*4+base,4);//read页表的物理地址
	assert(table_now&0x1);
	hwaddr_t page_now=hwaddr_read(((addr>>12)&0x3ff)*4+(table_now>>12<<12),4);//read页的物理地址
	assert(page_now&0x1);
	TLB[i].mark=addr>>12<<12;
	TLB[i].addr=page_now>>12<<12;
	return (page_now>>12<<12)+(addr&0xfff);
}
//80480aa
//0000 1000 00|00 0100 1000 |0000 1010 1010
//128*1024*1024=4*1024*(32*1024) number of page and page_entry
hwaddr_t page_translate(lnaddr_t addr)
{
	if(page_enable()) {
		int i=0;
	for (;i<TLB_SIZE;i++) if (TLB[i].valid&&TLB[i].mark==addr>>12<<12) { return TLB[i].addr+(addr&0xfff);break;}
	
	return TLB_fill(addr);
	
	}
	else return addr;
}
void printpage(uint32_t addr)
{
	uint32_t base=0x00138000>>12<<12;
	hwaddr_t table_now=hwaddr_read((addr>>22)*4+base,4);
	hwaddr_t page_now=hwaddr_read(((addr>>12)&0x3ff)*4+(table_now>>12<<12),4);
	uint32_t value=hwaddr_read((page_now>>12<<12)+(addr&0xfff),4);
	printf("table=0x%x\npage=0x%x\nvalue=0x%x\n",table_now,page_now,value);
}