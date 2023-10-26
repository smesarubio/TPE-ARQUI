#include <libc.h>
#include <stdint.h>
#include <stdlib.h>
#include <commands.h>
#include <syscalls.h>
#include <clock.h>

#define REGISTERS_SIZE 17

void help(){
    printf("\n Available commands:\n");
    printf("\nhelp\ndivzero\ninforeg\nclear\nclock");
}

void divzero(){
    int x = 1;
    int y = 0;
    //int resul = x / y;
}

char * registersNames[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RSP", "RIP"};

void registersinfo(){
    printf("\nRegistros: \n");
    uint64_t* regs = (uint64_t *) _syscall(SYS_INFOREG_ID, 0, 0, 0, 0, 0);
    for(int i = 0 ; i < REGISTERS_SIZE ; i++){
        printf(" %s:\t%x\n",registersNames[i], regs[i]);
    }

}

void clearScreen(){
    clearSc();
}

void  rtclock(){
    uint64_t date = getTime(DAYS);
    uint64_t month = getTime(MONTH);
    uint64_t year = getTime(YEAR);
    uint64_t hour = getTime(HOURS + TIME_ZONE);
    uint64_t minutes = getTime(MINUTES);
    uint64_t seconds = getTime(SECONDS);
    printf("The current date and time is:");
    dateFormat(date, month, year);
    timeFormat(hour, minutes, seconds);
}

//formato de la hora
void timeFormat(uint8_t h, uint8_t min, uint8_t sec){
    char rta[7];
    rta[2] = rta[5] = ':';
    rta[0] = (h / 10) % 10 + '0';
    rta[1] = h % 10 + '0';
    rta[3] = (min / 10) % 10 + '0';
    rta[4] = min % 10 + '0';
    rta[6] = (sec / 10) % 10 + '0';
    rta[7] = sec % 10 + '0';
    printf(" %s\n", rta);
}
//formato de la fecha
void dateFormat(uint8_t d, uint8_t m, uint8_t y){
    char rta[7];
    rta[2] = rta[5] = '/';
    rta[0] = (d / 10) % 10 + '0';
    rta[1] = d % 10 + '0';
    rta[3] = ( m / 10) % 10 + '0';
    rta[4] = m % 10 + '0';
    rta[6] = (y / 10) % 10 + '0';
    rta[7] = y % 10 + '0';
    printf(" %s ", rta);
}