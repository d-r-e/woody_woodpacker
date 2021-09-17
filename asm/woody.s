section .data
    wdy db "...WOODY...", 0xa ; 

section .text
    global _woody

_woody:
    mov rax, 1
    mov rdi, 1
    mov rsi, wdy
    mov rdx, 13
    syscall
    xor rax, rax;
    xor rdi, rdi;
    ret;
