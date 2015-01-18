#include "exec/helper.h"
extern char suffix;
#define DATA_BYTE 1
#include "inc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "inc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "inc-template.h"
#undef DATA_BYTE

make_helper(inc_rm_v) {
	return (suffix == 'l' ?inc_rm_l(eip) : inc_rm_w(eip));
}
make_helper(inc_r_v) {
	return (suffix == 'l' ?inc_r_l(eip) : inc_r_w(eip));
}

make_helper(dec_rm_v) {
	return (suffix == 'l' ?dec_rm_l(eip) : dec_rm_w(eip));
}
make_helper(dec_r_v) {
	return (suffix == 'l' ?dec_r_l(eip) : dec_r_w(eip));
}