#include "exec/helper.h"
extern char suffix;
extern char ins_name[4];
static void logical_give(int logical_chooser)
{
	switch(logical_chooser)
	{
		case 0:sprintf(ins_name,"%s","test");break;
		case 2:sprintf(ins_name,"%s","not");break;
		case 3:sprintf(ins_name,"%s","neg");break;
		case 4:sprintf(ins_name,"%s","mul");break;
		case 5:sprintf(ins_name,"%s","imul");break;
		case 6:sprintf(ins_name,"%s","div");break;
		case 7:sprintf(ins_name,"%s","idiv");break;
	}
}
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
