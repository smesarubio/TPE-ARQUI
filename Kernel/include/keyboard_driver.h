#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

extern int getKey();
void keyboard_handler();
char getChar();
char removeCharFromBuffer();
char getKeyChar();
#endif /* KEYBOARD_DRIVER_H */