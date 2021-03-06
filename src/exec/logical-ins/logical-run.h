#ifndef _MUL_HIGH_
#define _MUL_HIGH_
	uint32_t mul_high(uint32_t x,uint32_t y)
{	
	unsigned a[65]={0};
	int i=1,j=1;
	for (;j<=32;j++)
	{	for (i=1;i<=32;i++)
		{
			if ((x>>(i-1))&1)
			a[i+j-1]+=((y>>(j-1))&1);
		}
	}
	for (j=1;j<=64;j++) if (a[j]>=2) {a[j+1]+=a[j]>>1;a[j]=a[j]&1;}
	uint32_t result=0,temp=1;
	for (i=1;i<=32;i++)
	{
		temp=1;
		for (j=1;j<=i-1;j++) temp=temp*2;
		result+=a[i+32]*temp;
	}
	return result;
}
#endif

#if logical_chooser==0//test 
#define switch_r { result=*dst&src; cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)} 
#define switch_rm {result=*dst&src;cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)}

#elif logical_chooser==2//not
#define switch_r {*dst=~src;Unused(result)}
 #define switch_rm {MEM_W(addr,~src);Unused(*dst) }

 #elif logical_chooser==3//neg
 #define switch_r { if (src==0) cpu.CF=0;else cpu.CF=1;result=-src;*dst=-src;SF_check(result) ZF_check(result) PF_check(result)}
 #define switch_rm {if (src==0) cpu.CF=0;else cpu.CF=1;result=-src;MEM_W(addr,-src);SF_check(result) ZF_check(result) PF_check(result) Unused(*dst) }

 #elif logical_chooser==4//mul

 #define switch_rm switch_r
 #define switch_r {if(DATA_BYTE==1)  {reg_w(0)=REG(0)*src; if (( (MSB(REG(0))&&(reg_w(0)&0xff00))==0xff00 )||( (MSB(REG(0))!=0)&&((reg_w(0)&0xff00)==0))){cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==2) {result=REG(0)*src; REG(2)=REG(0)*src>>16; REG(0)=result;if(( (MSB(REG(0))	&&(REG(2)&0xffff))==0xffff )||(( MSB(REG(0))!=0)&&(REG(2)&0xffff)==0) ) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==4) {result=REG(0)*src; REG(2)=mul_high(REG(0),src);REG(0)=result;if( (MSB(REG(0))&&(REG(2)==0xffffffff))||(((MSB(REG(0))!=0)&&REG(2)==0))) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}Unused(*dst)}
 #elif logical_chooser==5//imul
 #define switch_rm switch_r	     
 #define switch_r   if(MSB(REG(0))) {if (DATA_BYTE==1) reg_w(0)=reg_w(0)|0xff00;if (DATA_BYTE==2) reg_l(0)=reg_l(0)|0xffff0000;}\
 		  {if(DATA_BYTE==1)  {reg_w(0)=REG(0)*src; if (( (MSB(REG(0))&&(reg_w(0)&0xff00))==0xff00 )||( (MSB(REG(0))!=0)&&((reg_w(0)&0xff00)==0))){cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==2) {result=REG(0)*src; REG(2)=REG(0)*src>>16; REG(0)=result;if(( (MSB(REG(0))	&&(REG(2)&0xffff))==0xffff )||(( MSB(REG(0))!=0)&&(REG(2)&0xffff)==0) ) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==4) {result=REG(0)*src;  REG(2)=mul_high(REG(0),src);REG(0)=result;if( (MSB(REG(0))&&(REG(2)==0xffffffff))||(((MSB(REG(0))!=0)&&REG(2)==0))) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}Unused(*dst)}
void concat(imul,DATA_BYTE)(DATA_TYPE *dst,DATA_TYPE src,DATA_TYPE src2) 
{

	int i=DATA_BYTE*8-1;
	for (;i>=1;i--) if(src2>>i!=0) break;
	int j=DATA_BYTE*8-1;
	for (;i>=1;i--) if(src>>j!=0) break;
	if(i+j+2<=DATA_BYTE*8) {cpu.CF=0;cpu.OF=0;}
	 else {cpu.CF=1;cpu.OF=1;} 
	 *dst=src*src2;
}

 #elif logical_chooser==6//div
 #define switch_rm switch_r
 #define switch_r {assert(src!=0);\
 		     if(DATA_BYTE==1)  {if(result/src>0xffff) assert(0);result=reg_w(0);REG(0)=result/src;reg_w(0)=(reg_w(0)&0xff)+((result%src)<<8);}\
 		   if (DATA_BYTE==2) {if(result/src>0xffffffff) assert(0);result=REG(0)+(REG(2)<<16);REG(0)=result/src; REG(1)=result%src;}\
		     if (DATA_BYTE==4) { if((REG(2)%src*(4294967296UL/src)+REG(0))/src>0xffffffff) assert(0);result=REG(0); REG(0)=(REG(2)%src*(4294967296UL/src)+REG(0))/src;REG(2)=result+REG(2)*4294967296UL-REG(0)*src;}\
		     Unused(*dst)}
 #elif logical_chooser==7//idiv
 #define switch_rm switch_r
 #define switch_r {assert(src!=0);\
 		     if(DATA_BYTE==1)  {if(result/src>0xffff) assert(0);result=reg_w(0);REG(0)=result/src;reg_w(0)=(reg_w(0)&0xff)+((result%src)<<8);}\
 		   if (DATA_BYTE==2) {if(result/src>0xffffffff) assert(0);result=REG(0)+(REG(2)<<16);REG(0)=result/src; REG(1)=result%src;}\
		     if (DATA_BYTE==4) { if((REG(2)%src*(4294967296UL/src)+REG(0))/src>0xffffffff) assert(0);result=REG(0); REG(0)=(REG(2)%src*(4294967296UL/src)+REG(0))/src;REG(2)=result+REG(2)*4294967296UL-REG(0)*src;}\
		     Unused(*dst)}
#endif
