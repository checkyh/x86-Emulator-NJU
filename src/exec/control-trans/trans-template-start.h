#include "common.h"
#include "memory.h"
#define ADDR(eip,addr,len)  if (len==8) {if (addr>0x80) { addr=0x100-addr;eip-=addr;} else eip+=addr;}