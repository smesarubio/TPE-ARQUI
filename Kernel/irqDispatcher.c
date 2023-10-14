#include <time.h>
#include <stdint.h>
#include <keyboard_driver.h>
#include <syscall.h>
#include <naiveConsole.h>
static void int_20();
static void int_21();
static void int_80();

void irqDispatcher(uint64_t irq,  uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8) {
	switch (irq){
		case 0:
			int_20();
			break;
		case 1:
			//ncPrint("Entra");
			int_21();
			break;
		case 0x60:
			int_80(rdi, rsi,  rdx,  rcx,  r8);
			break;
		}
	return;
}

void int_20() {
	
	timer_handler();
}

void int_21(){
	keyboard_handler(getKey());
}

void int_80( uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8){
	switch(rdi){
		case 1:
			sys_write((char*)rsi, rdx,rcx);
			break;
	}
}