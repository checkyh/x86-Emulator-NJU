#include "common.h"
#include "cache.h"
#include "cpu/reg.h"
#include "page.h"
#include "io/mmio.h"
//物理地址hwaddr 逻辑地址 swaddr
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
/* Memory accessing interfaces */
uint16_t current_sreg;
uint32_t segment_translater(lnaddr_t addr,size_t len)
{
	if ((cpu.CR0&0x1)==0) return addr;
	else return addr+segments[current_sreg].base;
}
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	if(is_mmio(addr)!=-1) return mmio_read(addr,len,is_mmio(addr));
	return L1cache_reads(addr, len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	if(is_mmio(addr)!=-1) mmio_write(addr,len,data,is_mmio(addr));
	else
	L1cache_writes(addr, len, data);
}
uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	if (page_cross(addr,len)) {
		/* this is a special case, you can handle it later. */
		assert(0);
		uint32_t temp=0;int i=0;
		for(i=0;i<len;i++) temp+=(lnaddr_read(addr+i,1))<<i*8;
		return temp;
	}
	else {
		hwaddr_t hwaddr = page_translate(addr);
		return hwaddr_read(hwaddr, len);
	}
}
 
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	if (page_cross(addr,len)) {
		/* this is a special case, you can handle it later. */
		printf("addr=%x\n",addr );
		assert(0);
		int i=0;
		for(i=0;i<len;i++) lnaddr_write(addr+i,1,data<<(24-8*i)>>24);
	}
	else {
		hwaddr_t hwaddr = page_translate(addr);
		hwaddr_write(hwaddr, len,data);
	}
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	if(addr>=0xa0000u&&addr<0xafa00u) return hwaddr_read(addr,len);
	lnaddr_t lnaddr=segment_translater(addr,len);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	if(addr>=0xa0000u&&addr<0xafa00u) hwaddr_write(addr,len,data);
	else{
	lnaddr_t lnaddr=segment_translater(addr,len);
	lnaddr_write(lnaddr, len, data);}
}

/*static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return dram_read(addr, len);
}*/

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	current_sreg=CS;
	lnaddr_t lnaddr=segment_translater(addr,len);
	return swaddr_read(lnaddr, len);
}
uint32_t base_read(uint32_t index)
{
	uint32_t temp=lnaddr_read(cpu.GDTR.base+index*8+2,2);
	temp+=lnaddr_read(cpu.GDTR.base+index*8+4,1)<<16;
	temp+=lnaddr_read(cpu.GDTR.base+index*8+7,1)<<24;
	return temp;
}