#if logical_chooser == 0 
#define logical test
#endif

#if logical_chooser == 2 
#define logical not
#endif

#if logical_chooser == 3 
#define logical neg
#endif

#if logical_chooser == 4 
#define logical imul
#endif

#if logical_chooser == 5 
#define logical mul
#endif

#if logical_chooser == 6 
#define logical div
#endif

#if logical_chooser == 7 
#define logical idiv
#endif

#define DATA_BYTE 1
#include "logical-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "logical-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "logical-template.h"
#undef DATA_BYTE

make_helper(concat(logical,_i2rm_v)) {
	return (suffix == 'l' ? concat(logical,_i2rm_l)(eip) : concat(logical,_i2rm_w)(eip));
}


#undef logical