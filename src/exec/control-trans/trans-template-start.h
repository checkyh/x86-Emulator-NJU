#include "common.h"
#include "memory.h"
#define ADDR(eip,addr,len)  {switch(len)\
{case 8:if (addr>0x80)eip-=0x100-addr;else eip+=addr;break;\
case 16: if (addr>0x8000)   eip-=0x10000-addr; else eip+=addr; break;\
case 32:if(len==32) {if (addr>0x80000000) eip-=0x100000000-addr;else eip+=addr;}}}
