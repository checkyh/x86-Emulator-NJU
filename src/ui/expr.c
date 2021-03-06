#include "common.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
int number_state=0;
enum {
	NOTYPE = 256, MULT=22,DIV=21,ADD=24,MINUS=23,STRING=1,EQ=15,LEFT=-1,RIGHT=-2,DEREF=3,REG=4,MOD=20,LESS=19,GREATER=18,
	LESSEQ=17,GREATEQ=16,NEQ=14,ALSO=13,ORSO=12,NOT=11,SHIFTL=10,SHIFTR=9,AND=8,OR=7,CRA=6,FAN=5,IMPO=2

	/* TODO: Add more token types */

};

static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",NOTYPE},				// white space
	{"\\*",MULT},
	{"\\+",ADD},					// plus
	{"\\-",MINUS},
	{"==",EQ},			
		// equal
	{"[a-zA-Z0-9_]+",STRING},
	{"\\/",DIV},
	{"\\(",LEFT},
	{"\\)",RIGHT},
	{"\\$",REG},
	{"\\%",MOD},
	{"<=",LESSEQ},
	{">=",GREATEQ},
	{"<<",SHIFTL},
	{">>",SHIFTR},
	{"<",LESS},
	{">",GREATER},
	{"!=",NEQ},
	{"\\&&",ALSO},
	{"\\|\\|",ORSO},
	{"!",NOT},
	{"\\&",AND},
	{"\\|",OR},
	{"\\^",CRA},
	{"\\~",FAN}
	
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for more times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {				//在main 调用了
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			test(0, "regex compilation failed: %s\n%s\n", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[100];
int nr_token;
int stop;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;
	
	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				//char *substr_start=e +position;
				int substr_len = pmatch.rm_eo;
				//Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);

				position += substr_len;


				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch(rules[i].token_type) 
				{
					case NOTYPE:break;
					case STRING:tokens[nr_token].type=STRING;memset(tokens[nr_token].str,0,32);
						int j=0;for (;j<substr_len;j++)
						tokens[nr_token].str[j]=e[-substr_len+j+position];
						nr_token++; break;
					default:tokens[nr_token].type=rules[i].token_type;nr_token++;
				}
				break;
			}
			
		}
		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}
	

	return true; 
}
bool check_parentheses(int p,int q)
{
	if (tokens[p].type==LEFT)
	{
		int leftmost=1,cou=p+1;
		for (;cou<=q-1;cou++) { 
		
		if (leftmost<=0) return 0;
		if (tokens[cou].type==LEFT) leftmost++;		
		if (tokens[cou].type==RIGHT) leftmost--;
		
		}
		if (tokens[q].type==RIGHT&&leftmost==1) return true;
		else return false;
		
	}
	else return false;
}
extern uint32_t regfinder(char *q);
extern uint32_t sixteenstring(char *q,int step);
extern uint32_t swaddr_read(swaddr_t addr, size_t len);
extern int symmatch(char *expr);
extern uint32_t symvalue(int num);
bool judge=true;
uint32_t eval(int p,int q) {
	uint32_t val1,val2;
    	if(p > q) {
	judge=false;return 0;
    	}
   	else if(p == q) { 
    	if (tokens[p].type==STRING)
  	{
  		int num=symmatch(tokens[p].str);
  		if(num!=-1)
		{
			number_state=2;
			return symvalue(num);
		}
		if (tokens[p].str[0]=='0'&&tokens[p].str[1]=='x')
		{
			number_state=2;
    			return sixteenstring(&tokens[p].str[2],16);
    		}
    		else return sixteenstring(tokens[p].str,10);
    	}
	else {judge=false;return 0;}
    }
    else if(check_parentheses(p, q) == true) {
	 return eval(p + 1, q - 1); 	
    }
    else {
    	int cou=p,op_type=0,op=0;
    	for (cou=p;cou<=q;)
    	{	
    	if (tokens[cou].type==LEFT) 
    		{
    			int count=1; 
    			while (count!=0) 
    			{
    			 cou++;
    			 if (cou>q) {judge=false;break;}
    			 if (tokens[cou].type==LEFT) count++;
    			 if (tokens[cou].type==RIGHT) count--;		   	
    			}	
    		}
    	if (tokens[cou].type>op_type) {op_type=tokens[cou].type;op=cou;}
    	cou++;	
    	}
    	val1=0;
	if (op_type>5) val1 = eval(p, op - 1);
	
	val2 = eval(op + 1, q); 
	switch(op_type) {
	    case EQ:return (val1==val2);
	    case ADD: return val1 + val2;
	    case MINUS: return  val1-val2;
	    case MULT: return val1*val2;
	    case DIV: return val1/val2;
	    case DEREF:number_state=1;return swaddr_read(val2,4);
	    case REG:number_state=2;
	    if(tokens[op+1].type==STRING) 
	    return regfinder(tokens[op+1].str); else {judge=false;return 0;}
	    case MOD:return val1%val2;
	    case LESS:return (val1<val2);
	    case GREATER:return (val1>val2);
	    case LESSEQ:return (val1<=val2);
	    case GREATEQ:return (val1>=val2);
	    case NEQ:return (val1!=val2);
	    case ALSO:return (val1&&val2);
	    case ORSO:return (val1||val2);
	    case AND:return (val1&val2);
	    case OR:return(val1|val2);
	    case NOT:return (!val2);
	    case SHIFTL:return (val1<<val2);
	    case SHIFTR:return(val1>>val2);
	    case CRA:return (val1^val2);
	    case FAN:return(~val2);
	    case IMPO:return (0-val2);
	    default:judge=false;return 0;
	}	
	}
}
uint32_t expr(char *e, bool *success) {
	number_state=0;
	judge=true;
	
	if(!make_token(e)) {
		*success = false;
		return 0;
	}

	int i;
	for(i = 0; i < nr_token; i ++)
	 {
    	if(tokens[i].type ==MULT && (i == 0 || ((tokens[i - 1].type!=STRING)&&(tokens[i-1].type!=RIGHT))) )
		tokens[i].type = DEREF;
		if(tokens[i].type ==MINUS && (i == 0 || ((tokens[i - 1].type!=STRING)&&(tokens[i-1].type!=RIGHT))) )
		tokens[i].type = IMPO;
    	}
	int cou=0,count=0;
			while (cou<=nr_token-1) 
    			{
    			 
    			 if (tokens[cou].type==LEFT) count++;
    			 if (tokens[cou].type==RIGHT) count--;cou++;	
    			}	
			if (count>0) {printf("more ( than )\n");judge=false;goto Judg;}
			if (count<0) {printf("more ) than (\n");judge=false;goto Judg;}
	

	/* TODO: Implement code to evaluate the expression. */
	uint32_t sult=eval(0,nr_token-1);
Judg:
	if (judge) return sult;
	
	if (judge==false){
	printf("bad expression\n");
	return 0;
	}
	return 0;
}
