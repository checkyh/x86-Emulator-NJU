#include "common.h"
#include "memory.h"
#define ADDR(temp,addr,len)  if (len==8) {if (addr>0x80) { addr=0x100-addr;temp-=addr;} else temp+=addr;}