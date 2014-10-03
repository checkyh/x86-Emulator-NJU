#include "common.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>

enum {
	NOTYPE = 256, MULT=3,DIV=4,ADD=5,MINUS=6,STRING=2,EQ=7,LEFT=-1,RIGHT=-2,DEREF=1

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
	{"==",EQ},				// equal
	{"[a-zA-Z0-9]+",STRING},
	{"\\/",DIV},
	{"\\(",LEFT},
	{"\\)",RIGHT}
	
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

Token tokens[32];
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
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match regex[%d] at position %d with len %d: %.*s", i, position, substr_len, substr_len, substr_start);

				position += substr_len;


				/* TODO: Now a new token is recognized with rules[i]. 
				 * Add codes to perform some actions with this token.
				 */

				switch(rules[i].token_type) 
				{
					case NOTYPE:break;
					case EQ:tokens[nr_token].type=EQ;nr_token++;break;
					case ADD:tokens[nr_token].type=ADD;nr_token++;break;
					case MINUS:tokens[nr_token].type=MINUS;nr_token++;break;
					case STRING:tokens[nr_token].type=STRING;
						int i=1;for (i=position-substr_len;i<=position;i++)
						tokens[nr_token].str[i-position+substr_len]=*(e+i);
						nr_token++;break;
					case MULT:tokens[nr_token].type=MULT;nr_token++;break;
					case DIV:tokens[nr_token].type=DIV;nr_token++;break;
					case LEFT:tokens[nr_token].type=LEFT;nr_token++;break;
					case RIGHT:tokens[nr_token].type=RIGHT;nr_token++;break;
					default: break;
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
		for (;cou<=q-1;cou++) { if (tokens[cou].type==LEFT) leftmost++;
					if (tokens[cou].type==RIGHT) leftmost--;
					}
		if (tokens[q].type==RIGHT&&leftmost==1) return true;
		else return false;
		
	}
	else return false;
}

extern uint32_t sixteenstring(char *q,int step);
uint32_t eval(int p,int q) {
	uint32_t val1,val2;
    if(p > q) {
	return 0;
    }
    else if(p == q) { 
    	if (tokens[p].str[0]=='0'&&tokens[p].str[1]=='x')
    	return sixteenstring(tokens[p+2].str,16);
    	else
    	return sixteenstring(tokens[p].str,10);
    }
    else if(check_parentheses(p, q) == true) {

	 return eval(p + 1, q - 1); 
	
    }
    else {
    	int cou,op_type=0,op=0;
    	for (cou=p;cou<=q;cou++)
    	{if (tokens[cou].type==LEFT) while (tokens[cou].type!=RIGHT) {cou++;}	
    	if (tokens[cou].type>op_type) {op_type=tokens[cou].type;op=cou;}
    	}
    	
	val1 = eval(p, op - 1);
	 val2 = eval(op + 1, q);
 
	switch(op_type) {
	    case EQ:return (val1==val2);
	    case ADD: return val1 + val2;
	    case MINUS: return  val1-val2;
	    case MULT: return val1*val2;
	    case DIV: return val1/val2;
	    case DEREF:return val2;
	    case 0: return 0;
	    default:return 0;
	}
			
	}
}

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
	int i;
	for(i = 0; i < nr_token; i ++)
	 {
    		if(tokens[i].type == '*' && (i == 0 || tokens[i - 1].type ==LEFT) ) {
		tokens[i].type = DEREF;}
    	}
	printf("%d\n",eval(0,nr_token-1));	
	/* TODO: Implement code to evaluate the expression. */
	return 0;
}
