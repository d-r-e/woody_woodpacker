[BITS] 64
segment .text
    global _start
_start:
    push rax
    push rdi
    push rsi
    push rdx        ;save registers
    mov rax, 1      ; syscall write
    mov rdi, 1      ; fd 1
    mov rsi, .wdy    ; buffer woody
    mov rdx, 15     ; bytes 14
    syscall
    pop rdx
    pop rsi
    pop rdi
    pop rax         ; restore regs
    jmp 0x4003e0
    .wdy db "....WOODY.....", 0xa, 0; 
    ; xor rdi, rdi
    ; mov rax, 60
    ; syscall