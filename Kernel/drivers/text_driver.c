#include <text_driver.h>
#include <stdint.h>

static char buff[MAX_BUFFER_LEN] = {0};
static int buff_size = 0;



char * getBuffer(){
    return buff;
}

void putInBuffer(char c){
    buff[buff_size] = c;
    buff_size ++;
}

void removeLastFromBuffer(){
    buff_size--;
}

void resetBuffer(){
    buff_size = 0;
}

int getBuffSize(){
    return buff_size;
}

char getLastFromBuffer(){
    if(buff_size <=0){
        return -1;
    }
    return buff[--buff_size];
}