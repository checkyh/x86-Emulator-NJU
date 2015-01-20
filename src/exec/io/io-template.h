#include "exec/helper.h"
#include "exec/template-start.h"
#include "cpu/modrm.h"
#include "io/port-io.h"

make_helper(concat(out_a2d_,SUFFIX)){
	pio_write(reg_w(2),4,reg_l(0));
	print_asm("out %%%s,(%%dx)",REG_NAME(0));
	return 1;
}
make_helper(concat(in_d2a_,SUFFIX)){
	reg_l(0)=pio_read(reg_w(2),4);
	print_asm("in (%%dx),%%%s",REG_NAME(0));
	return 1;
}
#include "exec/template-end.h"