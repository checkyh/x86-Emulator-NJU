#include "exec/helper.h"
#include "all-instr.h"
#include "cpu/modrm.h"
#include "common.h"

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
	switch(m.reg)
	{
		case 0:return concat(add,_ei2rm_v)(eip);
 		case 1:return concat(or,_ei2rm_v)(eip);
		case 2:return concat(adc,_ei2rm_v)(eip);
 		case 3:return concat(sbb,_ei2rm_v)(eip);
 		case 4:return concat(and,_ei2rm_v)(eip);
 		case 5:return concat(sub,_ei2rm_v)(eip);
 		case 6:return concat(xor,_ei2rm_v)(eip);
 		case 7:return concat(cmp,_ei2rm_v)(eip);
	}
}
make_helper(x81_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.reg)
	{
		case 0:return concat(add,_i2rm_v)(eip);
 		case 1:return concat(or,_i2rm_v)(eip);
		case 2:return concat(adc,_i2rm_v)(eip);
 		case 3:return concat(sbb,_i2rm_v)(eip);
 		case 4:return concat(and,_i2rm_v)(eip);
 		case 5:return concat(sub,_i2rm_v)(eip);
 		case 6:return concat(xor,_i2rm_v)(eip);
 		case 7:return concat(cmp,_i2rm_v)(eip);
	}
}
make_helper(x80_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.reg)
	{
		case 0:return concat(add,_i2rm_b)(eip);
 		case 1:return concat(or,_i2rm_b)(eip);
		case 2:return concat(adc,_i2rm_b)(eip);
 		case 3:return concat(sbb,_i2rm_b)(eip);
 		case 4:return concat(and,_i2rm_b)(eip);
 		case 5:return concat(sub,_i2rm_b)(eip);
 		case 6:return concat(xor,_i2rm_b)(eip);
 		case 7:return concat(cmp,_i2rm_b)(eip);
	}
}