#if binlogical_chooser==4//sal
#define switch_r   {Unused(src) Unused(*dst)}
#define switch_rm  {Unused(src) Unused(*dst)}  

#elif binlogical_chooser==5//shr
#define switch_r   {Unused(src) Unused(*dst)}
 #define switch_rm {Unused(src) Unused(*dst)}   



 #elif binlogical_chooser==7//sar
 #define switch_r { if (src==0) cpu.OF=0;\
		int i=1;for (;i<=src;i++) {\
			cpu.CF=*dst&0x1;if (MSB(*dst)==0) *dst=*dst>>1;\
			else {*dst=(*dst>>1);*dst=((*dst)&(1<<(8*DATA_BYTE-1)));}}\
			Unused(result)}
 #define switch_rm {if (src==0) cpu.OF=0;int i=1;\
			for (;i<=src;i++) {cpu.CF=*dst&0x1;\
			if (MSB(*dst)==0) {*dst=*dst>>1;MEM_W(addr,*dst);}\
			else {*dst=(*dst>>1);*dst=((*dst)&(1<<(8*DATA_BYTE-1)));\
			MEM_W(addr,*dst);}}Unused(result)} 

#endif
