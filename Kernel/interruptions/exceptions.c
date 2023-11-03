#include <syscalls.h>
#include <colors.h>
#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

char * registersNames[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RSP", "RIP"};

uint32_t changeBase(uint64_t value, char *buffer, uint32_t base);

static void zero_division();
static void opcode();

void exceptionDispatcher(int exception, uint8_t * regs) {
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

static void opcode(uint64_t regs[17]){
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	sys_write("Exception : invalid opcode operation.", 29, BACKGROUND, ERROR,0);
	sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	for(int i=0;i<17;i++){
		char buffer[64] = {'0'};
		int a = regs[i];
		changeBase(a, buffer, 16);
		sys_write(registersNames[i], 10, BACKGROUND, FOREGROUND, 0);
		sys_write(": ",10,BACKGROUND,FOREGROUND,0);
		/*if(a==0){
			sys_write("0",10,BACKGROUND,FOREGROUND,0);
			
		}
		while(a!=0){
			char * c;
			c[0]= a%10+'0';
			sys_write(c,10,BACKGROUND,FOREGROUND,0);
			a=a/10;
		}*/
		sys_write(buffer, 10, BACKGROUND, FOREGROUND, 0);
		sys_write("\n",1,BACKGROUND, FOREGROUND,0);
	}
	return;
}


uint32_t changeBase(uint64_t value, char *buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	// Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	} while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	// Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}