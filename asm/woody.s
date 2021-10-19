global start

start:
	mov r13, 0xcacacaca ; new_entry (temporary values will be overwritten)
	mov r12, 0xcacacaca ; text_offset
	mov r11, 0xcacacaca ; text_size

	lea rdi, [ rel start ]
	neg r13
	add rdi, r13
	add rdi, r11
	mov r10, rdi
	and rdi, -0x1000
	neg rdi
	add r10, rdi
	neg rdi
	add r12, r10
	; all this above is to get the text section actual mem addresss
	mov rax, 10 ; mprotect() syscall
	mov rsi, r12 ; address size
	mov rdx, 7 ; PROT_READ | PROT_WRITE | PROT_EXEC
	syscall
	add rdi, r10 ; offset section text
    neg r10
    add r12, r10 
    mov rdx, r12
    mov rsi, rdi
    mov rax, -1
	jmp key
decryptor:
   	pop r9 ; get key
   	mov r10, 10 ; key length
   	xor rcx, rcx ; i = 0
   	xor r11, r11
loop:
   	inc rax
   	mov r8, [r9 + rcx]
   	xor byte [rsi + rax], r8b ; decryption
   	inc rcx
   	cmp byte [r9 + rcx], 0 ; while key[i]
   	cmove rcx, r11 ; key back to stsart
   	cmp rax, rdx 
   	jb loop 
	jmp woody
write:  ; (rax=0x01)(rdi, rsi, rdx) = write(fd, buff, len)
	mov rax, 1
	mov rdi, 1
	pop rsi
	mov rdx, 23
	syscall
	jmp end
key:
	call decryptor
	db `\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca`, 0x0
woody:
	call write
	db `\e[35m....WOODY....\e[0m\n`
end:
	xor rax, rax
	xor rdi, rdi
	xor rdx, rdx
	xor rsi, rsi
	jmp 0xffffffff