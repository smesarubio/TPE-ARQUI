
GLOBAL _syscall

GLOBAL _opcodeExp


section .text

_syscall:
    push rbp
    mov rbp, rsp
	pushState

    int 80h

	popState
	mov rsp, rbp
    pop rbp

    ret
_opcodeExp:
	UD2
	ret