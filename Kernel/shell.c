#include <shell.h>
#include <libc.h>

static int  startedShell = 0;
static char username[] = "Sanchu";

void startShell()
{
    welcomeMessage();
    startedShell = 1;
    cursor();
}

void welcomeMessage(){
    if(startedShell>0){
        return;
    }
    printf("\n          +-+-+-+-+-+ +-+-+");
    printf("\n          |K|a|c|h|u| |o|s|");
    printf("\n          +-+-+-+-+-+ +-+-+\n\n\n");
}
 
void cursor(){
    printf("\n%s> ", username);
    //waitCommand();
}
