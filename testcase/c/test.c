#include "trap.h"
#include "stdint.h"
int main()
{
	uint32_t y,x;
	x=0x66666667;
	y=0x12a;
	nemu_assert(x*y==0x333333e6);
	HIT_GOOD_TRAP;
	return 0;
}