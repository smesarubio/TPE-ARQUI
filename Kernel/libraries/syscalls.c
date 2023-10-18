#include <syscalls.h>
#include <stdint.h>
#include <videoDriver.h>
#include <keyboard_driver.h>

void sys_write(char * str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen){
    for (int i = 0; str[i] != 0 && i < len; i++) 
	    write(str[i]);   
}

uint64_t sys_read(){
	return getKeyChar();
}