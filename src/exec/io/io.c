#include "exec/helper.h"

#define DATA_BYTE 1
#include "io-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "io-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "io-template.h"
#undef DATA_BYTE
extern char suffix;

make_helper(out_a2d_v)
{
	return (suffix== 'l'?out_a2d_l(eip):out_a2d_w(eip));
}
make_helper(in_d2a_v)
{
	return (suffix== 'l'?in_d2a_l(eip):in_d2a_w(eip));
}