#include "trap.h"



int main() {
	int n=1890;
	nemu_assert((n % 4 == 0 && n % 100 != 0) || (n % 400 == 0)==0)
	HIT_GOOD_TRAP;

	return 0;
}
