#include "prefix/prefix.h"
#include "switcher.h"

#include "data-mov/mov.h"
#include "data-mov/push.h"
#include "data-mov/lea.h"
#include "data-mov/cwd.h"
#include "data-mov/xchg.h"

#include "misc/misc.h"

#include "logical-ins/logical.h"
#include "logical-ins/binlogical.h"
#include "logical-ins/setcc.h"

#include "control-trans/jump.h"
#include "control-trans/call.h"
#include "control-trans/jmp-far.h"

#include  "binary-arith/arith.h"
#include "binary-arith/inc.h"

#include "string-trans/rep.h"

#include "flag-control/dflag.h"

#include "sys-ins/ldt.h"