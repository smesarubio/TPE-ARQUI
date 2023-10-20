#ifndef SYSCALL_DISPATCHER_H
#define SYSCALL_DISPATCHER_H
#include <stdint.h>
uint64_t syscall_selector(uint64_t irq, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint32_t r9);
#endif