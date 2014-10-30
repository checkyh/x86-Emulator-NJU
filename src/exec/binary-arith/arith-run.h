#if arith_chooser==0
#define switch_r result=*dst+src; if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;*dst=*dst+src;
#endif 

 #if arith_chooser==1
 #define switch_r  result=*dst|src;*dst=*dst|src;
#endif
 #if arith_chooser==2
 #define switch_r src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;*dst=*dst+src;
#endif
 #if arith_chooser==3
 #define switch_r src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+(~src);}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}
#endif
 #if arith_chooser==4
 #define switch_r result=(*dst)&(src);*dst=(*dst)&(src);
#endif
 #if arith_chooser==5
 #define switch_r if(*dst<src) {result=*dst+(~src);cpu.CF=1;*dst=*dst+~src;}else {result=*dst-src;cpu.CF=0;*dst=*dst-src;}
#endif
 #if arith_chooser==6
 #define switch_r result=*dst^src;*dst=*dst^src;
#endif
 #if arith_chooser==7
 #define switch_r if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}
#endif

 #if arith_chooser==0
 #define switch_rm result=*dst+src;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;MEM_W(addr,*dst+src);
#endif
 #if arith_chooser==1
 #define switch_rm result=*dst|src;MEM_W(addr,*dst|src);
#endif
 #if arith_chooser==2
 #define switch_rm src+=cpu.CF;if(result<*dst||result<src) cpu.CF=1;else cpu.CF=0;result=*dst+src;MEM_W(addr,*dst+src);
#endif
 #if arith_chooser==3
 #define switch_rm src+=cpu.CF;if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}
#endif
 #if arith_chooser==4
 #define switch_rm result=(*dst)&(src);MEM_W(addr,*dst&src);
#endif
 #if arith_chooser==5
 #define switch_rm if(*dst<src) {result=*dst+(~src);cpu.CF=1;MEM_W(addr,*dst+(~src));}else {result=*dst-src;cpu.CF=0;MEM_W(addr,*dst-src);}
#endif
 #if arith_chooser==6
 #define switch_rm result=*dst^src;MEM_W(addr,*dst^src);
#endif
 #if arith_chooser==7
 #define switch_rm if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}
#endif