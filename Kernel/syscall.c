#include <syscall.h>
#include <naiveConsole.h>

void sys_write(const char *buffer, int length, int filedescriptor){
    if(filedescriptor==1){
        ncPrint(buffer);
    }else if(filedescriptor ==2)
    {
        ncPrintColor(buffer, RED, WHITE);
    }
}