/*在NEMU中实现一个cache, 它的性质如下: 
cache block存储空间的大小为64B 
 cache存储空间的大小为64KB 
 八位组相联
标志位只需要valid bit即可 
替换算法采用随机方式:从候选行的主存块中随机选取一个淘汰掉
全写法：当cpu执行写操作时，若写命中，则同时写cache和主存

写分配法：先在主存块中更新相应存储单元，然后分配一个cache行，
将更新后的主存块装入分配的cache行中，
每次写不命中都要从主存读一个块到cache
16=7+3+6
27=7+6+14
*/
#ifndef __CACHE_H__
#define __CACHE_H__
#include "common.h"
uint64_t read_cachecost();
void hitcache_c();
void misscache_c();
void cache_init();
#endif