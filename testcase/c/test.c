#include "trap.h"

int main(){
	unsigned a=0xfff0;
	nemu_assert(a==0xfff0);
	unsigned m=a-0xfff0;
	nemu_assert(m==0xffee);
	HIT_GOOD_TRAP;
	return 0 ;
}