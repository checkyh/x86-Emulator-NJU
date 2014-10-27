#include "common.h"
#include "memory.h"
#define ADDR(eip,addr,len)  if (len==8) { if (addr>0x80)   eip-=0x100-addr; else eip+=addr; 	}