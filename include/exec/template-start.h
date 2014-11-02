#include "common.h"
#include "memory.h"

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
#define EX_I(src,imm)     {if (((imm) >> ((1 << 3) - 1)&0x1)){ if (DATA_BYTE==2) src=imm|0xff00;if (DATA_BYTE==4) src=imm|0xffffff00;}else{if (DATA_BYTE==2);src=imm;if(DATA_BYTE==4) src=imm;}}
#define MSB(n) ((DATA_TYPE)(n) >> ((DATA_BYTE << 3) - 1))
#define MLSB(n) (((DATA_TYPE)(n)<<1)>>((DATA_BYTE<<3)-1))
#define PF_check(result) {int i=0,count=0;for (;i<=7;i++){if(result%2==1) count++;result=result/2;}if (count%2==0) cpu.PF=1;else cpu.PF=0;}
#define ZF_check(result) {if (result==0) cpu.ZF=1;else cpu.ZF=0;}
#define SF_check(result) {if (MSB(result)) cpu.SF=1;else cpu.SF=0;}
#define ADDR(eip,addr,len)  {switch(len)\
{case 8:if (addr>0x80)eip-=0x100-addr;else eip+=addr;break;\
case 16: if (addr>0x8000)   eip-=0x10000-addr; else eip+=addr; break;\
case 32:if(len==32) {if (addr>0x80000000) eip-=0x100000000-addr;else eip+=addr;}}}
