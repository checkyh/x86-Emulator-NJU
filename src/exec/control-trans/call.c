
#include "exec/helper.h"
#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE

extern char suffix;
make_helper(call_rel_v) {
	return (suffix == 'l' ? call_rel_l(eip) :call_rel_w(eip));
}
make_helper(call_rm_v) {
	return (suffix == 'l' ? call_rm_l(eip) :call_rm_w(eip));
}
make_helper(leave_v) {
	return (suffix == 'l' ? leave_l(eip) : leave_w(eip));
}

make_helper(ret)
{
	return 1;
}
