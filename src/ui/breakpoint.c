#include "ui/breakpoint.h"
#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;
extern uint32_t hwaddr_read(hwaddr_t addr, size_t len);
extern void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data);
void init_bp_pool() 
{
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
}
BP *new_bp(uint32_t addr)
{
	if (head==NULL) 
	{
		init_bp_pool();
		head=free_;
	}
	BP *current=free_;
	free_->addr=addr;
	free_->inst=swaddr_read(addr,1);
	printf("%x",free_->inst);
	swaddr_write((addr+*hw_mem),1,0xcc);
	if (free_->next!=NULL) free_=free_->next;
	else assert(0);
	return 	current;
}
void free_bp(BP *bp);
/* TODO: Implement the function of breakpoint */
