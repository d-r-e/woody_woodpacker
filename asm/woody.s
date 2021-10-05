    global _start
_start:
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
	mov rdi, 1
	jmp woody
back:
	pop rsi
	mov rdx, 15
	mov rax, rdi
	syscall
	jmp finish
woody:
	call back
	.string db "....WOODY.....", 10, 00

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
	xor rax, rax
	mov r13, 0x42424242 
	jmp r13