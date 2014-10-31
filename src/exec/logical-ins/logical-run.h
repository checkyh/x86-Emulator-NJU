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
 #define switch_rm switch_r
 #define switch_r {if(DATA_BYTE==1)  {reg_w(0)=REG(0)*src; if ((reg_w(0)&0xff00)==0) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==2) {REG(0)=REG(0)*src; REG(1)=REG(0)*src>>16; if(REG(1)) {cpu.CF=1;cpu.OF=1;}else{cpu.CF=0;cpu.OF=0;}}\
		     if (DATA_BYTE==4) {REG(0)=((REG(0)&0xffff)*(src&0xffff))&0xffff;REG(1)=(((REG(0)&0xffff)*(src&0xffff)>>16)+(REG(0)>>16)*(src>>16));}Unused(*dst)}


 #elif logical_chooser==5//imul
 #define switch_rm switch_r	     
 #define switch_r    {if(DATA_BYTE==1)  {reg_w(0)=REG(0)*src; if (	( (MSB(REG(0))&&(reg_w(0)&0xff00))==0xff00 )	||	( (MSB(REG(0))!=0)	&&	((reg_w(0)&0xff00)==0)	)	){cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==2) {REG(0)=REG(0)*src; REG(1)=REG(0)*src>>16; if(	( (MSB(REG(0))	&&	(REG(1)&0xffff))==0xffff )||(( MSB(REG(0))!=0)	&&	(REG(1)&0xffff)==0) 	) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}\
		     if (DATA_BYTE==4) {REG(0)=((REG(0)&0xffff)*(src&0xffff))&0xffff;REG(1)=(((REG(0)&0xffff)*(src&0xffff)>>16)+(REG(0)>>16)*(src>>16));\
		     if(	( (MSB(REG(0))&&(REG(1)&0xffffffff)==0xffffffff) )		||	(( (MSB(REG(0))!=0)&&(REG(1)&0xffffffff)==0) ) 	) {cpu.CF=0;cpu.OF=0;}else{cpu.CF=1;cpu.OF=1;}}Unused(*dst) }

 #elif logical_chooser==6
 #define switch_r {result=*dst^src;*dst=*dst^src;}
 #define switch_rm {result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)}

 #elif logical_chooser==7
 #define switch_r {if(*dst<src) {result=*dst+(~src);cpu.CF=1;}else {result=*dst-src;cpu.CF=0;}}
 #define switch_rm {result=*dst&src;MEM_W(addr,*dst&src); cpu.CF=0;cpu.OF=0;PF_check(result) ZF_check(result) SF_check(result)}
#endif