#include <libc.h>
#include <stdint.h>
#include <stdlib.h>
#include <commands.h>
#include <syscalls.h>
#include <clock.h>
#include <snake.h>

void zero_division_exception();
void opcodeExp();
#define REGISTERS_SIZE 17

void help(){
    printf("\n Available commands:\n");
    printf("\nhelp\ndivzero\ninforeg\nclear\nclock\nsnake\nplayer2");
    //printf("\nhelp\ndivzero\ninforeg\nclear\nclock\nopcode\n");
}

void divzero(){
   int x = 1;
   int y = 0;
   int exception = x/y;
    //_syscall(SYS_EXIT_ID, 0, 0, 0, 0, 0);
}

void opCode(){
    _opcodeExp();
    return;
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
    printf(" The current time is:");
    timeFormat();
}

//formato de la hora
void timeFormat(){
    char rta[7];
    rta[2] = rta[5] = ':';
    uint64_t h = getTime(HOURS);
    rta[0] = (h / 10) % 10 + '0';
    rta[1] = h % 10 + '0';
    uint64_t min = getTime(MINUTES);
    rta[3] = (min / 10) % 10 + '0';
    rta[4] = min % 10 + '0';
    uint64_t sec = getTime(SECONDS);
    rta[6] = (sec / 10) % 10 + '0';
    rta[7] = sec % 10 + '0';
    printf(" %s\n", rta);
}

void snake(){
    if (!startGame(1)){
        return;
    }
}
void player2(){
    if (!startGame(2)){
        return;
    }
}