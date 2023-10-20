#include <syscalls.h>
#include <colors.h>
#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	sys_write("dispacheando", 100, BACKGROUND, FOREGROUND, 0);
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	// Handler para manejar excepcíon
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("Excecpion : Opcode invalido.", 29, BACKGROUND, ERROR,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);

}