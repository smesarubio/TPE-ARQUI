#include <libc.h>
#include <stdint.h>
#include <stdlib.h>
#include <registers.h>

void help(){
    printf("\n Los programas disponibles son:\n");
    printf("\n divzero\n inforeg\n");
}

void divzero(){
    int x = 1;
    int y = 0;
    //int resul = x / y;
}

char * registersNames[] = {"R15","R14","R13","R12","R11","R10","R9","R8","RSI","RDI","RBP","RDX","RCX","RBX","RAX","RSP","RIP","CS","FLAGS"};

void registersinfo(){

    registers regInfo;
    uint64_t * regs = (uint64_t *)&regInfo;
    printf("\nRegistros: \n");
        
    for(int i = 0 ; i < REGISTERS_SIZE ; i++){
        printf(" %s\t%d\n",registersNames[i],regs[i]);
    }

}