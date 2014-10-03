#include "nemu.h"

#include <stdlib.h>
#include <time.h>

CPU_state cpu;

const char *regsl[] = {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
const char *regsw[] = {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};
const char *regsb[] = {"al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"};

void reg_test() {
	srand(time(0));
	uint32_t sample[8];
	int i;
	for(i = R_EAX; i <= R_EDI; i ++) {
		sample[i] = rand();
		reg_l(i) = sample[i];
		assert(reg_w(i) == (sample[i] & 0xffff));
	}

	assert(reg_b(R_AL) == (sample[R_EAX] & 0xff));
	assert(reg_b(R_AH) == ((sample[R_EAX] >> 8) & 0xff));
	assert(reg_b(R_BL) == (sample[R_EBX] & 0xff));
	assert(reg_b(R_BH) == ((sample[R_EBX] >> 8) & 0xff));
	assert(reg_b(R_CL) == (sample[R_ECX] & 0xff));
	assert(reg_b(R_CH) == ((sample[R_ECX] >> 8) & 0xff));
	assert(reg_b(R_DL) == (sample[R_EDX] & 0xff));
	assert(reg_b(R_DH) == ((sample[R_EDX] >> 8) & 0xff));

	assert(sample[R_EAX] == cpu.eax);
	assert(sample[R_ECX] == cpu.ecx);
	assert(sample[R_EDX] == cpu.edx);
	assert(sample[R_EBX] == cpu.ebx);
	assert(sample[R_ESP] == cpu.esp);
	assert(sample[R_EBP] == cpu.ebp);
	assert(sample[R_ESI] == cpu.esi);
	assert(sample[R_EDI] == cpu.edi);
}
void printreg()
{
	printf("eax\t\t0x%08x\t\t%d\n",cpu.eax,cpu.eax);
	printf("ecx\t\t0x%08x\t\t%d\n",cpu.ecx,cpu.ecx);
	printf("edx\t\t0x%08x\t\t%d\n",cpu.edx,cpu.edx);
	printf("ebx\t\t0x%08x\t\t%d\n",cpu.ebx,cpu.ebx);
	printf("esp\t\t0x%08x\t\t%d\n",cpu.esp,cpu.esp);
	printf("ebp\t\t0x%08x\t\t%d\n",cpu.ebp,cpu.ebp);
	printf("esi\t\t0x%08x\t\t%d\n",cpu.esi,cpu.esi);
	printf("edi\t\t0x%08x\t\t%d\n",cpu.edi,cpu.edi);
	printf("eip\t\t0x%08x\t\t%d\n",cpu.eip,cpu.eip);
}
uint32_t regfinder(char *q)
{
	if(strcmp(q,"eax")==0) return cpu.eax;
	if(strcmp(q,"ecx")==0) return cpu.ecx;
	if(strcmp(q,"edx")==0) return cpu.edx;
	if(strcmp(q,"ebx")==0) return cpu.ebx;
	if(strcmp(q,"esp")==0) return cpu.esp;
	if(strcmp(q,"ebp")==0) return cpu.ebp;
	if(strcmp(q,"esi")==0) return cpu.esi;
	if(strcmp(q,"edi")==0) return cpu.edi;
	if(strcmp(q,"eip")==0) return cpu.eip;
	return 0;
	
}
