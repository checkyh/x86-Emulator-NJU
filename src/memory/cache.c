#include"common.h"
uint64_t cachecost;
#define GROUP_N 128
#define SET_N 8
#define DATA_LEN 8
//
typedef struct{
	uint8_t data[DATA_LEN];
	bool valid;
	uint16_t mark:14;
}cache_line;
cache_line cache[SET_N][GROUP_N];

//
uint64_t read_cachecost(){return cachecost;}
void hitcache_c(){cachecost+=2;}
void misscache_c(){cachecost+=200;}
void cache_init(){
	cachecost=0;
	int i,j=0;
	for (i=0;i<SET_N;i++)
		for (j=0;j<GROUP_N;j++)
			cache[i][j].valid=0;
}