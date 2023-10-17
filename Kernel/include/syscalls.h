#ifndef SYSCALLS_H
#define SYSCALLS_H
#include <stdint.h>
#include <colors.h>
#define SYS_WRITE_ID 4
#define SYS_READ_ID 3

uint64_t _syscall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
void sys_write(char * str, uint8_t len, t_color bgColor, t_color ftColor, int usrLen);


#endif