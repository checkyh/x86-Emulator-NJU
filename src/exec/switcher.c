#include "exec/helper.h"
#include "all-instr.h"
#include "cpu/modrm.h"
#include "common.h"
#define binlogical_change(intype) switch(m.reg)\
		{case 4:return concat(sal,intype)(eip);\
 		case 5:return concat(shr,intype)(eip);\
 		case 7:return concat(sar,intype)(eip);\
 		default:assert(0);}
#define arith_change(intype) switch(m.reg)\
		{case 0:return concat(add,intype)(eip);\
 		case 1:return concat(or,intype)(eip);\
		case 2:return concat(adc,intype)(eip);\
 		case 3:return concat(sbb,intype)(eip);\
 		case 4:return concat(and,intype)(eip);\
 		case 5:return concat(sub,intype)(eip);\
 		case 6:return concat(xor,intype)(eip);\
 		case 7:return concat(cmp,intype)(eip);}
 #define logical_change(intype) switch(m.reg)\
		{case 0:return concat(test,intype)(eip);\
		case 2:return concat(not,intype)(eip);\
 		case 3:return concat(neg,intype)(eip);\
 		case 4:return concat(mul,intype)(eip);\
 		case 5:return concat(imul,intype)(eip);\
 		case 6:return concat(div,intype)(eip);\
 		case 7:return concat(idiv,intype)(eip);\
 		default:assert(0);}

make_helper(xff_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.reg)
	{
		case 0:return inc_rm_v(eip);
		case 2:return call_rm_v(eip);
		case 4:return jumpff_v(eip);
		case 5:return jumpff_ad_v(eip);
		case 6:return push_rm_v(eip);
		default:return 0;
	}
}
make_helper(xfe_switcher)
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	switch(m.reg)
	{
		case 0:return inc_rm_b(eip);
		default:return 0;
	}
}
make_helper(x83_switcher)//arith
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	arith_change(_ei2rm_v)
}
make_helper(x81_switcher)//arith
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	arith_change(_i2rm_v)
}
make_helper(x80_switcher)//arith
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	arith_change(_i2rm_b)
}
make_helper(xf6_switcher)//logical
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	logical_change(_i2rm_b)
}
make_helper(xf7_switcher)//logical
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	logical_change(_i2rm_v)
}
make_helper(xc1_switcher)//bin-logcial imm
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
		binlogical_change(_i2rm_v)
}
make_helper(xc0_switcher)//bin-logcial imm
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	binlogical_change(_i2rm_v)
}
make_helper(xc2_switcher)//bin-logcial imm
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	binlogical_change(_i2rm_v)
}
make_helper(xd1_switcher)//bin-logcial imm
{
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	binlogical_change(_i2rm_v)
}
make_helper(x0f_switcher)//2 byte escape
{
	 uint8_t ins_type=instr_fetch(eip + 1, 1);
	 if (ins_type>=0x80&&ins_type<=0x8f) return 1+j_near(eip+1);
	 else
	 {

	 switch(ins_type)
	 {
	 	case (0xaf):return 1+imul_rm2r_v(eip+1);
	 	case (0xbe):return 1+movsb_v(eip+1);
	 	case(0xb6):return 1+movzb_v(eip+1);
	 	case(0xb7):return 1+movzx_l(eip+1);
	 }
	 return 1;
	}
}
make_helper(nop)
{
	print_asm("nop");
	return 1;
}
#undef arith_change
#undef logical_change
#undef binlogical_change
