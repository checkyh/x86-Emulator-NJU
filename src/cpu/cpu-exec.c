#include "ui/ui.h"

#include "nemu.h"

#include <setjmp.h>
#include "ui/breakpoint.h"
#define LOADER_START 0x100000

int exec(swaddr_t);
void load_prog();
void init_dram();

char assembly[40];
jmp_buf jbuf;	/* Make it easy to perform exception handling */

extern uint8_t loader [];
extern uint32_t loader_len;

extern int quiet;

void restart() {
	/* Perform some initialization to restart a program */
	load_prog();
	memcpy(hwa_to_va(LOADER_START), loader, loader_len);

	cpu.eip = LOADER_START;
// load Code Segment
	segments[CS].base=0;
	segments[CS].limit=0xffffffff;
// CR0-PE =0 real address mode 
	cpu.CR0=0;
	cpu.CR3=0;
	init_dram();
	cache_init();
	maptlb();
	setbreak();// 设置已存在的断点 src/ui/breakpoint.c
	cpu.ebp=0;
	cpu.esp=0x8000000;
	cpu.EFLAGS=0x2;
}


static void print_bin_instr(swaddr_t eip, int len) {
	int i;
	printf("%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		printf("%02x ", swaddr_read(eip + i, 1));
	}
	printf("%*.s", 50 - (12 + 3 * len), "");
}
extern uint32_t hwaddr_read(hwaddr_t addr, size_t len);
void cpu_exec(volatile uint32_t n) {
	volatile uint32_t n_temp = n;
	setjmp(jbuf);
	for(; n > 0; n --) {
		if (have_watch&&findwatch()) return;
		//if (hwaddr_read((0x8048123>>22)*4+0x00138000,4)==0x13c007)  {Log("HERE!");return  ;}
		if(break_state!=0)
		{
			if (break_state==1) 
			{
			 break_state=2;
			 break_addr=cpu.eip;
			 break_tcl(cpu.eip);
			 return ;
			 }
			else if (break_state==2&&(cpu.eip>break_addr))
			{
			 break_state=0;
			 swaddr_write(break_addr,1,0xcc);
			}		
		}
		swaddr_t eip_temp = cpu.eip;
		int instr_len = exec(cpu.eip);

		cpu.eip += instr_len;

		if(n_temp != -1 || (enable_debug && !quiet)) {
			print_bin_instr(eip_temp, instr_len);
			puts(assembly);
		}

		if(nemu_state == INT) {
			printf("\n\nUser interrupt\n");
			return;
		} 
		else if(nemu_state == END) { return; }
	}
}
