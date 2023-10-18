#include <syscalls.h>
#include <stdint.h>
#include <videoDriver.h>
#include <keyboard_driver.h>

void sys_write(char * str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen){
    for (int i = 0; str[i] != 0 && i < len; i++) 
	    write(str[i]);   
}

uint64_t sys_read(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint32_t r9){
	if(rsi == 5){//read userLen
		setVideoUserLen(rdx);
		return 1;
	}

	return getKeyChar();
}