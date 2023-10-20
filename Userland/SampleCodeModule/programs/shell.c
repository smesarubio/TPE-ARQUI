#include <shell.h>
#include <libc.h>
#include <commands.h>

static int  startedShell = 0;
static char username[] = "Sanchu";
static char commandList[][30] = {"help","divzero",0};
void (*commandFuncts[])() = {help, divzero};

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
    logo();
    /*     printf("\n          +-+-+-+-+-+-+ +-+-+");
        printf("\n          |Z|a|0|S|e|X| |o|s|");
        printf("\n          +-+-+-+-+-+-+ +-+-+\n\n\n"); */
    /*     printf("\n          +-+-+-+-+-+ +-+-+");
        printf("\n          |K|a|c|h|u| |o|s|");
        printf("\n          +-+-+-+-+-+ +-+-+\n\n\n"); */
}
 

void cnf(){
    printf("\ncommand not found\n\n");
}

void runShell(){
    while (1)
    {
        char command[BUFFER_SIZE] = {0};
        char userInput[BUFFER_SIZE] = {0};
        char argv[MAX_ARGUMENTS][BUFFER_SIZE];
        int argc = 0;
        int inputSize = 0;
        char c=0;
        userPrint();
        while (c != '\n' )
        {
            c = readChar();
            if(c!='\n' && c!=0){
                if(c == '\b'){
                    inputSize--;
                }else{
                    userInput[inputSize++] = c;
                }
            }
            putChar(c);
        }
        if(inputSize==0){
            cnf();
        }else{
            argc = getCommandArgs(userInput, command, argv);
            if(argc == -1) {
                printf("\nIngreso argumentos de mas.\nLa maxima cantidad de argumentos permitida es: %d.\n\n", MAX_ARGUMENTS);
            }
            for (int i = 0; commandList[i][0]!=0; i++)
            {
                if(strcmp(command,commandList[i])==0){
                    commandFuncts[i]();
                }
            }
        }

    }
}


void logo(){
    printf("\n");
    printf("                                                                      :\n");
    printf("                                                                       :\n");
    printf("                                                                     ::\n");
    printf("                                                                     :::\n");
    printf("                                                                     ::::\n");
    printf("                                                                    .::::.\n");
    printf("                                                                    ::::::.\n");
    printf("                                                                   :::::::::\n");
    printf("                                                                  :::::::::::                                           .\n");
    printf("                                                                 :::::::::::::                                         ::\n");
    printf("                                                                :::::::::::::::                                      .::\n");
    printf("                                                              :::::::::::::::::                                    .:::\n");
    printf("                                                             ::::::::::::::::::                                  .:::::\n");
    printf("                                                            :::::::::::::::''''                                .::::::\n");
    printf("                                                           :::::::::::',,cd$$$$$$$$$$hcc,.                  .:::::::::\n");
    printf("                                                         :::::::'`.,cc$$$$$$$$$$$$$$$$$$$$$$c,.         ..:::::::::::'\n");
    printf("                                                        :::::: ,c$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$h   ..::::::::::::::::\n");
    printf("                                                       ::::: ,$$P\"\',$$P\"\"$$$$$$$$$$$$$$$$$$PF\"\"..::::::::::::::::::::\n");
    printf("                                                       ::: ,$$\",c$$$\",d$$$$$$$$$$$$$$$P\"\".::::::::::::::::::::::::::\n");
    printf("                                                      ::: J$$$$$$$$$$$$$$$$$$$$$$P\"\'.:::::::::::::::::::::::::::::::\n");
    printf("                                                     ::: $$$$$$$$$$$$$$$$$$$$P\".::::::::::::::::::::::::::::::::::::\n");
    printf("                                                     :: J$$$$$$$$$$$$$$$$$$P\':::::::::::::::::::::::::::::::::::::::\n");
    printf("                                                     :: ?$$$$$$$$$$$$$$$P\".:::::::::::::::::::::::::::::::::::::::::\n");
    printf("       Wolverine OS                                 .::: $$$$$$$$$$$$$\".::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("                                                    `::::`?$$$$\"3$$$$\':::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("                                                     ::::: ?$$F,$$$$':::::::::::::::::::::::::::::::::::`:::::::::'\n");
    printf("                                                     :::::: \"P $F3$\'::::::::::::::::::::::::::::::`. '`:: `::::::'\n");
    printf("                                                    ```:::::: <$ $$ ::::::::````:::::::::::::::::` :: : :: :::::\n");
    printf("       Press ENTER to start                            =cc,`:  \" \"\" :::\'\`,cc$$$ `::::::::::::::::::`:`  :::::::\n");
    printf("                                                       :.`"" d$$$$$ ::  `???"".::::::::::::::::::::` : :: ::'`\n");
    printf("                                                      ::::: d$$$$F :::::::::::::::::::::::::::::::::: :: ',,cc,\n");
    printf("                                                      ::::'J$$$$$> ::::::::::::::::::::::::::::::::::'`,c$$$$$$$h,\n");
    printf("                                                      `::: $$$$P'::::::::::::::::::::::::::::::::::::<$$$$$$$$$$$$$,?$$$ccccc,.\n");
    printf("                                                         ` $$$P :::::::::``````::::::::::::::::::::::<$$$$$$$$$$$$$$cJ$$$$$$$$$\n");
    printf("                                                        '$ ??\" `.,,cccccc$$$$$$ccc,``::::::::::::::: J$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("                                                         $$hh$$$$$$$$$$h,\"?$$$$$$$$$.`::::::::::::: c$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("                                                         ?$??$$?????$$$$$$$c.`\"$$$$$ ::::::::::::: ,$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("                                                          $$ec :;;;;;;;, \"$$$$c $$$$ :::::::::::: J$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    printf("                                                          $$$$,,`'''`,,ccc$$$$$,\"$$$> :::::::``  $$$$$$$$$$$$$$$$$$$$$$$$$$$$P\"\n");
    printf("                                                          4$\",$$$$$$$$$$$$$$$$$$c$$$\':::``,ccc$  $$$$$$$$$$$$$$$$$$$$$$$$$$$\".:\n");
    printf("                                                          4$$cccc,,$$$$$$$$$$$$$$??\".,,c$$$$$$$  $$$$$$$$$$$$$$$$$$F,z$$$$\" :::\n");
    printf("                                                        :: \"$$$$$$$$$$$$$$$$P\",, d\")C3$$$$$$$$$> $$$$$$$$$$$$$$$P\",c$$$$$\" ::::\n");
    printf("                                                       ::::.\"???$$$$$$$$$P\"..\" \"L\'$ccc?$$$$$$$$$ ?$$$$$$$$$$$$$P z$$$$$$F :::::\n");
    printf("       v0.1                                            :::::::::::.."""".::\',c  `ccc==-3$$$$$$$$h`$$$$$$$$$$$$\",,$$$$$$$ ::::::\n");
    printf("                                                       :::::::::::::::::::\',$F\': .`??\",`?$$$$$$$$c$$$$$$$$$$$F, d$$$$$$F ::::::\n");
    printf("                                                        :::::::::::::::::: $$F::::`?cc,\"?$$$$$$$$$$$$$$$$$$$$,L$$$$$$$$ ::::```\n");
    printf("                                                         ::::::::::::::::\'J$$\':::: zc,\"=-\"\"?$$$$$$$$$$$$$$$$$$$$$$$PF\" .::::::\n");
    printf("                                                          `:::::::::::::: $$$ ::::<$$$$$$cc,,,J$$$$$$$$$$$$$$$$$P\",c$\" :::::: d\n");
    printf("                                                           `::::::::::::: $$$,:::\'<$$$$$$$$$$$$$$$$$$$$$$$$P\",zd$$$$$ :````` ??\n");
    printf("                                                            `:::::::::::: $$$L`:: $$$$$$$$$$$$$??$$$$$$??$$$$$$$$$P"".:::: z$$$\n");
    printf("                                                              ::::::::::: $$$$ :: $$$$$$$$$$$$$bc,\"??\",cd$$$$$$$$$d$ :::::<$$$$\n");
    printf("                                                               `::::::::: ?$$$c`: $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$h`::: $$$$$\n");
    printf("                                                                ,`:::::::.`$$$$,` $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ :::,$$$$$\n");
    printf("                                                                $$c,`::::: ?$$$$, 3$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$c`: $$$$$$\n");
    printf("                                                                $$$$bc``::: $$$$$cd$$$$$$$$$$$$$$$ d$$$$$$$$$$$$$$$$$$ : $$$$$$\n");
    printf("                                                                 $$$$$$c,`::`$$$$$$$$$$$$$$$$$$$$ d$$$$$$$$$$$$$$$$$$$h` $$$$$$\n");
    char c;
    while (c != '\n'){
        c = readChar();
    }
    wipeScreen();
}
