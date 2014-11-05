#include "ui/ui.h"
#include "ui/breakpoint.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "ui-head.h"
extern int number_state;

int nemu_state = END;

char tp[200];char backup[200];
char *temp1=tp;char *temp2=backup;
int readlinefun_state=0;
/* We use the readline library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;
	if (line_read) {
		free(line_read);
		line_read = NULL;
	}
	line_read=readline("(nemu) ");
	
	if (line_read && *line_read) {
		readlinefun_state=0;
		add_history(line_read);
		sprintf(temp1,"%s",line_read);
		 return line_read;
	}	
	else {
		if (readlinefun_state==1) sprintf(temp1,"%s",temp2);
		if (readlinefun_state==0) {sprintf(temp2,"%s",temp1);readlinefun_state=1;}
		return (temp1);
	}
	
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
			if(q!=NULL){
			if(strcmp(q,"r")==0) printreg();
			if(strcmp(q,"b")==0) printbreak();}
		}
		else if (strcmp(p,"x")==0)			//x
		{
			suc=true;
			q=strtok(NULL," ");
			if (q!=NULL){
			uint32_t N=sixteenstring(q,10);			
			q=strtok(NULL,"");
			suc=true;
			uint32_t addr=expr(q,&suc);	
			int cir_x=1;		
			if (judge) for (;cir_x<=N;cir_x++,addr++) {
			printf("%02x ",swaddr_read(addr,1));	
			if ((cir_x%5)==0) printf("\n");
			}	
			if (cir_x<=4) printf("\n");
		}
		}
		else if (strcmp(p,"b")==0)			//b
		{
			suc=true;
			q=strtok(NULL,"");
			if (q!=NULL)
			{
			expr(q,&suc);
			if (number_state==1) { int addr=expr(q+1,&suc); if (judge) new_bp(addr);}	
			q=strtok(NULL,"");
		}
		}
		else if (strcmp(p,"d")==0)
		{
			q=strtok(NULL,"");
			if (q!=NULL)
			{if(sixteenstring(q,10)<=32&&sixteenstring(q,10)>=0) free_bp(sixteenstring(q,16));
			}
			else printf("error NO\n");
		}
		else if(strcmp(p,"p")==0)			//si 
		{
			suc=true;
			q=strtok(NULL,"");
			if (q!=NULL){
			int t=expr(q,&suc);
			if (judge)
			{if (number_state==2) printf("0x%08x\n",t);
			else printf("%d\n",t);}	}		
		}	
		else if(strcmp(p,"p/x")==0)			//si 
		{
			suc=true;
			q=strtok(NULL,"");
			if (q!=NULL){
			int t=expr(q,&suc);
			if (judge)
			 printf("0x%08x\n",t);}	
		}	
		else if(strcmp(p,"p/d")==0)			//si 
		{
			suc=true;
			q=strtok(NULL,"");
			if (q!=NULL){
			int t=expr(q,&suc);
			if (judge)
			 printf("%d\n",t);}	
		}	
		else if(strcmp(p,"w")==0)
		{
			suc=true;
			q=strtok(NULL,"");
			if (q!=NULL){
			uint32_t a=expr(q,&suc);a=a-1;
			if (judge) new_watch(q);}	
		}
		else if(strcmp(p,"re")==0)			//si 
		{
			suc=true;
			q=strtok(NULL,"");
			if (q!=NULL)
			read_symtab(sixteenstring(q,10)); 
				
		}
		/* TODO: Add more commands */
		else { printf("Unknown command '%s'\n", p); }
	}
}
