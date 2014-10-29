#include "trap.h"


int main() {
	short x=0x8000;short y=0x8000;
	short z=x+y;
	nemu_assert(z==0	);
	HIT_GOOD_TRAP;

	return 0;
}
