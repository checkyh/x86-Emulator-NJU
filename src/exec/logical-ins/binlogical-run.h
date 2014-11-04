#if binlogical_chooser==4//sal
#define switch_r  { if (src==0) cpu.OF=0;\
		int i=1;for (;i<=src;i++) {\
			cpu.CF=MSB(*dst);if (MSB(*dst)==0) *dst=*dst<<1;\
			else *dst=(*dst<<1);}\
			Unused(result)}
#define switch_rm  {if (src==0) cpu.OF=0;int i=1;\
			for (;i<=src;i++) {cpu.CF=MSB(*dst);\
			*dst=*dst<<1;}MEM_W(addr,*dst);\
			Unused(result)} 


#elif binlogical_chooser==5//shr
#define switch_r { if (src==0) cpu.OF=0;\
		int i=1;for (;i<=src;i++) {\
			cpu.CF=*dst&0x1;*dst=(*dst>>1);}\
			Unused(result)}
 #define switch_rm {if (src==0) cpu.OF=0;int i=1;\
			for (;i<=src;i++) {cpu.CF=*dst&0x1;\
			*dst=*dst>>1;MEM_W(addr,*dst);}\
			Unused(result)} 

 #elif binlogical_chooser==7//sar
 #define switch_r { if (src==0) cpu.OF=0;\
		int i=1;for (;i<=src;i++) {\
			result=*dst;cpu.CF=*dst&0x1;*dst=*dst>>1;\
			*dst=(result&0x80000000)+*dst;}}
 #define switch_rm {if (src==0) cpu.OF=0;int i=1;\
			for (;i<=src;i++) {cpu.CF=*dst&0x1;\
			result=*dst;cpu.CF=*dst&0x1;*dst=*dst>>1;*dst=(result&0x80000000)+*dst;}\
			MEM_W(addr,*dst);} 
#endif
