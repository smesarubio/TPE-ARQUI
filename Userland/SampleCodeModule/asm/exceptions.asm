section .text
GLOBAL ex_zerodiv
ex_zerodiv:
	mov rax, 0
	mov rbx, 1
	div rbx
	ret
