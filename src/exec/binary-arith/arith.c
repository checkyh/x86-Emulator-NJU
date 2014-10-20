#include "exec/helper.h"

#define DATA_BYTE 1
#include "arith-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "arith-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "arith-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;
make_helper(arith_i2r_v) {
	return (suffix == 'l' ? arith_i2r_l(eip) : arith_i2r_w(eip));
}

make_helper(arith_i2rm_v) {
	return (suffix == 'l' ? arith_i2rm_l(eip) : arith_i2rm_w(eip));
}

make_helper(arith_r2rm_v) {
	return (suffix == 'l' ? arith_r2rm_l(eip) : arith_r2rm_w(eip));
}

make_helper(arith_rm2r_v) {
	return (suffix == 'l' ? arith_rm2r_l(eip) : arith_rm2r_w(eip));
}