#include "exec/helper.h"
#include "common.h"
#include "memory.h"
extern char suffix;
make_helper (call)
{
	uint32_t call_addr;
	int call_ins = instr_fetch(eip, 1);
	int lens=0;
	switch(call_ins)
	{
		case (0xe8):	call_addr=instr_fetch(eip+1,4);lens+=5;cpu.eip+=call_addr;break;
	}
	print_asm("call 0x%x",cpu.eip+lens);	
	return lens;
}
make_helper(leave)
{
	/*IF StackAddrSize = 16
	THEN
 	  SP <- BP;
ELSE (* StackAddrSize = 32 *)
   ESP <- EBP;
FI;
IF OperandSize = 16
THEN
   BP <- Pop();
ELSE (* OperandSize = 32 *)
   EBP <- Pop();
FI;*/


	return 1;
}