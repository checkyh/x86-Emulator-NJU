#include "trap.h"

int is_leap_year(int n) {
	return (n % 4 == 0 && n % 100 != 0) || (n % 400 == 0);
}

int ans[] = {0, 0, 1};

int main() {
	int i;
	for(i = 0; i < 3; i ++) {
		nemu_assert(is_leap_year(i + 1890) == ans[i]);
	}

	HIT_GOOD_TRAP;

	return 0;
}
