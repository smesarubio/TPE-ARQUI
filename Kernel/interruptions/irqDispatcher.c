#include <time.h>
#include <stdint.h>
#include <keyboard_driver.h>
#include <syscalls.h>
#include <syscallDispatcher.h>
#include <naiveConsole.h>
static void int_20();
static void int_21();
static void int_80(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

void irqDispatcher(uint64_t irq,  uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
	switch (irq){
		case 0:
			int_20();
			break;
		case 1:
			//ncPrint("Entra");
			int_21();
			break;
		case 0x60:
			int_80(&irq, rdi, rsi,  rdx,  rcx,  r8, r9);
			break;
		}
	return;
}

void int_20() {
	
	timer_handler();
}

void int_21(){
	keyboard_handler();
}

void int_80(uint64_t irq,uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
	syscall_selector(irq, rdi, rsi, rdx, rcx, r8, r9);
}