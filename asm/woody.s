    global _woody
_woody:
	pushfq
	push rax
	push rdi
	push rsi
	push rsp
	push rdx
	push rcx
	jmp woody
back:
	pop rsi
	mov rdi, 1
	mov rdx, 15
	mov rax, rdi
	syscall
	jmp finish
woody:
	call back
	.string db "....WOODY.....", 10, 00
finish:
	pop rcx
	pop rdx
	pop rsp
	pop rsi
	pop rdi
	pop rax
	popfq
	mov r13, 0x4242424242424242
	lea r12, [rel _woody]
	sub r12, r13
	jmp r12
	