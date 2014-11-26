#include"memory.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
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
cache_line cache[GROUP_N][SET_N];

//
uint64_t read_cachecost(){return cachecost;}
void hitcache_c(){cachecost+=2;}
void misscache_c(){cachecost+=200;}
void cache_init(){
	cachecost=0;
	int i,j=0;
	for (i=0;i<GROUP_N;i++)
		for (j=0;j<SET_N;j++)
			cache[i][j].valid=0;
}
uint32_t cache_read(uint32_t addr,size_t len)
{
	int i,j;bool get=false;
	uint32_t temp=0;
	uint16_t mark=(addr>>13)&0x3fff;
	uint8_t offset=addr&0x3ff;
	uint8_t group=(addr>>6)&0x7f;
	for (i=0;i<SET_N;i++) if (cache[group][i].valid&&cache[group][i].mark==mark)
	{
		get=true;
		cache[group][i].valid=true;
		for (j=0;j<len;j++) temp+=(temp<<8*j)+cache[group][i].data[offset+j];
		i=SET_N;//end
	}
	if (get) return temp;
	else{
		get=false;
		for (i=0;i<SET_N;i++) if (!cache[group][i].valid)
		{
			get=true;
			cache[group][i].valid=true;
			for(j=0;j<DATA_LEN;j++) cache[group][i].data[j]=dram_read(addr-offset+j,1);
			i=SET_N;//end
		}
		if (get) {return dram_read(addr,len);}
		else
		{
			for(j=0;j<DATA_LEN;j++) cache[group][0].data[j]=dram_read(addr-offset+j,1);
				return dram_read(addr,len);
		}
	}	
}
