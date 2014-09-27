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
BP *new_bp(uint32_t addr)
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
		swaddr_write(addr,1,0xcc);
		free_=free_->next;
		return 	current;
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
}
void printbreak()
{
	BP *cirall=head;
	printf("Num\tType\tAddress\n");
	while(cirall!=NULL)
	{
		printf("%d:\tbreakpoint\t0x%06x",cirall->NO,cirall->addr);
		cirall=cirall->next;
		
	}
}
/* TODO: Implement the function of breakpoint */
