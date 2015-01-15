#if binlogical_chooser == 4 
#define binlogical sal
#endif

#if binlogical_chooser == 5 
#define binlogical shr
#endif

#if binlogical_chooser == 7 
#define binlogical sar
#endif

#define DATA_BYTE 1
#include "binlogical-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "binlogical-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "binlogical-template.h"
#undef DATA_BYTE

make_helper(concat(binlogical,_i2rm_v)) {
	return (suffix == 'l' ? concat(binlogical,_i2rm_l)(eip) : concat(binlogical,_i2rm_w)(eip));
}

make_helper(concat(binlogical,_cl2rm_v)) {
	return (suffix == 'l' ? concat(binlogical,_cl2rm_l)(eip) : concat(binlogical,_cl2rm_w)(eip));
}

#undef binlogical