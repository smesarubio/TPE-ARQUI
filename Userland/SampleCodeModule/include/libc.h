#ifndef LIBC_H
#define LIBC_H

#include <colors.h>
#include <stdint.h>

void setBGC(t_color colour);
void setFTC(t_color colour);
int scanf(char * str, ...);
void printf(char *str, ...);
void putChar(char c);
// int getChar(); // MODO ESPERA ACTIVA
char getChar(); // MODO HLT
int strlen(const char *s);
void setUserLength(char *user);
int strcmp(char string1[], char string2[]);
int strToInt(char *str, int* size);
char *intToStr(int value, char *buffer, int base);
void newLine();
char *reverse(char *buffer, int i, int j);
int abs(int num);
void swap(char *x, char *y);
char *strcpy(char *destination, const char *source);
void newLine();
int readText();
int strToHex(const char *str);
void sendUserData();
void doubleToStr(double n, char* res, int afterpoint);
int pow(int x, unsigned int y);
void strToDouble(char *numStr, double *result);
void setFirstChange(int number);

char *getInput();

void waitForEnter();

int getInputSize();

void wipeScreen();

void clearSc();

uint64_t getTime(int i);

void waitSec();

void backToTerm();

int getTicksInt();

void drawSquare(int size, int x, int y, int color);
int randInt(int min, int max);

#endif