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
	printf("CF\t\t0x%08x\t\t%d\n",cpu.CF,cpu.CF);
	printf("PF\t\t0x%08x\t\t%d\n",cpu.PF,cpu.PF);
	printf("ZF\t\t0x%08x\t\t%d\n",cpu.ZF,cpu.ZF);
	printf("SF\t\t0x%08x\t\t%d\n",cpu.SF ,cpu.SF);
	printf("IF  \t\t0x%08x\t\t%d\n",cpu.IF  ,cpu.IF  );
	printf("DF\t\t0x%08x\t\t%d\n",cpu.DF,cpu.DF);
	printf("OF\t\t0x%08x\t\t%d\n",cpu.OF,cpu.OF);
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
	if(strcmp(q,"ax")==0) return reg_w(R_AX);
	if(strcmp(q,"cx")==0) return reg_w(R_CX);
	if(strcmp(q,"dx")==0) return reg_w(R_DX);
	if(strcmp(q,"bx")==0) return reg_w(R_BX);
	if(strcmp(q,"sp")==0) return reg_w(R_SP);
	if(strcmp(q,"bp")==0) return reg_w(R_BP);
	if(strcmp(q,"si")==0) return reg_w(R_SI);
	if(strcmp(q,"di")==0) return reg_w(R_DI);
	if(strcmp(q,"al")==0) return reg_b(R_AL);
	if(strcmp(q,"cl")==0) return reg_b(R_CL);
	if(strcmp(q,"dl")==0) return reg_b(R_DL);
	if(strcmp(q,"bl")==0) return reg_b(R_BL);
	if(strcmp(q,"ah")==0) return reg_b(R_AH);
	if(strcmp(q,"ch")==0) return reg_b(R_CH);
	if(strcmp(q,"dh")==0) return reg_b(R_DH);
	if(strcmp(q,"bh")==0) return reg_b(R_BH);
	if(strcmp(q,"CF")==0) return cpu.CF;
	if(strcmp(q,"PF")==0) return cpu.PF;
	if(strcmp(q,"ZF")==0) return cpu.ZF;
	if(strcmp(q,"SF")==0) return cpu.SF;
	if(strcmp(q,"IF")==0) return cpu.IF;
	if(strcmp(q,"DF")==0) return cpu.DF;
	if(strcmp(q,"OF")==0) return cpu.OF;
	if(strcmp(q,"cs")==0) return  cpu.CS;
	if(strcmp(q,"ds")==0) return  cpu.DS;
	if(strcmp(q,"es")==0) return  cpu.ES;
	if(strcmp(q,"ss")==0) return  cpu.SS;
	if(strcmp(q,"cr0")==0) return  cpu.CR0;
	if(strcmp(q,"cr3")==0) return  cpu.CR3;
	if(strcmp(q,"gdtr")==0) {printf("limit=%d\naddr=",cpu.GDTR.limit); return  cpu.GDTR.base;}

	printf("wrong expr\n");return 0;
}
