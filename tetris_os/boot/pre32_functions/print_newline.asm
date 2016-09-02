; prints a line feed and a carriage return, resulting in a new line on the screen

[bits 16]		; force 16 bit code for real mode
print_newline:
	; save registers
	push ax

	mov ax, 0xA	; \n
	call print_char
	mov ax, 0xD	; \r
	call print_char

	; restore and return
	pop ax
	ret