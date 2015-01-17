#include "exec/helper.h"
extern char suffix;
extern char ins_name[4];
void binlogical_give(int binlogical_chooser)
{
	switch(binlogical_chooser)
	{
		case 4:sprintf(ins_name,"%s","shl");break;
		case 5:sprintf(ins_name,"%s","shr");break;
		case 7:sprintf(ins_name,"%s","sar");break;
		default:assert(0);
	}
}

#define Unused(val) {result=result+(-val+val);}


#define binlogical_chooser 4
#include "binlogical-head.h"
#undef binlogical_chooser

#define binlogical_chooser 5
#include "binlogical-head.h"
#undef binlogical_chooser


#define binlogical_chooser 7
#include "binlogical-head.h"
#undef binlogical_chooser

//complex logical ins


#undef Unused