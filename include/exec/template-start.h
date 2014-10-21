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
#define EX_I(ex_imm,imm)     {if ((imm) >> ((1 << 3) - 1)){if (DATA_BYTE==2) ex_imm=imm|0x1100;if (DATA_BYTE==4) ex_imm=imm|0x11110000;}else{if (DATA_BYTE==2);ex_imm=imm&&0x0011;if (DATA_BYTE==4) ex_imm=imm&&0x00001111;}}
#define MSB(n) ((DATA_TYPE)(n) >> ((DATA_BYTE << 3) - 1))

