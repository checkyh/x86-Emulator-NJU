extern bool judge;
extern int read_symtab(uint32_t lens);
void cpu_exec(uint32_t);
void restart();
extern void printreg();
extern void printbt();
extern uint32_t expr(char *e, bool *success);


//read for numbers
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