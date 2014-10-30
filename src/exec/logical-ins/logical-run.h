#if logical_chooser==0
#define switch_r result=*dst&src; *dst=*dst&src;cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)
#define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)

#elif logical_chooser==2
 #define switch_r src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;*dst=*dst+src;
 #define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)

 #elif logical_chooser==3
 #define switch_r src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+(~src);}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}
 #define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)

 #elif logical_chooser==4
 #define switch_r result=(*dst)&(src);*dst=(*dst)&(src);
 #define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)

 #elif logical_chooser==5
 #define switch_r if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+~src;}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}
 #define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)

 #elif logical_chooser==6
 #define switch_r result=*dst^src;*dst=*dst^src;
 #define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)

 #elif logical_chooser==7
 #define switch_r if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}
 #define switch_rm result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)
#endif