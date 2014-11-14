#include "exec/helper.h"
#include "memory.h"
make_helper(cld)
{
	cpu.DF=0;
	print_asm("cld");
	return 1;
}