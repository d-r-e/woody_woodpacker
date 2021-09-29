[BITS] 64

section .text
    global _start
    extern _woody
_start:
    call _woody;
    mov rax, 60;
    xor rdi, rdi;
    syscall