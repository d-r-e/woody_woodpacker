section .text
  global _start
_start:
  ;; save cpu state
  push rax
  push rdi
  push rsi
  push rdx

  mov rax, 1                     ; syscall [1] -> sys_write
  mov rdi, 1                     ; stdout
  lea rsi, [rel msg]             ; msg address
  mov rdx, msg_end - msg -1       ; msg size
  syscall
  
align 8
  msg     db 0x1b,'[94m....WOODY.....',0x1b,'[0m',0x0a,0
  msg_end db 0x0

  ;; restore cpu state
  pop rdx
  pop rsi
  pop rdi
  pop rax

  jmp -0x0000