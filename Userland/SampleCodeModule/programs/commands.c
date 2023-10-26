#include <libc.h>
#include <stdint.h>
#include <stdlib.h>
#include <commands.h>
#include <syscalls.h>
#include <clock.h>

#define REGISTERS_SIZE 17

void help(){
    printf("\n Available commands:\n");
    printf("\nhelp\ndivzero\ninforeg\nclear");
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
    uint64_t hour = getTime(HOURS);
    uint64_t minutes = getTime(MINUTES);
    uint64_t seconds = getTime(SECONDS);
    printf("The current date and time is: %s %s",dateFormat(date, month, year), timeFormat(hour, minutes, seconds));
}