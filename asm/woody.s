global start

start:
    ; xor rax, rax ;; not needed since we are overwriting all these regs
    ; xor rdi, rdi ;; "
    ; xor rdx, rdx ;; "

  mov r13, 0xcacacaca ; new_entry
  mov r12, 0xcacacaca ; text_offset
  mov r11, 0xcacacaca ; text_size
;   mov r10, 8 ; key length

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



    add rdi, r10 ; offset section text
    neg r10
    add r12, r10 ; ripristino size

    mov rdx, r12 ; size tot
    mov rsi, rdi ; section offset
    mov rax, -1
	jmp key
decryptor:
   	pop r9 ; key string
   	mov r10, 10 ; key len
   	xor ecx, ecx ; contatore key len
   	xor r11, r11
loop:
   	inc rax ; incremento contatore sezione .text
   	mov r8, [r9 + rcx]
   	xor byte [rsi + rax], r8b ; xor tra carattere sezione .text e carattere key
   	inc cl ; incremento contatore stringa key
   	cmp byte [r9 + rcx], 0 ; controllo se la stringa della key sia finita
   	cmove ecx, r11d ; se la stringa key è finita la riposiziono all'inizio
   	cmp rax, rdx ; controllo se sono arrivato alla fine della sezione .text
   	jb loop ; se non sono alla fine della sezione .text riparte il loop
	jmp woody
write:
	mov rax, 1
	mov rdi, 1
	pop rsi
	; mov rdx, 14
	mov rdx, 23
	syscall
	jmp end
key:
	call decryptor
	db `\xca\xca\xca\xca\xca\xca\xca\xca\xca\xca`, 0x0
woody:
	call write
	; db `....WOODY....\n`
	db `\e[35m....WOODY....\e[0m\n`
end:
	xor rax, rax
	xor rdi, rdi
	xor rdx, rdx
	xor rsi, rsi
	jmp 0xffffffff