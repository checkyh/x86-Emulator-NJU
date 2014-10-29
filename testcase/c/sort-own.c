#include "trap.h"


int main() {
	uint8_t x=0x10;uint8_t y=0x10;
	uint8_t z=x+y;
	nemu_assert(z==1);
	HIT_GOOD_TRAP;

	return 0;
}
