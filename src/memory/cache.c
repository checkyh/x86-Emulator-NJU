#include "cache.h"
uint64_t read_cachehit(){return cache_hit;}
void hitcache(){cache_hit++;}
void cache_init(){cache_hit=0;}