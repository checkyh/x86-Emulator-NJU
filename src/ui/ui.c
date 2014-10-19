#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
extern bool judge;
int nemu_state = END;
void cpu_exec(uint32_t);
extern int number_state;
void restart();
extern void printreg();
extern void free_bp(int NO);
extern BP *new_bp();
extern void new_watch();
extern void printbreak();
extern uint32_t expr(char *e, bool *success);
extern void setbreak();
uint32_t  sixteenstring(char *q,int step)
{
	int addr=0;
	int temp=1;
	do
	{	
	switch(*q)    
	{      case '0' : temp=0 ; break;
	       case '1' : temp=1 ; break;
	       case '2' : temp=2 ; break;
	       case '3' : temp=3 ; break;
	       case '4' : temp=4 ; break;
	       case '5' : temp=5 ; break;
	       case '6' : temp=6 ; break;
	       case '7' : temp=7 ; break;
	       case '8' : temp=8 ; break;
	       case '9' : temp=9 ; break;
	       case 'a' : temp=10 ; break;
	       case 'b' : temp=11 ; break;
	       case 'c' : temp=12 ; break;
	       case 'd' : temp=13 ; break;
	       case 'e' : temp=14 ; break;
	       case 'f' : temp=15 ; break;
	       default: temp=-1;
	}
	if (temp!=-1)
	{
		addr=addr*step+temp;
		q++;
	}
	}
	while (temp!=-1);	
	return  addr;
}
char *temp=NULL;
/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}
	assert(0);
	printf("%s\n", line_read);
	if(*line_read!=0) sprintf(temp,"%s",line_read);
	return line_read;
}

/* This function will be called when you press <C-c>. And it will return to 
 * where you press <C-c>. If you are interesting in how it works, please
 * search for "Unix signal" in the Internet.
 */
static void control_C(int signum) {
	if(nemu_state == RUNNING) {
		nemu_state = INT;
	}
}

void init_signal() {
	/* Register a signal handler. */
	struct sigaction s;
	memset(&s, 0, sizeof(s));
	s.sa_handler = control_C;
	int ret = sigaction(SIGINT, &s, NULL);
	assert(ret == 0);
}

static void cmd_c() {
	if(nemu_state == END) {
		puts("The Program does not start. Use 'r' command to start the program.");
		return;
	}
	nemu_state = RUNNING;
	cpu_exec(-1);
	if(nemu_state != END) { nemu_state = STOP; }
}

static void cmd_r() {
	if(nemu_state != END) { 
		char c;
		while(1) {
			printf("The program is already running. Restart the program? (y or n)");
			fflush(stdout);
			scanf(" %c", &c);
			switch(c) {
				case 'y': goto restart_;
				case 'n': return;
				default: puts("Please answer y or n.");
			}
		}
	}

restart_:
	
	restart();
	nemu_state = STOP;
	cmd_c();
}

void main_loop() {
	char *cmd;bool suc;//char *temp=NULL;
	while(1) {
		cmd = rl_gets();
		if (temp!=0) cmd=temp;
		char *p = strtok(cmd," ");
		char *q=NULL;
		if(p == NULL) { continue;}
		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }	//r
		else if(strcmp(p, "q") == 0) { return; }	//q
		else if(strcmp(p,"si")==0)			//si 
		{
			suc=true;
			if (nemu_state==END) restart();
			nemu_state=STOP;
			q=strtok(NULL,"");
			if (q!=NULL) 
			cpu_exec(sixteenstring(q,10));
			else 			
			cpu_exec(1);
		}
		else if (strcmp(p,"info")==0)			//info 
		{
			q=strtok(NULL,"");
			if(strcmp(q,"r")==0) printreg();
			if(strcmp(q,"b")==0) printbreak();
		}
		else if (strcmp(p,"x")==0)			//x
		{
			suc=true;
			q=strtok(NULL," ");
			uint32_t N=sixteenstring(q,10);			
			q=strtok(NULL,"");
			suc=true;
			uint32_t addr=expr(q,&suc);	
			int cir_x=1;		
			if (judge) for (;cir_x<=N;cir_x++,addr++) {
			printf("%02x ",swaddr_read(addr,1));	
			if ((cir_x%5)==0) printf("\n");
			}	
			printf("\n");	
		}
		else if (strcmp(p,"b")==0)			//b
		{
			suc=true;
			q=strtok(NULL,"");
			expr(q,&suc);
			if (number_state==1) { int addr=expr(q+1,&suc); if (judge) new_bp(addr);}	
			q=strtok(NULL,"");
		}
		else if (strcmp(p,"d")==0)
		{
			q=strtok(NULL,"");
			if(sixteenstring(q,10)<=32&&sixteenstring(q,10)>=0) free_bp(sixteenstring(q,16));
			else printf("error NO\n");
		}
		else if(strcmp(p,"p")==0)			//si 
		{
			suc=true;
			q=strtok(NULL,"");
			int t=expr(q,&suc);
			if (judge)
			{if (number_state==2) printf("0x%08x\n",t);
			else printf("%d\n",t);}			
		}	
		else if(strcmp(p,"w")==0)
		{
			suc=true;
			q=strtok(NULL,"");
			uint32_t a=expr(q,&suc);a=a-1;
			if (judge) new_watch(q);	
		}
		/* TODO: Add more commands */
		else { printf("Unknown command '%s'\n", p); }
	}
}
