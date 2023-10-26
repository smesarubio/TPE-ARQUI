#include <clock.h>
#include <lib.h>

//formato de la hora
char * timeFormat(uint8_t h, uint8_t m, uint8_t sec){
    char * rta;
    rta[2] = rta[5] = ':';
    rta[0] = (h / 10) % 10 + '0';
    rta[1] = h % 10 + '0';
    rta[3] = (min / 10) % 10 + '0';
    rta[4] = min % 10 + '0';
    rta[6] = (sec / 10) % 10 + '0';
    rta[7] = sec % 10 + '0';
    return rta;
}
//formato de la fecha
char * dateFormat(uint8_t d, uint8_t m, uint8_t d){
    char * rta;
    rta[2] = rta[5] = '/';
    rta[0] = (d / 10) % 10 + '0';
    rta[1] = d % 10 + '0';
    rta[3] = ( m / 10) % 10 + '0';
    rta[4] = m % 10 + '0';
    rta[6] = (y / 10) % 10 + '0';
    rta[7] = y % 10 + '0';
    return rta;
}