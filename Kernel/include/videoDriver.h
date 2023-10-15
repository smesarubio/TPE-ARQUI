#ifndef H_VIDEO_DRIVER
#define H_VIDEO_DRIVER
#include <stdint.h>

typedef enum
{
    BACKGROUND = 0x282c34,
    ERROR = 0xe06c75,
    OKAY = 0x98c379,
    WARNING = 0xe5c07b,
    HELP = 0x61afef,
    COMP1 = 0xc678dd,
    COMP2 = 0x56b6c3,
    FOREGROUND = 0xdcdfe4,
}colorscheme;

void putChar(char c, colorscheme fontColor, colorscheme bgColor, int next);
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void paint(uint32_t color);
void square(uint32_t color, int x, int y, int size);
void load_video();
void font();
#endif