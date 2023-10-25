#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

extern int getKey();
void keyboard_handler(uint64_t * rsp);
char getChar();
char removeCharFromBuffer();
char getKeyChar();
char getCharCode();
char getChar();
int getOnAction(int key);

#endif /* KEYBOARD_DRIVER_H */