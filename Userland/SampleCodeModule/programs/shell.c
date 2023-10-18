#include <shell.h>
#include <libc.h>

static int  startedShell = 0;
static char username[] = "Sanchu";

void startShell()
{
    setUserLength(username);
    welcomeMessage();
    startedShell = 1;
    runShell();
}

void userPrint(){
    printf("\n %s > ", username);
}

static int getCommandArgs(char* userInput, char* command, char argv[MAX_ARGUMENTS][BUFFER_SIZE]) {
    int argc = 0;
    int i = 0;
    for(i = 0; userInput[i] != 0 && userInput[i] != ' '; i++) {
        command[i] = userInput[i];
    }
    command[i] = 0;
    int argIdx = 0;

    for(int j = 0; j < MAX_ARGUMENTS; j++) {
            argv[j][0] = 0;
    }

    while(userInput[i] != 0 && argc < MAX_ARGUMENTS) {
        i++;
        argIdx = 0;
        for(; userInput[i] != ' ' && userInput[i] != 0; i++, argIdx++) {
           argv[argc][argIdx] = userInput[i];
        }
        argv[argc][argIdx] = 0;
        argc++;
    }
    if(argc == MAX_ARGUMENTS && userInput[i] != 0)
        return -1;
    return argc;
}

void welcomeMessage(){
    if(startedShell>0){
        return;
    }
    printf("\n          +-+-+-+-+-+ +-+-+");
    printf("\n          |K|a|c|h|u| |o|s|");
    printf("\n          +-+-+-+-+-+ +-+-+\n\n\n");
}
 
void runShell(){
    char command[BUFFER_SIZE] = {0};
    char argv[MAX_ARGUMENTS][BUFFER_SIZE];
    char userInput[BUFFER_SIZE] = {0};
    int argc = 0;
    while (1)
    {
        userPrint();
        
        userInput[0] = 0;

        scanf("%s", userInput);
        
        argc = getCommandArgs(userInput, command, argv);

        if(argc == -1) {
            printf("\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos permitida es: %d.\n\n", MAX_ARGUMENTS);
        }
    }
}
