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
	switch (suffix)
	{
		case 'l':return rep_l(eip);
		case 'w':return rep_w(eip);
		case 'b':return rep_b(eip);
		default:return 1;
	}
}

