#include "exec/helper.h"
extern char suffix;
char ins_name[4]={};
static void  arith_give(int arith_chooser)
{
	switch(arith_chooser)
	{
		case 0:sprintf(ins_name,"%s","add");break;
		case 1:sprintf(ins_name,"%s","or");break;
		case 2:sprintf(ins_name,"%s","adc");break;
		case 3:sprintf(ins_name,"%s","sbb");break;
		case 4:sprintf(ins_name,"%s","and");break;
		case 5:sprintf(ins_name,"%s","sub");break;
		case 6:sprintf(ins_name,"%s","xor");break;
		case 7:sprintf(ins_name,"%s","cmp");break;
	}
}

#define arith_chooser 0
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 1
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 2
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 3
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 4
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 5
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 6
#include "arith-head.h"
#undef arith_chooser

#define arith_chooser 7
#include "arith-head.h"
#undef arith_chooser
