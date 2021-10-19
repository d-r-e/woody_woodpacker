global start

start:
    ; xor rax, rax
    ; xor rdi, rdi
    ; xor rdx, rdx

  mov r9, 0xcacacacacacacaca ; key
  mov r13, 0xcacacaca ; new_entry
  mov r12, 0xcacacaca ; text_offset
  mov r11, 0xcacacaca ; text_size
  mov r10, 8 ; key length
  jmp woody
print:
	mov rax, 1
	mov rdi, 1
	pop rsi
	mov rdx, 23
	syscall

	jmp end



woody:
	call print
	db `\e[94m....WOODY....\e[0m\n`
end:
	xor rax, rax
	xor rdi, rdi
	xor rdx, rdx
	xor rsi, rsi
	jmp -0x00