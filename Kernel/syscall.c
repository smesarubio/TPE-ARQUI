#include <syscall.h> // VA EN USERMODULE
#include <naiveConsole.h>

void sys_write(const char *buffer, int length, int filedescriptor){
/*     if(filedescriptor==1){
        ncPrint(buffer);
    }else if(filedescriptor ==2)
    {
        ncPrintColor(buffer, RED, WHITE);
    } */

}

uint64_t _syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
