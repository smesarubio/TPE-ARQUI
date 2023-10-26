
GLOBAL _syscall

GLOBAL _opcodeExp


section .text

%macro pushCalleeState 0
	push rbx
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popCalleeState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
%endmacro


_syscall:
    push rbp
    mov rbp, rsp
	mov rax,3
	mov r14,4
	mov r12,5
	mov rcx,6
	mov r15,15
	pushCalleeState

    int 80h

	popCalleeState
	mov rsp, rbp
    pop rbp

    ret
_opcodeExp:
	UD2
	ret

