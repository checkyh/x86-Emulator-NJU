#include"memory.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
uint64_t cachecost;
int set;
#define GROUP_N 128
#define SET_N 8
#define DATA_LEN 64
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
			cache[i][j].valid=false;
}
int cache_mchoose(uint8_t mark,uint8_t group)
{
	if (cache[group][set].valid&&cache[group][set].mark==mark) return set;
	int i=0;
	for (i=0;i<SET_N;i++) if (cache[group][i].valid&&cache[group][i].mark==mark) 
		{hitcache_c();return i;}
	for (i=0;i<SET_N;i++) if (!cache[group][i].valid) return -1-i;
	return -1;
} 
void cache_makup(uint8_t group,uint8_t mark,uint32_t addr)
{
	int j=0;
	misscache_c();
	cache[group][set].valid=true;
	cache[group][set].mark=mark;
	addr=addr&(0x7ffffc0);
	for(j=0;j<DATA_LEN;j++)  cache[group][set].data[j]=dram_read(addr+j,1);
}
uint8_t cache_read(uint32_t addr)
{
	uint16_t mark=(addr>>13)&0x3fff;
	uint8_t offset=addr&0x3f;
	uint8_t group=(addr>>6)&0x7f;
	set=cache_mchoose(mark,group);
	if (set<0) {set=-1-set;cache_makup(group,mark,addr);}
	return cache[group][set].data[offset]; 
}
uint32_t cache_reads(uint32_t addr,size_t len)
{
	set=10;
	int i=0;
	uint32_t temp=0;
	for(;i<len;i++)temp=temp+(cache_read(addr+i)<<(i*8));
	return  temp;
}
void cache_writes(uint32_t addr,size_t len,uint32_t data)
{
	set=10;
	uint16_t mark=(addr>>13)&0x3fff;
	uint8_t group=(addr>>6)&0x7f;
	uint8_t offset=addr&0x3f;
	set=cache_mchoose(mark,group);
	dram_write(addr,len,data);
	cache_makup(group,mark,addr);
	if (offset+len-1>=DATA_LEN) 
		{
			printf("OK\n");
			group++;
			set=cache_mchoose(mark,group);
			cache_makup(group,mark,addr);
		}
}
void printcacheinfo(uint8_t group,uint8_t set)
{
	int i=0;
	printf("data=");
	for(;i<DATA_LEN;i++) 
		{
			if (i%16==0) printf("\n");
			printf("%2x ",cache[group][set].data[i] );
		}
	printf("\nvalid=%d\n",cache[group][set].valid );
	printf("mark=%x\n",cache[group][set].mark);
}
