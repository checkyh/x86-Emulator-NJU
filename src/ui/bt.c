#include "memory.h"
#include "cpu/reg.h"
extern char *find_fun_name(uint32_t addr);
void printbt()
{
uint32_t addr = cpu.eip;
uint32_t ebp = cpu.ebp;
char *fun_name=NULL;
while( ebp>=0 ) {
	printf("%x\n",ebp );
	fun_name=find_fun_name(addr);
	printf("%s\n",fun_name);
	addr = swaddr_read(ebp-8,4);
	ebp = swaddr_read(ebp-4,4);
}
}