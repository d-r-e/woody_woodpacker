section .text
  global _start
_start:
  ;; save cpu state
  xor rax, rax
  xor rdi, rdi
  xor rsi, rsi
  xor rdx, rdx
  jmp woody
  ;; write
print:
  xor rax, rax                ; xor + inc -> set to 1
  inc rax                     ; syscall [1] -> sys_write
  xor rdi, rdi
  inc rdi                     ; stdout
  pop rsi             ; msg address
  mov rdx, 24         ; msg size
  syscall
  jmp end
woody:
  call print
  msg     db `\e[94m....WOODY.....\e[0m\n`
  ;; restore cpu state
end:
  xor rdx, rdx
  xor rsi, rsi
  xor rdi, rdi
  xor rax, rax

  jmp  -0x00 