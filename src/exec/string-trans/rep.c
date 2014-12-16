#include "exec/helper.h"
#define DATA_BYTE 1
#include "rep-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "rep-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "rep-template.h"
#undef DATA_BYTE
extern char suffix;
make_helper(rep)
{
	int ins = instr_fetch(eip+1, 1);
	switch(ins)
	{
		case(0xa4):case(0xaa):return rep_b(eip);
		default: switch (suffix)
		{
			case 'l':return rep_l(eip);
			case 'w':return rep_w(eip);
		}
	}
	assert(0);
}

