section .data
    msg db "...WOODY...", 0xa ; 

section .text
    global _start

_woody:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 13
    syscall
    xor rax, rax;
    xor rdi, rdi;
    ret;

_start:
    call _woody;
    mov rax, 60 ;exit
    xor rdi, rdi
    syscall