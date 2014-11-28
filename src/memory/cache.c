#include"memory.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

uint64_t L1cachecost;
int set;
#define GROUP_N 128
#define GROUP_LEN  7
#define SET_N 8
#define DATA_LEN 6
#define DATA_N 64
#define MARK_LEN (27-DATA_LEN-GROUP_LEN)
//addr analysis
typedef union{
	struct
	{
		unsigned offset:DATA_LEN;
		unsigned group:GROUP_LEN;
		unsigned mark:MARK_LEN;
	};
	unsigned v:27;
} analy;
//L1 cache
typedef struct{
	uint8_t data[DATA_N];
	bool valid;
	uint16_t mark:MARK_LEN;
} L1cache_line;
L1cache_line L1cache[GROUP_N][SET_N];

void cache_init()
{
	L1cachecost=0;int i,j=0;
	for (i=0;i<GROUP_N;i++) for (j=0;j<SET_N;j++) L1cache[i][j].valid=false;
}
//L1 cache
uint64_t read_L1cachecost(){return L1cachecost;}
void hitL1cache_c(){L1cachecost+=2;}
void missL1cache_c(){L1cachecost+=200;}
int L1cache_mchoose(analy cur)
{
	if (set<=7&&L1cache[cur.group][set].valid&&L1cache[cur.group][set].mark==cur.mark) return set;
	int i=0;
	for (i=0;i<SET_N;i++) if (L1cache[cur.group][i].valid&&L1cache[cur.group][i].mark==cur.mark) 
	{hitL1cache_c();return i;}
	for (i=0;i<SET_N;i++) if (!L1cache[cur.group][i].valid) return -1-i;
	return -1;
} 
void L1cache_makup(analy cur)
{
	int j=0;
	missL1cache_c();
	L1cache[cur.group][set].valid=true;
	L1cache[cur.group][set].mark=cur.mark;
	cur.v=(cur.v>>6)<<6;
	for(j=0;j<DATA_N;j++)  L1cache[cur.group][set].data[j]=dram_read(cur.v+j,1);
}
uint32_t L1cache_reads(uint32_t addr,size_t len)
{
	analy cur;
	cur.v=addr;
	set=10;
	int i=0;
	uint32_t temp=0;
	set=L1cache_mchoose(cur);
	if (set<0) {set=-1-set;L1cache_makup(cur);}
	for(;i<len;i++)
	{
		if (cur.offset==DATA_N){cur.group++;cur.offset=0;set=L1cache_mchoose(cur);}
		if (set<0) {set=-1-set;L1cache_makup(cur);}
		printf("addr=%x\n", cur.v);
		temp=temp+(L1cache[cur.group][set].data[cur.offset]<<(i*8));
		printf("temp=%x\n", temp);
		cur.offset++;
	}
	return  temp;
}
void L1cache_writes(uint32_t addr,size_t len,uint32_t data)
{
	analy cur;
	cur.v=addr;
	dram_write(addr,len,data);
 	set=10;
 	set=L1cache_mchoose(cur);
	if (set>=0)//not write allocate
	{
		int i=0;
		for (i=0;i<len;i++)
		{
			if (cur.offset==DATA_N) {cur.group++;cur.offset=0;set=L1cache_mchoose(cur);}
			if (set<0) break;
			L1cache[cur.group][set].data[cur.offset]=(data<<(24-i*8))>>24;
			cur.offset++;
		}
	}
}
void printL1cacheinfo(uint8_t group,uint8_t set)
{
	int i=0;
	printf("data=");
	for(;i<DATA_N;i++) 
		{
			if (i%16==0) printf("\n");
			printf("%2x ",L1cache[group][set].data[i] );
		}
	printf("\nvalid=%d\n",L1cache[group][set].valid );
	printf("mark=%x\n",L1cache[group][set].mark);
}
