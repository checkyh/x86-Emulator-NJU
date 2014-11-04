#include "trap.h"
#include "stdint.h"
int main()
{
	uint32_t y,x,z;
	x=0x66666667;
	y=0x12a;
	z=0x333333e6;
	nemu_assert(x*y-z==0);
	HIT_GOOD_TRAP;
	return 0;
}