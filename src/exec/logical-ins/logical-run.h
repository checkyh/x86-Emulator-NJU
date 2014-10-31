#define EX_re(result) if(MSB(result))  {if (DATA_BYTE==1) result=result|0xff00;if (DATA_BYTE==2) result=result|0xffffff00;}else{if (DATA_BYTE==1);result=result;if(DATA_BYTE==4) result-result;}}

#if logical_chooser==0//test 
#define switch_r {result=*dst&src; *dst=*dst&src;cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)} 
#define switch_rm {result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)}

#elif logical_chooser==2//not
#define switch_r {*dst=~src;Unused(result)}
 #define switch_rm {MEM_W(addr,~src);Unused(*dst) }

 #elif logical_chooser==3//neg
 #define switch_r { if (src==0) cpu.CF=0;else cpu.CF=1;result=-src;*dst=-src;OF_check(result) SF_check(result) ZF_check(result) PF_check(result)}
 #define switch_rm {if (src==0) cpu.CF=0;else cpu.CF=1;result=-src;MEM_W(addr,-src);OF_check(result) SF_check(result) ZF_check(result) PF_check(result) Unused(*dst) }

 #elif logical_chooser==4//mul
 #define switch_r {if(DATA_BYTE==1)  {reg_w(0)=REG(0)*src;if ((REG(0)&0xff00)==0) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     else {REG(0)=REG(0)*src; REG(1)=(REG(0)*src)>>(DATA_BYTE*8-1)>>1;  if(REG(1)==0) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}Unused(*dst) }
 #define switch_rm switch_r

 #elif logical_chooser==5//imul
 #define switch_r {Unused(*dst) REG(0)=REG(0)*src;}
 #define switch_rm switch_r

 #elif logical_chooser==6
 #define switch_r {result=*dst^src;*dst=*dst^src;}
 #define switch_rm {result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)}

 #elif logical_chooser==7
 #define switch_r {if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}}
 #define switch_rm {result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)}
#endif