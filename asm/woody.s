[BITS] 64
segment .text
    global _woody
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
    mov rax, 1      ; syscall write
    mov rdi, 1      ; fd 1
    mov rsi, .wdy    ; buffer woody
    mov rdx, 15     ; bytes 15
    syscall
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
    jmp 0x424242
    .wdy db "....WOODY.....", 0xa, 0; 
    ; xor rdi, rdi
    ; mov rax, 60
    ; syscall