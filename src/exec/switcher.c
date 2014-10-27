#include "exec/helper.h"
#include "all-instr.h"
#include "cpu/modrm.h"


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
