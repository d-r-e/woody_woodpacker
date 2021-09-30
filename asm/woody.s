
segment .text
    global _woody
	extern _start
_woody:
	pushfq
	push rax
	push rdi
	push rsi
	push rsp
	push rdx
	push rcx
	push r8
	push r9
	push r10
	mov edi, 1
	jmp woody
back:
	pop rsi
	mov rdx, 15
	mov rax, rdi
	syscall
	jmp finish
woody:
	call back
	.string db "Hello world!!!", 10, 00

finish:
	pop r10
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsp
	pop rsi
	pop rdi
	pop rax
	popfq
	jmp _start
	ret