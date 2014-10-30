#include "exec/helper.h"
extern char suffix;
extern char ins_name[4];

#define logical_chooser 0
#include "logical-head.h"
#undef logical_chooser

#define logical_chooser 2
#include "logical-head.h"
#undef logical_chooser

#define logical_chooser 3
#include "logical-head.h"
#undef logical_chooser

#define logical_chooser 4
#include "logical-head.h"
#undef logical_chooser

#define logical_chooser 5
#include "logical-head.h"
#undef logical_chooser

#define logical_chooser 6
#include "logical-head.h"
#undef logical_chooser

#define logical_chooser 7
#include "logical-head.h"
#undef logical_chooser

//complex logical ins

make_helper(concat(test,_i2r_v)) {
	return (suffix == 'l' ? concat(test,_i2r_l)(eip) : concat(test,_i2r_w)(eip));
}

make_helper(concat(test,_r2rm_v)) {
	return (suffix == 'l' ? concat(test,_r2rm_l)(eip) : concat(test,_r2rm_w)(eip));
}

make_helper(concat(imul,_i2r_v)) {
	return (suffix == 'l' ? concat(imul,_i2r_l)(eip) : concat(imul,_i2r_w)(eip));
}
