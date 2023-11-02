#include <syscalls.h>
#include <colors.h>
#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

char * registersNames[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RSP", "RIP"};



static void zero_division();
static void opcode();

void exceptionDispatcher(int exception, uint8_t regs[]) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if(exception == OPCODE_EXCEPTION_ID)
		opcode(regs);
	return;
}

static void zero_division() {
	// Handler para manejar excepcíon
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("Exception : Divide by zero.", 29, BACKGROUND, ERROR,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	return;
}

static void opcode(uint8_t regs[]){
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("Exception : invalid opcode operation.", 29, BACKGROUND, ERROR,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	for(int i=0;i<17;i++){
		int a = regs[i];
		sys_write(registersNames[i],10,BACKGROUND,FOREGROUND,0);
		sys_write(": ",10,BACKGROUND,FOREGROUND,0);
		if(a==0){
			sys_write("0",10,BACKGROUND,FOREGROUND,0);
			
		}
		while(a!=0){
			char * c;
			c[0]= a%10+'0';
			sys_write(c,10,BACKGROUND,FOREGROUND,0);
			a=a/10;
		}
		sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	}
	return;
}
