#include "trap.h"

int main(){
	int a=0xffff;
	nemu_assert(a==0xfff0);
	int m=a-0xf;
	nemu_assert(m==0xffee);
	HIT_GOOD_TRAP;
	return 0 ;
}