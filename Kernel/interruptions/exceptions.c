#include <syscalls.h>
#include <colors.h>
#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

static void zero_division();
static void opcode();

void exceptionDispatcher(int exception, uint8_t regs[]) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if(exception == OPCODE_EXCEPTION_ID)
		opcode();
	return;
}

static void zero_division() {
	// Handler para manejar excepcíon
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("Exception : Divide by zero.", 29, BACKGROUND, ERROR,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	return;
}

static void opcode(){
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("Exception : invalid opcode operation.", 29, BACKGROUND, ERROR,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	return;
}
