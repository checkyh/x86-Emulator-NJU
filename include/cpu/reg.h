#ifndef __CPU_REG_H__
#define __CPU_REG_H__

#include "common.h"

/* TODO: Re-organize the 'CPU_state' structure to match
 * the GPR encoding scheme in i386 instruction format.
 * For example, if we access reg_w(R_BX) we will get the 'bx' register;
 * if we access reg_b(R_CH), we will get the 'ch' register.
 * Hint: Use 'union'.
 * For more details about the GPR encoding scheme, see i386 manual.
 */
 typedef struct {
	union{
		union {
			uint32_t _32;
			uint16_t _16;
			uint8_t _8[2];
		} gpr[8];

	/* Do NOT change the order of the GPRs' definitions. 
	 * They match the register encoding scheme used in i386 instruction format.
	 * See i386 manual for more details.
	 */
		struct {
			uint32_t eax, ecx, edx, ebx, esp, ebp, esi, edi;
		};
	};



	swaddr_t eip;	uint32_t CR0,CR1,CR2,CR3;
	uint16_t CS,DS,ES,SS;
	union{struct {	unsigned CF:1;unsigned set1:1;unsigned PF:1;unsigned set3:1;
			unsigned AF:1;unsigned set4:1;unsigned ZF:1;unsigned SF:1;
			unsigned TF:1;unsigned IF:1;unsigned DF:1;unsigned OF:1;
			unsigned IOPL:2;unsigned NT:1;unsigned set15:1;
			unsigned RF:1;unsigned VM:1;};
		uint32_t EFLAGS;};
		
	struct{
		uint16_t limit; 
		uint32_t base;
		uint16_t unused;
	}GDTR;
	struct{
		uint32_t base;
		uint16_t limit;
		uint16_t unused;
	}IDTR;
} CPU_state;
extern CPU_state cpu;
typedef struct{
	uint32_t base;
	uint32_t limit;
	uint8_t G,B,AVL,P,DPL,TYPE;
}invdis;
invdis segments[4];
typedef struct{
	uint32_t offset;
	uint16_t selector;
	uint8_t type;
	uint8_t P,DPL;
}gates;
gates gate[4];
enum {ES,CS,SS,DS};
enum { R_EAX, R_ECX, R_EDX, R_EBX, R_ESP, R_EBP, R_ESI, R_EDI };
enum { R_AX, R_CX, R_DX, R_BX, R_SP, R_BP, R_SI, R_DI };
enum { R_AL, R_CL, R_DL, R_BL, R_AH, R_CH, R_DH, R_BH };

#define reg_l(index) (cpu.gpr[index]._32)
#define reg_w(index) (cpu.gpr[index]._16)
#define reg_b(index) (cpu.gpr[index & 0x3]._8[index >> 2])

extern const char* regsl[];
extern const char* regsw[];
extern const char* regsb[];

#endif
