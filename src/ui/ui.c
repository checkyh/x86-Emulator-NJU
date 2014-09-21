#include "ui/ui.h"

#include "nemu.h"

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int nemu_state = END;
void cpu_exec(uint32_t);
void restart();
void printreg();

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
	char *cmd;
	while(1) {
		cmd = rl_gets();
		char *p = strtok(cmd, " ");

		if(p == NULL) { continue; }

		if(strcmp(p, "c") == 0) { cmd_c(); }
		else if(strcmp(p, "r") == 0) { cmd_r(); }
		else if(strcmp(p, "q") == 0) { return; }
		else if(strcmp(p,"si")==0)
		{
			if (nemu_state==END) restart();
			nemu_state=STOP;
			char *q=strtok(NULL," ");
			uint32_t step=0;
			while ((unsigned int)(*q-48)<10&&(unsigned int)(*q-48)>=0)
			{
				step=step*10+(*q-48);
				q++;
			}			
			cpu_exec(step);
		}
		else if (strcmp(p,"info")==0)
		{
			char *q=strtok(NULL," ");
			if(strcmp(q,"r")==0) printreg();			
		}
		else if (strcmp(p,"x")==0)
		{
			char *q=strtok(NULL," ");
			uint32_t N=*q-48;
			q=strtok(NULL," ");
			q+=2;
			int temp;
			uint32_t addr=0;
			bool readOK=1;
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
				       default: readOK=0;
				}
				if (readOK)
				{
					addr=addr*16+temp;
					q++;
				}
			}while (readOK);
			for (;N>0;N--,addr++) printf("%d\n",swaddr_read(addr,1));			
		}

		/* TODO: Add more commands */

		else { printf("Unknown command '%s'\n", p); }
	}
}
