section .text
  global _start
_start:
  ;; save cpu state
  ; xor rax, rax
  ; xor rdi, rdi
  ; xor rsi, rsi
  ; xor rdx, rdx
  jmp woody
print:
  mov rax, 1          ; syscall [1] -> sys_write
  mov rdi, 1          ; stdout
  pop rsi             ; msg address
  mov rdx, 23         ; msg size
  syscall
  jmp end
woody:
  call print
  db `\e[94m....WOODY....\e[0m\n`
key:
  mov r13, 0xcacacacacacacaca ; key
  mov r12, 0xcacacacacacacaca ; text_offset
  mov r11, 0xcacacacacacacaca ; text_size
end:
  ;; restore cpu state
  xor rdx, rdx
  xor rsi, rsi
  xor rdi, rdi
  xor rax, rax
  jmp  -0x00