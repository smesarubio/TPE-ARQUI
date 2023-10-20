
#define ZERO_EXCEPTION_ID 0

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

static void zero_division() {
	// Handler para manejar excepcíon
	printLine();
	sys_write("Excecpion : Opcode invalido.", 29, BLACK, RED,0);
	printLine();
	printLine();
}