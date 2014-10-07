#include "ui/breakpoint.h"
#include "nemu.h"

#define NR_BP 32
extern unsigned char loader[];
static BP bp_pool[NR_BP];
static BP *head, *free_;
int break_state=0;
uint32_t break_ins;

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
void new_bp(uint32_t addr)
{
	if (free_==NULL) assert(0);
	else
	{
		if (head==NULL) 
		{
			init_bp_pool();
			head=free_;
		}
		BP *current=free_;
		current->next=NULL;
		free_->addr=addr;
		free_->inst=swaddr_read(addr,1);
		free_->type=0;
		swaddr_write(addr,1,0xcc);
		free_=free_->next;
	}
}
void break_tcl(uint32_t addr)
{
	BP *cirall=head;
	while(cirall!=NULL)
	{
		if (cirall->addr==addr) { swaddr_write(addr,1,cirall->inst);break;}
		cirall=cirall->next;
	}
	
}
void free_bp(int NO)
{
	BP *temp;
	BP *cirall=head;
	while(cirall!=NULL)
	{
		if (cirall->NO==NO)
		{
			if (cirall==head){
			if (cirall->next!=NULL)
			  head=cirall->next;
			 else head=NULL;
			  cirall->next=free_;
				free_=cirall;
			}
			else{
				temp->next=cirall->next;
				cirall->next=free_;
				free_=cirall;
			}
			return;
		}
		temp=cirall;
		cirall=cirall->next;
	}
	if (head==NULL) break_state=0;
}
void free_all(BP *head)
{
	BP *cirall=head;
	while(cirall!=NULL)
	{
		BP *temp=cirall;
		cirall=cirall->next;
		temp->next=free_;
				free_=temp;
	}
	head=NULL;
	break_state=0;
}
void printbreak()
{
	BP *cirall=head;
	printf("Num\tType\t\tAddress\t\tEXPR\n");
	while(cirall!=NULL)
	{
		printf("%d\t",cirall->NO);
		if (cirall->type==0) printf("breakpoint\t");
		else printf("watchpoint\t");
		printf("0x%06x\t%s\n",cirall->addr,cirall->watch_expr);
		cirall=cirall->next;
		
	}
}
extern uint32_t expr(char *e, bool *success);
void new_watch(char *q)
{
	bool suc=true;
	if (free_==NULL) assert(0);
	else
	{
		if (head==NULL) 
		{
			init_bp_pool();
			head=free_;
		}
		BP *current=free_;
		current->next=NULL;
		free_->watch_expr=q;
		free_->type=1;
		free_->watch_value=expr(q,&suc);
		free_=free_->next;
	}
}
/* TODO: Implement the function of breakpoint */
