#ifndef __LOGICAL_H__
#define __LOGICAL_H__

make_helper(test_i2r_b);
make_helper(test_i2rm_b);
make_helper(test_r2rm_b);
make_helper(test_rm2r_b);

make_helper(test_ei2rm_v);
make_helper(test_i2r_v);
make_helper(test_i2rm_v);
make_helper(test_r2rm_v);
make_helper(test_rm2r_v);


make_helper(not_i2rm_b);
make_helper(not_i2rm_v);



make_helper(neg_i2rm_b);
make_helper(neg_i2rm_v);



make_helper(mul_i2rm_b);
make_helper(mul_i2rm_v);


make_helper(imul_i2r_b);
make_helper(imul_i2rm_b);
make_helper(imul_r2rm_b);
make_helper(imul_rm2r_b);

make_helper(imul_ei2rm_v);
make_helper(imul_i2r_v);
make_helper(imul_i2rm_v);
make_helper(imul_r2rm_v);
make_helper(imul_rm2r_v);


make_helper(div_i2rm_b);
make_helper(div_i2rm_v);

make_helper(idiv_i2rm_b);
make_helper(idiv_i2rm_v);

#endif