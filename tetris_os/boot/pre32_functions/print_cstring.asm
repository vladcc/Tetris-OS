; prints a zero terminated string

[bits 16]		; force 16 bit code for real mode
print_cstring:
	; ax - string address

	; save registers
	push ax
	push bx
	
	mov bx, ax	; move address in bx
	mov ax, [bx]	; load character in ax
.loop:	
	call print_char	; print character
	inc bx		; address of next character
	mov ax, [bx]	; see what the character is
	cmp al, 0	; print again if it's not null
	jne .loop

	; restore and return
	pop bx
	pop ax
	ret