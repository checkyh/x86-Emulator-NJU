#include "trap.h"
#include "stdint.h"
int main()
{
	uint32_t y,x,z;
	x=0x66666667;
	y=0x12a;

	z=0x333333e6;
	nemu_assert(x*y/2*2-z==0);
	return 0;
}