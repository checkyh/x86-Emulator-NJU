#include "ui/breakpoint.h"

#include "nemu.h"

#define NR_BP 32

static BP bp_pool[NR_BP];
static BP *head, *free_;

void init_bp_pool() {
	int i;
	for(i = 0; i < NR_BP - 1; i ++) {
		bp_pool[i].NO = i;
		bp_pool[i].next = &bp_pool[i + 1];
	}
	bp_pool[i].next = NULL;

	head = NULL;
	free_ = bp_pool;
}
BP *new_bp()
{
	if (head==NULL) init_bp_pool();
	head=free_;
	if (free_->next!=NULL) free_=free_->next;
	else assert(0);
	return free_;	
}
void free_bp(BP *bp);

/* TODO: Implement the function of breakpoint */
