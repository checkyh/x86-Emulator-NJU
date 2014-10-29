#include "exec/helper.h"
#include "all-instr.h"
#include "cpu/modrm.h"
#include "common.h"
#define arith_change(intype) switch(m.reg)\
		{case 0:return concat(add,intype)(eip);\
 		case 1:return concat(or,intype)(eip);\
		case 2:return concat(adc,intype)(eip);\
 		case 3:return concat(sbb,intype)(eip);\
 		case 4:return concat(and,intype)(eip);\
 		case 5:return concat(sub,intype)(eip);\
 		case 6:return concat(xor,intype)(eip);\
 		case 7:return concat(cmp,intype)(eip);}
make_helper(xff_switcher)
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
make_helper(x83_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	arith_change(_ei2rm_v)
}
make_helper(x81_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	arith_change(_i2rm_v)
}
make_helper(x80_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	arith_change(_i2rm_b)
}