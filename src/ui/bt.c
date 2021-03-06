#include "memory.h"
#include "cpu/reg.h"
extern char *find_fun_name(uint32_t addr);
void printbt()
{
int num=0;
uint32_t addr = cpu.eip;
uint32_t ebp = cpu.ebp;
char *fun_name=NULL;
while(ebp>0) {
	fun_name=find_fun_name(addr);
	printf("#%d\t 0x%x in %s()\n",num,addr,fun_name);
	if (ebp>=0x7fffffc) {goto EXIT_;}
	addr = swaddr_read(ebp+4,4);
	ebp = swaddr_read(ebp,4);
	num++;
}
EXIT_:
	num=0;
}