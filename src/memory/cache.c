#include"memory.h"
#include "stdlib.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

// uint64_t L1cachecost;
int set;
int set2;
#define GROUP_LEN  7
#define GROUP_N 1<<GROUP_LEN
#define SET_N 8
#define SET2_N 16
#define DATA_LEN 6
#define DATA_N 1<<DATA_LEN
#define MARK_LEN (27-DATA_LEN-GROUP_LEN)
#define GROUP2_LEN 12
#define GROUP2_N 1<<GROUP2_LEN
#define MARK2_LEN (27-DATA_LEN-GROUP2_LEN)
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
typedef union{
	struct
	{
		unsigned offset:DATA_LEN;
		unsigned group:GROUP2_LEN;
		unsigned mark:MARK2_LEN;
	};
	unsigned v:27;
} analy2;

//L1 cache
typedef struct{
	uint8_t data[DATA_N];
	bool valid;
	uint16_t mark:MARK_LEN;
} L1cache_line;
L1cache_line L1cache[GROUP_N][SET_N];
typedef struct{
	uint8_t data[DATA_N];
	bool valid;
	bool dirty;
	uint16_t mark:MARK_LEN;
} L2cache_line;
L2cache_line L2cache[GROUP2_N][SET2_N];

void cache_init()
{
	// L1cachecost=0;
	int i,j=0;
	for (i=0;i<GROUP_N;i++) for (j=0;j<SET_N;j++) L1cache[i][j].valid=false;
	for (i=0;i<GROUP2_N;i++) for (j=0;j<SET2_N;j++) L2cache[i][j].valid=false;
	for (i=0;i<GROUP2_N;i++) for (j=0;j<SET2_N;j++) L2cache[i][j].dirty=false;

}
int L2cache_mchoose(analy2 cur)
{
	if (set2<=SET2_N-1&&L2cache[cur.group][set2].valid&&L2cache[cur.group][set2].mark==cur.mark) return set2;
	int i=0;
	for (i=0;i<SET2_N;i++) if (L2cache[cur.group][i].valid&&L2cache[cur.group][i].mark==cur.mark) 
	return i;
	for (i=0;i<SET2_N;i++) if (!L2cache[cur.group][i].valid) return -1-i;
	srand(cur.v);
	return -(1+rand()%SET2_N);
} 
void L2cache_makup(analy2 cur)
{
	int j=0;
	L2cache[cur.group][set2].valid=true;
	L2cache[cur.group][set2].mark=cur.mark;
	cur.v=(cur.v>>DATA_LEN)<<DATA_LEN;
	for(j=0;j<DATA_N;j++)  L2cache[cur.group][set2].data[j]=dram_read(cur.v+j,1);
}
void L1cache_makup(analy cur);
uint32_t L2cache_reads(uint32_t addr,size_t len)
{
	analy2 cur;
	cur.v=addr;
	set2=SET2_N+1;
	int i=0;
	uint32_t temp=0;
	set2=L2cache_mchoose(cur);
	if (set2<0) {set2=-1-set2;L2cache_makup(cur);}
	for(;i<len;i++)
	{
		temp=temp+(L2cache[cur.group][set2].data[cur.offset]<<(i*8));
		if (cur.offset+1==DATA_N){
			cur.group++;cur.offset=0;
			set2=L2cache_mchoose(cur);}else cur.offset++;
		if (set<0) {set2=-1-set2;L2cache_makup(cur);}
	}
	return  temp;
}
void L2cache_writes(uint32_t addr,size_t len,uint32_t data)
{
	analy2 cur;
	cur.v=addr;
 	set2=SET2_N+1;
 	int i=0;
 	set2=L2cache_mchoose(cur);

 	if (set2>=0)//write back
 	{
 		analy2 temp;
 		temp.v=cur.v;
 		if (L2cache[temp.group][set2].dirty)
 		 {
 			temp.offset=0;
 			L2cache[temp.group][set2].dirty=false;
 			for(i=0;i<DATA_N;i++) {dram_write(temp.v,1,L2cache[temp.group][set2].data[temp.offset]);temp.offset++;}
 		} 
 		if (cur.offset+len-1>=DATA_N) 
 		{

 			temp.group++;temp.offset=0;
 			set2=L2cache_mchoose(cur);
 			if (L2cache[temp.group][set2].dirty) 
 			{
 			L2cache[temp.group][set2].dirty=false;
 			for(i=0;i<DATA_N;i++) {dram_write(temp.v,1,L2cache[temp.group][set2].data[temp.offset]);temp.offset++;}
 			}
 		}
 	} 
	else {set2=-1-set2;L2cache_makup(cur);}//write allocate 写不命中时  先把所写单元所在的块调入 Cache
	for (i=0;i<len;i++)
	{
		L2cache[cur.group][set2].dirty=true;
		L2cache[cur.group][set2].data[cur.offset]=(data<<(24-i*8))>>24;
		if (cur.offset+1==DATA_N){cur.group++;cur.offset=0;set2=L2cache_mchoose(cur);}
		else cur.offset++;
		if (set2<0) {set2=-1-set2;L2cache_makup(cur);L2cache[cur.group][set2].dirty=true;}
	}
	
}
//L1 cache
// uint64_t read_L1cachecost(){return L1cachecost;}
// void hitL1cache_c(){L1cachecost+=2;}
// void missL1cache_c(){L1cachecost+=200;}
int L1cache_mchoose(analy cur)
{
	if (set<=SET_N-1&&L1cache[cur.group][set].valid&&L1cache[cur.group][set].mark==cur.mark) return set;
	int i=0;
	for (i=0;i<SET_N;i++) if (L1cache[cur.group][i].valid&&L1cache[cur.group][i].mark==cur.mark) 
	{		// hitL1cache_c();
		return i;}
	for (i=0;i<SET_N;i++) if (!L1cache[cur.group][i].valid) return -1-i;
	srand(cur.v);
	return -(1+rand()%SET_N);
} 
void L1cache_makup(analy cur)
{
	int j=0;
	// missL1cache_c();
	L1cache[cur.group][set].valid=true;
	L1cache[cur.group][set].mark=cur.mark;
	cur.v=(cur.v>>DATA_LEN)<<DATA_LEN;
	for(j=0;j<DATA_N;j++)  L1cache[cur.group][set].data[j]=L2cache_reads(cur.v+j,1);
}
uint32_t L1cache_reads(uint32_t addr,size_t len)
{
	analy cur;
	cur.v=addr;
	set=SET_N+1;
	int i=0;
	uint32_t temp=0;
	set=L1cache_mchoose(cur);
	if (set<0) {set=-1-set;L1cache_makup(cur);}
	for(;i<len;i++)
	{
		temp=temp+(L1cache[cur.group][set].data[cur.offset]<<(i*8));
		if (cur.offset+1==DATA_N){cur.group++;cur.offset=0;set=L1cache_mchoose(cur);}else cur.offset++;
		if (set<0) {set=-1-set;L1cache_makup(cur);}
	}
	return  temp;
}
void L1cache_writes(uint32_t addr,size_t len,uint32_t data)
{
	analy cur;
	cur.v=addr;
	L2cache_writes(addr,len,data);
 	set=SET_N+1;
 	set=L1cache_mchoose(cur);
	//not write allocate
	if (set>=0)
	{
		int i=0;
		for (i=0;i<len;i++)
		{
			L1cache[cur.group][set].data[cur.offset]=(data<<(24-i*8))>>24;
			if (cur.offset+1==DATA_N){cur.group++;cur.offset=0;set=L1cache_mchoose(cur);}else cur.offset++;
			if (set<0) break;
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
