#include <time.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <stdlib.h>
static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
	if(ticks %(5*18)==0){
		//ncPrint(" [20 seconds have passed] ");
		//ncNewline();
		//scroll();
		// Seed the random number generator with the current time
		
	}
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

