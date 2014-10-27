#include "exec/helper.h"
#define DATA_BYTE 2
#include "call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "call-template.h"
#undef DATA_BYTE

extern char suffix;
make_helper(call_v) {
	return (suffix == 'l' ? call_l(eip) :call_w(eip));
}

make_helper(leave_v) {
	return (suffix == 'l' ? leave_l(eip) : leave_w(eip));
}
