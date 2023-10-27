#include <syscalls.h>
#include <stdint.h>
#include <videoDriver.h>
#include <keyboard_driver.h>
#include <text_driver.h>
#include <clock.h>

int clock();
static uint64_t registers[19] = {0};

void sys_write(char *str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen)
{
	if (str == 0 ||  len <= 0 || bgColor < 0 || ftColor < 0) 
        return ;
	for (int i = 0; str[i] != 0 && i < len; i++) 
	write(str[i], bgColor, ftColor);
}

void sys_clear(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint32_t r9){
	clear();
}

void sys_wait(uint64_t rsi, char rdx, uint64_t rcx, uint64_t r8, uint32_t r9){
	if(rsi == 1){//wait for char
		char c;
		while ((c = getKey()) != rdx);
	}
}

uint64_t sys_read(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint32_t r9){
	if(rsi == 5){//read userLen
		setVideoUserLen(rdx);
		return 0;
	}
	if(rsi == 6){
		return getBuffer();
	}
	if(rsi == 7){
		return getBuffSize();
	}
	if(rsi == 8){
		return getChar();
	}
	

	//return getKeyChar();
	return 0;
}

uint64_t sys_inforeg(){
	return registers;
}

void updateRegisters(uint64_t* rsp){
    for (int i=0 ; i<19;i++) {
        registers[i] = rsp[i]; 
    } 
}

uint8_t sys_rtc(uint64_t id){
	uint8_t time;
	if (id == HOURS){
		time = clock(id) + TIME_ZONE;
	}else {
		time = clock(id);
	}
	uint8_t final = ((time >> 4) * 10 + (time & 0xf));
    return final; 
}