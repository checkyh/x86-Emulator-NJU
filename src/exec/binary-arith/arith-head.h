#if arith_chooser == 0 
#define arith add
#endif

#if arith_chooser ==  1
#define arith or
#endif

#if arith_chooser == 2 
#define arith adc
#endif

#if arith_chooser == 3 
#define arith sbb
#endif

#if arith_chooser == 4 
#define arith and
#endif

#if arith_chooser == 5 
#define arith sub
#endif

#if arith_chooser == 6 
#define arith xor
#endif

#if arith_chooser == 7 
#define arith cmp
#endif

#define DATA_BYTE 1
#include "arith-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "arith-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "arith-template.h"
#undef DATA_BYTE

make_helper(concat(arith,_i2r_v)) {
	return (suffix == 'l' ? concat(arith,_i2r_l)(eip) : concat(arith,_i2r_w)(eip));
}
make_helper(concat(arith,_ei2rm_v) ){
	return (suffix == 'l' ? concat(arith,_ei2rm_l)(eip) : concat(arith,_ei2rm_w)(eip));
}

make_helper(concat(arith,_i2rm_v)) {
	return (suffix == 'l' ? concat(arith,_i2rm_l)(eip) : concat(arith,_i2rm_w)(eip));
}
make_helper(concat(arith,_r2rm_v)) {
	return (suffix == 'l' ? concat(arith,_r2rm_l)(eip) : concat(arith,_r2rm_w)(eip));
}

make_helper(concat(arith,_rm2r_v)) {
	return (suffix == 'l' ? concat(arith,_rm2r_l)(eip) : concat(arith,_rm2r_w)(eip));
}
#undef arith