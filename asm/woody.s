section .text
  global _start

_start:
  ;; save cpu state
  push rax
  push rdi
  push rsi
  push rdx

  ;; write msg to stdout
  mov rax,1                     ; [1] - sys_write
  mov rdi,1                     ; 0 = stdin / 1 = stdout / 2 = stderr
  lea rsi,[rel msg]             ; pointer(mem address) to msg (*char[])
  mov rdx, msg_end - msg        ; msg size
  syscall                       ; calls the function stored in rax

  ;; restore cpu state
  pop rdx
  pop rsi
  pop rdi
  pop rax

  mov rax, 0x4242424242424242            ; changed during patching
  jmp rax
align 8
  msg     db 0x1b,'[31m....WOODY.....',0x1b,'[0m',0x0a,0
  msg_end db 0x0