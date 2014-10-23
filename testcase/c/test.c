#include "trap.h"

int main(){
	int a=0xfff0;
	nemu_assert(a==0xfff0);
	int m=a-2;
	nemu_assert(m==0xffee);
	a=m+1;
	nemu_assert(a==0xffef);
	HIT_GOOD_TRAP;
	return 0 ;
}