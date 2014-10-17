#include "exec/helper.h"
#include "cpu/reg.h"
#include "memory.h"
#include "cpu/modrm.h"
make_helper(push_r_0) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.eax);
	print_asm("push %s","%eax");
	return  1;
}
make_helper(push_r_1) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.ecx);
	print_asm("push %s","%ecx");
	return  1;
}
make_helper(push_r_2) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.edx);
	print_asm("push %s","%edx");
	return  1;
}
make_helper(push_r_3) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.ebx);
	print_asm("push %s","%ebx");
	return  1;
}
make_helper(push_r_4) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.esp);
	print_asm("push %s","%esp");
	return  1;
}
make_helper(push_r_5) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.ebp);
	print_asm("push %s","%ebp");
	return  1;
}
make_helper(push_r_6) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.esi);
	print_asm("push %s","%esi");
	return  1;
}
make_helper(push_r_7) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.edi);
	print_asm("push %s","%edi");
	return  1;
}


