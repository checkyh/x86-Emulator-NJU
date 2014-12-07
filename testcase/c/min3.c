#include "trap.h"

int min3(int x, int y, int z) {
	int m;
	if(x < y) { m = x; }
	else { m = y; }
	if(z < m) m = z;
	return m;
}

int test_data[] = {0, 1, 2, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff};
int ans[] = {0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x1, 0x1, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x1, 0x1, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x1, 0x1, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x1, 0x1, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x2, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x2, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0, 0, 0, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x1, 0x1, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x2, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0, 0x1, 0x2, 0x7fffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0x80000001, 0x80000000, 0x80000001, 0x80000001, 0x80000001, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0xfffffffe, 0x80000000, 0x80000001, 0xfffffffe, 0xfffffffe, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x80000000, 0x80000001, 0xfffffffe, 0xffffffff};

#define NR_DATA (sizeof(test_data) / sizeof(test_data[0]))

int main() {
	int i, j, k, ans_idx = 0;
	for(i = 0; i < NR_DATA; i ++) {
		for(j = 0; j < NR_DATA; j ++) {
			for(k = 0; k < NR_DATA; k ++) {
				nemu_assert(min3(test_data[i], test_data[j], test_data[k]) == ans[ans_idx ++]);
			}
		}
	}
	HIT_GOOD_TRAP;


	return 0;
}
