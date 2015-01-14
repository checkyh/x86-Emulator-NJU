#include "exec/helper.h"
#include "cpu/reg.h"
#include "memory.h"
#include "cpu/modrm.h"

#define DATA_BYTE 1
#include "push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "push-template.h"
#undef DATA_BYTE

extern char suffix;

make_helper(push_i_v){
	return (suffix =='l'?push_i_l(eip):push_i_w(eip));
}
make_helper(push_r_v) {
	return (suffix == 'l' ? push_r_l(eip) : push_r_w(eip));
}

make_helper(push_rm_v) {
	return (suffix == 'l' ? push_rm_l(eip) : push_rm_w(eip));
}

make_helper(pop_r_v) {
	return (suffix == 'l' ? pop_r_l(eip) : pop_r_w(eip));
}

make_helper(pop_rm_v) {
	return (suffix == 'l' ? pop_rm_l(eip) : pop_rm_w(eip));
}
make_helper(pusha_v) {
	return (suffix == 'l' ? pusha_l(eip):pusha_w(eip));
}
make_helper(popa_v) {
	return (suffix == 'l' ? popa_l(eip):popa_w(eip));
}