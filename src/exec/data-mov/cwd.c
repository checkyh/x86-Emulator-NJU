#include "exec/helper.h"
extern char suffix;

make_helper(cwd_l){
	if ((reg_l(0)>>31)==1) reg_l(2)=0x0FFFFFFFF;else reg_l(2)=0;
	print_asm("cwdl");
	return 1;
}
make_helper(cwd_w){
	if ((reg_w(0)>>15)==1) reg_w(2)=0x0FFF;else reg_w(2)=0;
	print_asm("cwdw");
	return 1;
}
make_helper(cwd_v) {
	return (suffix == 'l' ? cwd_l(eip) : cwd_w(eip));
}
