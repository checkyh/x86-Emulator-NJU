
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
extern make_helper(push_rm_v);
make_helper(ff_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.reg)
	{
		case 2:return call_rel_v(eip);
		case 6:return push_rm_v(eip);
		default:return 0;
	}
}
