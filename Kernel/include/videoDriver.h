#ifndef H_VIDEO_DRIVER
#define H_VIDEO_DRIVER
#include <stdint.h>



void printCharAt(char c, int x0, int y0);
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void paint(uint32_t color);
void square(uint32_t color, int x, int y, int size);
void write(char c);
void printNewLine();
void printTab();
void load_video();
void printBackspace();
void font();
void hola();
#endif