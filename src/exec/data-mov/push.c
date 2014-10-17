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
	return  1;
}
make_helper(push_r_2) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.edx);
	return  1;
}
make_helper(push_r_3) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.ebx);
	return  1;
}
make_helper(push_r_4) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.esp);
	return  1;
}
make_helper(push_r_5) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.ebp);
	print_asm("push %s","%eax");
	return  1;
}
make_helper(push_r_6) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.esi);
	return  1;
}
make_helper(push_r_7) {
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.edi);
	return  1;
}


