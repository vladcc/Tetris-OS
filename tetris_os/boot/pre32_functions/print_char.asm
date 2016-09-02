; prints a character using bios int 10h

[bits 16]		; force 16 bit code for real mode
print_char:
	; ax - character to print

	; save registers
	push ax

	mov ah, 0x0e	; print case for bios int
	int 0x10	; interrupt

	; restore registers and return
	pop ax
	ret