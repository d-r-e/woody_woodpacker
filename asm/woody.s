global start

start:
    ; xor rax, rax ;; not needed since we are overwriting all these regs
    ; xor rdi, rdi ;; "
    ; xor rdx, rdx ;; "

  mov r13, 0xcacacaca ; new_entry
  mov r12, 0xcacacaca ; text_offset
  mov r11, 0xcacacaca ; text_size
;   mov r10, 8 ; key length
  jmp woody
write:
	mov rax, 1
	mov rdi, 1
	pop rsi
	mov rdx, 23
	syscall
	jmp mprotect
woody:
	call write
	db `\e[35m....WOODY....\e[0m\n`

mprotect: ;thanks usavoia
	lea rdi, [ rel start ]
	neg r13
	add rdi, r13 ; substract new entry to 
	add rdi, r11
	mov r10, rdi
	and rdi, -0x1000
	neg rdi
	add r10, rdi
	neg rdi
	add r12, r10

	mov rax, 0xa ; chiamata a mprotect per avere i permessi di scrittura su .text per decriptare
	mov rsi, r12 ; grandezza della sezione
	mov rdx, 0x07 ; PROT_READ | PROT_WRITE | PROT_EXEC
	syscall
	jmp end
key:
	db `\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca`, 0x00
end:
	xor rax, rax
	xor rdi, rdi
	xor rdx, rdx
	xor rsi, rsi
	jmp -0x00