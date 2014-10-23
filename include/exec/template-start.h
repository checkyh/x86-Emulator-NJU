#include "common.h"
#include "memory.h"
extern char ins_name[5];
#if DATA_BYTE == 1

#define SUFFIX b
#define DATA_TYPE uint8_t
#define DATA_TYPE_S int8_t


#elif DATA_BYTE == 2

#define SUFFIX w
#define DATA_TYPE uint16_t
#define DATA_TYPE_S int16_t

#elif DATA_BYTE == 4
#define SUFFIX l
#define DATA_TYPE uint32_t
#define DATA_TYPE_S int32_t

#else

#error unknown DATA_BYTE

#endif

#define REG(index) concat(reg_, SUFFIX) (index)
#define REG_NAME(index) concat(regs, SUFFIX) [index]
#define MEM_R(addr) swaddr_read(addr, DATA_BYTE)
#define MEM_W(addr, data) swaddr_write(addr, DATA_BYTE, data)
#define EX_I(src,imm)     {if ((imm) >> ((1 << 3) - 1)){if (DATA_BYTE==2) src=imm|0xc;if (DATA_BYTE==4) src=imm|0xf0;}else{if (DATA_BYTE==2);src=imm;if(DATA_BYTE==4) src=imm;}}
#define MSB(n) ((DATA_TYPE)(n) >> ((DATA_BYTE << 3) - 1))
#define OF_check(result)  {if (MSB(result_c)==1) cpu.OF=1;else cpu.OF=0;}
#define PF_check(result) {int i=0,count=0;for (;i<=7;i++){if(result%2==1) count++;result=result/2;}if (count%2==0) cpu.PF=1;else cpu.PF=0;}
#define RESULT_check	if (MSB(result)) cpu.SF=1;else cpu.SF=0;if (result==0) cpu.ZF=1;else cpu.ZF=0;if (result<0) cpu.CF=0;PF_check(result) OF_check(result)