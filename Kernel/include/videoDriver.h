#ifndef H_VIDEO_DRIVER
#define H_VIDEO_DRIVER
#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void paint(uint32_t color);
#endif