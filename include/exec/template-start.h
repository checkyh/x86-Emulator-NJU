#include "common.h"
#include "memory.h"
extern char ins_name[5];
#if DATA_BYTE == 1

#define SUFFIX b
#define DATA_TYPE uint8_t
#define DATA_TYPE_S int8_t
#define OF_check(result)  if((result<127UL&&result>-128UL)||result==0) cpu.OF=0;else cpu.OF=1;

#elif DATA_BYTE == 2

#define SUFFIX w
#define DATA_TYPE uint16_t
#define DATA_TYPE_S int16_t
#define OF_check(result)  if((result<32767UL&&result>-32768UL)||result==0) cpu.OF=0;else cpu.OF=1;

#elif DATA_BYTE == 4
#define SUFFIX l
#define DATA_TYPE uint32_t
#define DATA_TYPE_S int32_t
#define OF_check(result)  if((result<2147483647UL&&result>-2147483648UL)||result==0) cpu.OF=0;else cpu.OF=1;

#else

#error unknown DATA_BYTE

#endif

#define REG(index) concat(reg_, SUFFIX) (index)
#define REG_NAME(index) concat(regs, SUFFIX) [index]
#define MEM_R(addr) swaddr_read(addr, DATA_BYTE)
#define MEM_W(addr, data) swaddr_write(addr, DATA_BYTE, data)
#define EX_I(src,imm)     {if ((imm) >> ((1 << 3) - 1)){if (DATA_BYTE==2) src=imm|0x1100;if (DATA_BYTE==4) src=imm|0x11110000;}else{if (DATA_BYTE==2);src=imm&0x0011;if (DATA_BYTE==4) src=imm&0x00001111;}}
#define MSB(n) ((DATA_TYPE)(n) >> ((DATA_BYTE << 3) - 1))
#define PF_check(result) {int i=0,count=0;for (;i<=7;i++){if(result%2==1) count++;result=result/2;}if (count%2==0) cpu.PF=1;else cpu.PF=0;}
