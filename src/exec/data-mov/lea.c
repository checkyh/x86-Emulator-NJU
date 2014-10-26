#include "exec/helper.h"

#define DATA_BYTE 1
#include "lea-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "lea-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "lea-template.h"
#undef DATA_BYTE


/* for instruction encoding overloading */

extern char suffix;

make_helper(lea_i2r_v) {
	return (suffix == 'l' ? lea_i2r_l(eip) : lea_i2r_w(eip));
}

make_helper(lea_i2rm_v) {
	return (suffix == 'l' ? lea_i2rm_l(eip) : lea_i2rm_w(eip));
}

make_helper(lea_r2rm_v) {
	return (suffix == 'l' ? lea_r2rm_l(eip) : lea_r2rm_w(eip));
}

make_helper(lea_rm2r_v) {
	return (suffix == 'l' ? lea_rm2r_l(eip) : lea_rm2r_w(eip));
}

make_helper(lea_a2moffs_v) {
	return (suffix == 'l' ? lea_a2moffs_l(eip) : lea_a2moffs_w(eip));
}

make_helper(lea_moffs2a_v) {
	return (suffix == 'l' ? lea_moffs2a_l(eip) : lea_moffs2a_w(eip));
}

