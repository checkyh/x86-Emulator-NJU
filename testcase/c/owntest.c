#include "trap.h"

int add(int a, int b) {
	int c = a + b;
	return c;
}

int test_data[] = {1,2,45};
int main()
{
	nemu_assert(add(test_data[0],test_data[1]) == 3);

	nemu_assert(add(test_data[1],test_data[2]) == 47);

	HIT_GOOD_TRAP;

	return 0;
}