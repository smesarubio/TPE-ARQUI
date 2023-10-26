#ifndef CLOCK_H
#define CLOCK_H

//por default, ver pagina
#define SECONDS 0x00
#define MINUTES 0x02
#define HOURS 0x04
#define DAYS 0x07
#define MONTH 0x08
#define YEAR 0x09
#define TIME_ZONE -3

void timeFormat(uint8_t h, uint8_t m, uint8_t sec);
void dateFormat(uint8_t d, uint8_t m, uint8_t y);

#endif
