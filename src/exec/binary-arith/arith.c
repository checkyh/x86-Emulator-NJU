#include "exec/helper.h"
extern char suffix;
char ins_name[4]={};
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
/* for instruction encoding overloading */