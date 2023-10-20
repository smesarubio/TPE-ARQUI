#include <syscallDispatcher.h>
#include <syscalls.h>
#include <stdint.h>
uint64_t syscall_selector(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint32_t r9){
    switch (rdi)
    {
    case SYS_WRITE_ID:
        sys_write(rsi, rdx, rcx, r8, r9);
        break;
    case SYS_READ_ID:
        sys_read(rsi, rdx, rcx, r8, r9);
        break;
    case SYS_WAIT_ID:
        sys_wait(rsi, rdx, rcx, r8, r9);
        break;
    case SYS_CLEAR_ID:
        sys_clear(rsi, rdx, rcx, r8, r9);
        break;
    case SYS_INFOREG_ID:
        return sys_inforeg(&rsi);
    default:
        break;
    }
}