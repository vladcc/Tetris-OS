; clears the screen by printing new lines

[bits 16]		; force 16 bit code for real mode
clear_screen:
	; save the registers we gonna use
	push ax
	push bx
	push dx

	mov bx, 50
.loop:			; print 50 new lines
	mov ax, 0xA
	call print_char
	dec bx
	jnz .loop

	; set the cursor top left
	mov ah, 2	; move cursor
	mov dl, 0	; column
	mov dh, 0	; row
	mov bh, 0	; page
	int 0x10

	; restore the original values and return
	pop dx
	pop bx
	pop ax
	ret