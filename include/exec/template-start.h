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
#define EX_I(src,imm)     {if ((imm) >> ((1 << 3) - 1)){ if (DATA_BYTE==2) src=imm|0xff00;if (DATA_BYTE==4) src=imm|0xffffff00;}else{if (DATA_BYTE==2);src=imm;if(DATA_BYTE==4) src=imm;}}
#define MSB(n) ((DATA_TYPE)(n) >> ((DATA_BYTE << 3) - 1))
#define MLSB(n) (((DATA_TYPE)(n)<<1)>>((DATA_BYTE<<3)-1))
#define OF_check(result)    {uint8_t temp=MSB(src)+MSB(*dst);temp=temp-((temp>>1)<<1); uint8_t temp1=MLSB(src)+MLSB(*dst);temp1=temp1-((temp1>>1)<<1);cpu.OF=(MSB(result)^(temp))^(MLSB(result)^temp1);}
#define PF_check(result) {int i=0,count=0;for (;i<=7;i++){if(result%2==1) count++;result=result/2;}if (count%2==0) cpu.PF=1;else cpu.PF=0;}
#define RESULT_check	{if (MSB(result)) cpu.SF=1;else cpu.SF=0;if (result==0) cpu.ZF=1;else cpu.ZF=0;PF_check(result) OF_check(result)}
#define a_pre_r {DATA_TYPE src=0;src=imm;DATA_TYPE *dst=&REG(m.R_M);}
#define a_pre_rm {src=imm;DATA_TYPE dst_v=MEM_R(addr);DATA_TYPE *dst=&dst_v;}


/*#define sprintf(ins_name,"%s","add");result=*dst+src; if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;*dst=*dst+src;break;\
 case 1:sprintf(ins_name,"%s","or");result=*dst|src;*dst=*dst|src;break;\
 case 2:sprintf(ins_name,"%s","adc");src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;*dst=*dst+src;break;\
 case 3:sprintf(ins_name,"%s","sbb");src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+(~src);}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}break;\
 case 4:sprintf(ins_name,"%s","and");result=(*dst)&(src);*dst=(*dst)&(src);break;\
 case 5:sprintf(ins_name,"%s","sub");if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+~src;}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}break;\
 case 6:sprintf(ins_name,"%s","xor");result=*dst^src;*dst=*dst^src;break;\
 case 7:sprintf(ins_name,"%s","cmp");if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}break;}
#define switch_r_m switch(r_r)\
{case 0:sprintf(ins_name,"%s","add");result=*dst+src;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;MEM_W(addr,*dst+src);break;\
 case 1:sprintf(ins_name,"%s","or");result=*dst|src;MEM_W(addr,*dst|src);break;\
 case 2:sprintf(ins_name,"%s","adc");src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;MEM_W(addr,*dst+src);break;\
 case 3:sprintf(ins_name,"%s","sbb");src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}break;\
 case 4:sprintf(ins_name,"%s","and");result=(*dst)&(src);MEM_W(addr,*dst&src);break;\
 case 5:sprintf(ins_name,"%s","sub");if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}break;\
 case 6:sprintf(ins_name,"%s","xor");result=*dst^src;MEM_W(addr,*dst^src);break;\
 case 7:sprintf(ins_name,"%s","cmp");if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}break;}
*/