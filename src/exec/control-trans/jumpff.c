#include "exec/helper.h"
#define ADDR(eip,addr,len)  {switch(len)\
{case 8:if (addr>0x80)eip-=0x100-addr;else eip+=addr;break;\
case 16: if (addr>0x8000)   eip-=0x10000-addr; else eip+=addr; break;\
case 32:if(len==32) {if (addr>0x80000000) eip-=0x100000000-addr;else eip+=addr;}}}
#define DATA_BYTE 2
#include "jumpff-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "jumpff-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(jumpff_v)
{
	return (suffix == 'l' ? jumpff_l(eip) : jumpff_w(eip));
}
make_helper(jumpff_ad_v)
{
	return (suffix == 'l' ? jumpff_ad_l(eip) : jumpff_ad_w(eip));
}
#undef ADDR