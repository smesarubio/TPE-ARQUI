#include <lib.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <keyboard_driver.h>
#include <stdint.h>
#include <shell.h>


#define PRESS 1
#define RELEASE 2
#define ERROR -1

#define BUFF_LEN 30
static int buffSize=0; //cantidad de elementos del buffer
static int ridx=0; //posicion de escritura
static int widx=0; //posicion de lectura

#define LEFT_SHIFT 0x2A
#define RIGHT_SHIFT 0x36
#define CAPS_LOCK 0x3A
#define CTRL 0x1D

static char buffer[BUFF_LEN]={0};

static int shift = 0;
static int ctrl = 0;
static int capsLock = 0;


static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
'\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 
'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 0, 0 };


void keyboard_handler(){
    int key = getKey();
    static int capsLockOn = 0;

    if (key == 0x3A) { // Caps Lock press
        capsLockOn = 1 - capsLockOn; // Toggle the Caps Lock status
    }

    if (key == 0xBA) { // Caps Lock release
        // Don't change the Caps Lock status here, as it's typically only changed on press.
    }

    if(key == 0x39){ // space
        ncPrint(" ");
        write(' ');
        // paint(0xd61c44);
        return;
    }
    if(ScanCodes[key] == '\b'){
        ncBackspace();
        printBackspace();
        return;
    }
    if(ScanCodes[key] == '\t'){
        ncPrint("    ");
        putInBuffer('\t');
        printTab();
        return;
    }
    if(ScanCodes[key] == '\n'){
        //printInScreen(buffer, buffSize);
        printCoso();
        printNewLine();
        return;
    }
    if( key >= 0 && key <= 256 && ScanCodes[key] != 0 ){
        if (capsLockOn) {
            ncPrintChar(ScanCodes[key] - ('a' - 'A'));
            write(ScanCodes[key] - ('a' - 'A') );
            putInBuffer(ScanCodes[key]-('a'-'A'));
        }
        else
        {
            ncPrintChar(ScanCodes[key]);
            write(ScanCodes[key]);
            putInBuffer(ScanCodes[key]);
        }
        return;
    }
    return;
}

void putInBuffer(char c){
    buffer[buffSize++] = c;
}

char getKeyChar(){
    char c=0;
    c=removeCharFromBuffer();
    if(c=='\b'){
        removeCharFromBuffer();
    }
    while(c==-1){
        cursor();
        _hlt();
         c=removeCharFromBuffer();
    }
    stopCursor();
    return c;
}

char removeCharFromBuffer(){
    if(buffSize<=0)
        return -1;
    int c= buffer[ridx]; 
    ridx=(ridx +1)%BUFF_LEN; //mas rapido que ir preguntando si el indice alcanzo el maximo, y de esta manera recorremos ciclicamente el buffer
    if(buffSize!=0)
    buffSize--;
    return c;

}


void printCoso(){
    for (int i = 0; i < buffSize; i++)
    {
        write(buffer[i]);
    }
}