#if arith_chooser==0//add
#define switch_r {result=*dst+src; if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;\
	if((MSB(src)&&MSB(*dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(*dst)==0&&MSB(result)))cpu.OF=1;else cpu.OF=0;*dst=result;}
#define switch_rm {result=*dst+src;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;\
	if((MSB(src)&&MSB(*dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(*dst)==0&&MSB(result)))cpu.OF=1;else cpu.OF=0;MEM_W(addr,result);}

#elif arith_chooser==1//or
#define switch_r  {result=*dst|src;*dst=*dst|src;}
#define switch_rm {result=*dst|src;MEM_W(addr,*dst|src);}

#elif arith_chooser==2//adc
#define switch_r {src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;\
	if((MSB(src)&&MSB(*dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(*dst)==0&&MSB(result)))cpu.OF=1;else cpu.OF=0;*dst=result;}
#define switch_rm {src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;\
	if((MSB(src)&&MSB(*dst)&&MSB(result)==0)||(MSB(src)==0&&MSB(*dst)==0&&MSB(result)))cpu.OF=1;else cpu.OF=0;MEM_W(addr,result);}

#elif arith_chooser==3//sbb
#define switch_r {src+=cpu.CF;if(*dst<src) {result=*dst+(~src)+1;cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}*dst=result;}
#define switch_rm {src+=cpu.CF;if(*dst<src) {result=*dst+(~src)+1;cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}MEM_W(addr,result);}

#elif arith_chooser==4//and
#define switch_r {result=(*dst)&(src);*dst=(*dst)&(src);}
#define switch_rm {result=(*dst)&(src);MEM_W(addr,*dst&src);}

#elif arith_chooser==5//sub
#define switch_r {if(*dst<src) {result=*dst+(~src)+1;cpu.CF=1;*dst=*dst+~src+1;}else {result=*dst-src;cpu.CF=0;}\
	if((MSB(src)&&MSB(*dst)==0&&MSB(result))||(MSB(src)==0&&MSB(*dst)&&MSB(result)==0))cpu.OF=1;else cpu.OF=0;*dst=result;}
#define switch_rm {if(*dst<src) {result=*dst+(~src)+1;cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}\
	if((MSB(src)&&MSB(*dst)==0&&MSB(result))||(MSB(src)==0&&MSB(*dst)&&MSB(result)==0))cpu.OF=1;else cpu.OF=0;MEM_W(addr,result);}

#elif arith_chooser==6//xor
#define switch_r {result=*dst^src;*dst=*dst^src;}
#define switch_rm {result=*dst^src;MEM_W(addr,*dst^src);}

#elif arith_chooser==7//cmp
#define switch_r {if(*dst<src) {result=*dst+(~src)+1;cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}\
	if((MSB(src)&&MSB(*dst)==0&&MSB(result))||(MSB(src)==0&&MSB(*dst)&&MSB(result)==0))cpu.OF=1;else cpu.OF=0;}
#define switch_rm {if(*dst<src) {result=*dst+(~src)+1;cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}\
	if((MSB(src)&&MSB(*dst)==0&&MSB(result))||(MSB(src)==0&&MSB(*dst)&&MSB(result)==0))cpu.OF=1;else cpu.OF=0;}

#endif