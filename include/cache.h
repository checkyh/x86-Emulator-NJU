/*
在NEMU中实现一个L1cache, 它的性质如下: 
L1cache block存储空间的大小为64B 
 L1cache存储空间的大小为64KB 
 八位组相联
标志位只需要valid bit即可 
替换算法采用随机方式:从候选行的主存块中随机选取一个淘汰掉
全写法：当cpu执行写操作时，若写命中，则同时写L1cache和主存

写分配法：写失效时，先把所写单元所在的块调入 Cache，
然后再进行写入。这与读失效类似。这种方法也称为写时取方法。
每次写不命中都要从主存读一个块到L1cache
不按写分配法：写失效时，直接写入下一级存储器而不将相应的块调入 Cache。
这种方法也称为绕写法。

16=7+3+6
27=14+7+6
000 001 0000 000|0 0000 00|00 0000
111 111 1111 111   1 1111 11 00 0000
*/
#ifndef __cache_H__
#define __cache_H__
#include "common.h"
// uint64_t read_L1cachecost();
void hitL1cache_c();
void missL1cache_c();
void cache_init();
uint32_t L2cache_reads(uint32_t addr,size_t len);
void printL1cacheinfo(uint8_t group,uint8_t set);
void L2cache_writes(uint32_t addr,size_t len,uint32_t data);

#endif