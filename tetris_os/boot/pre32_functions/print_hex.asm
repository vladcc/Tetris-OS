; prints a byte as a hex value
; used for debugging, not included in the final bootsector

[bits 16]		; force 16 bit code for real mode
print_hex:
	; ax - value to print

	; save registers
	push ax
	push bx

	mov bx, ax	; copy the requested value
	push bx		; save it	

	shr bx, 4		; get higher nibble
	mov ax, [HEX_TBL + bx]	; fetch the character from the table
	call print_char		; print it

	pop bx			; restore original value
	and bx, 0x0F		; get lower nibble
	mov ax, [HEX_TBL + bx]	; fetch character from the table
	call print_char		; print

	; restore registers and return
	pop bx
	pop ax
	ret

; hex table
HEX_TBL: db "0123456789ABCDEF"