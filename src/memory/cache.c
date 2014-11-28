#include"memory.h"
uint32_t dram_read(hwaddr_t addr, size_t len);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);

uint64_t L1cachecost;
int set;
#define GROUP_N 128
#define SET_N 8
#define DATA_LEN 64
//
typedef struct{
	uint8_t data[DATA_LEN];
	bool valid;
	uint16_t mark:14;
} L1cache_line;
L1cache_line L1cache[GROUP_N][SET_N];

//
uint64_t read_L1cachecost(){return L1cachecost;}
void hitL1cache_c(){L1cachecost+=2;}
void missL1cache_c(){L1cachecost+=200;}
void cache_init(){
	L1cachecost=0;
	int i,j=0;
	for (i=0;i<GROUP_N;i++)
		for (j=0;j<SET_N;j++)
			L1cache[i][j].valid=false;
}
int L1cache_mchoose(uint8_t mark,uint8_t group)
{
	if (L1cache[group][set].valid&&L1cache[group][set].mark==mark) return set;
	int i=0;
	for (i=0;i<SET_N;i++) if (L1cache[group][i].valid&&L1cache[group][i].mark==mark) 
		{hitL1cache_c();return i;}
	for (i=0;i<SET_N;i++) if (!L1cache[group][i].valid) return -1-i;
	return -1;
} 
void L1cache_makup(uint8_t group,uint8_t mark,uint32_t addr)
{
	int j=0;
	missL1cache_c();
	L1cache[group][set].valid=true;
	L1cache[group][set].mark=mark;
	addr=(addr>>6)<<6;
	for(j=0;j<DATA_LEN;j++)  L1cache[group][set].data[j]=dram_read(addr+j,1);
}
uint8_t L1cache_read(uint32_t addr)
{
	uint16_t mark=addr>>13;
	uint8_t offset=addr&0x3f;
	uint8_t group=(addr>>6)&0x7f;
	set=L1cache_mchoose(mark,group);
	if (set<0) {set=-1-set;L1cache_makup(group,mark,addr);}
	return L1cache[group][set].data[offset]; 
}
uint32_t L1cache_reads(uint32_t addr,size_t len)
{
	set=10;
	int i=0;
	uint32_t temp=0;
	for(;i<len;i++)temp=temp+(L1cache_read(addr+i)<<(i*8));
	return  temp;
}
void L1cache_writes(uint32_t addr,size_t len,uint32_t data)
{
	uint16_t mark=addr>>13;
	uint8_t offset=addr&0x3f;
	uint8_t group=(addr>>6)&0x7f;
	dram_write(addr,len,data);
 	set=10;
 	set=L1cache_mchoose(mark,group);
 	int j=offset+len-DATA_LEN;
	if (set>=0)//not write allocate
	{
	int i=0;
	for (i=0;i<len&&i+offset<DATA_LEN;i++)
		L1cache[group][set].data[offset+i]=(data<<(24-i*8))>>24;
	}
	if (j>0) { Log("CROSS\n");}

}
void printL1cacheinfo(uint8_t group,uint8_t set)
{
	int i=0;
	printf("data=");
	for(;i<DATA_LEN;i++) 
		{
			if (i%16==0) printf("\n");
			printf("%2x ",L1cache[group][set].data[i] );
		}
	printf("\nvalid=%d\n",L1cache[group][set].valid );
	printf("mark=%x\n",L1cache[group][set].mark);
}
