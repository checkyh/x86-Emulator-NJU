#include "trap.h"
#include "stdint.h"
int main()
{
	uint32_t x,y,z;
	x=0x66666667;
	y=0x12a;
	z=x*y;
	nemu_assert(z==0x333333e6);
	HIT_GOOD_TRAP;
	return 0;
}