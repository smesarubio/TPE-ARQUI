#include <lib.h>
#include <naiveConsole.h>
#include <videoDriver.h>
#include <keyboard_driver.h>
#include <stdint.h>



static char ScanCodes[256]={0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
'\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 
'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', 0, 0 };


void keyboard_handler(int key){
    //int key = getKey();
    static int capsLockOn = 0;

    static int x0 = 0;
    static int y0 = 0;


    //square(FOREGROUND, x0, y0, 50);

    /* if(key == 0x1B){
        *flag = 1;
    } */

    if (ScanCodes[key] == 'w') //pink
    {
        //y0-=50;
        //(FOREGROUND, x0, y0, 50);
        //font();
    }

    /* 
    if (ScanCodes[key] == 'a') //pink
    {
        x0-=50;
        square(FOREGROUND, x0, y0, 50);
    }

    if (ScanCodes[key] == 's') //pink
    {
        y0+=50;
        square(FOREGROUND, x0, y0, 50);
    }
    
    if (ScanCodes[key] == 'd') //pink
    {
        x0+=50;
        square(FOREGROUND, x0, y0, 50);
    }


 */
    /* 
    if (ScanCodes[key] == 'r') //red
    {
        paint(0xeb050c);
    }
    if (ScanCodes[key] == 'g') //green
    {
        paint(0x90f56c);
    }
    if (ScanCodes[key] == 'b') //blue
    {
        paint(0x2a12ff);
    } */

    if (key == 0x3A) { // Caps Lock press
        capsLockOn = 1 - capsLockOn; // Toggle the Caps Lock status
    }

    if (key == 0xBA) { // Caps Lock release
        // Don't change the Caps Lock status here, as it's typically only changed on press.
    }

    if(key == 0x39){ // space
        ncPrint(" ");
        //paint(0xd61c44);
        return;
    }
    if(ScanCodes[key] == '\b'){
        ncBackspace();
        return;
    }
    if(ScanCodes[key] == '\t'){
        ncPrint("    ");
        return;
    }
    if(ScanCodes[key] == '\n'){
        ncNewline();
        //paint(0x90f56c);
        //scroll();
        return;
    }
    if( key >= 0 && key <= 256 && ScanCodes[key] != 0 ){
        if (capsLockOn) {
            ncPrintChar(ScanCodes[key] - ('a' - 'A'));
            //putChar(ScanCodes[key] - ('a' - 'A'),FOREGROUND,BACKGROUND,1);
        }
        else
        {
            ncPrintChar(ScanCodes[key]);
            //putChar(ScanCodes[key] - ('a' - 'A'),FOREGROUND,BACKGROUND,1);
        }
        return;
    }
    return;
}

/*
void keyboard_handler(){
    int key = getKey();

    static int capsLockOn = 0;

    if (key == 0x3A) {
        capsLockOn = 1 - capsLockOn;
    }



	if(key == 0x39){ // space
		ncPrint(" ");
		return;
	}
	if(ScanCodes[key] == '\b'){
		ncBackspace();
		return;
	}
	if(ScanCodes[key] == '\t'){
		ncPrint("    ");
		return;
	}
	if(ScanCodes[key] == '\n'){
		ncNewline();
		return;
	}
	if( key>=0 && key<=256 && ScanCodes[key] != 0 ){
        if (capsLockOn) {
            ncPrintChar(ScanCodes[key] - ('a' - 'A'));
        } else {
		    ncPrintChar(ScanCodes[key]);
        }
		return;
	}
	
    capsLockOn = 0;
}
*/