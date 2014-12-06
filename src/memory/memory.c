#include "common.h"
#include "cache.h"
#include "cpu/reg.h"
//物理地址hwaddr 逻辑地址 swaddr
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
/* Memory accessing interfaces */
uint16_t current_sreg;
uint32_t segment_translater(lnaddr_t addr,size_t len)
{
	if ((cpu.CR0&0x1)==0) return addr;
	else{
		return addr;
	}
}
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return L1cache_reads(addr, len);
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	L1cache_writes(addr, len, data);
}
uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return hwaddr_read(addr, len);
}
 
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	return hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr=segment_translater(addr,len);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	lnaddr_t lnaddr=segment_translater(addr,len);
	lnaddr_write(lnaddr, len, data);
}

/*static uint32_t hwaddr_read_instr(hwaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return dram_read(addr, len);
}*/

uint32_t instr_fetch(swaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	current_sreg=cpu.CS>>3;
	lnaddr_t lnaddr=segment_translater(addr,len);
	return swaddr_read(lnaddr, len);
}