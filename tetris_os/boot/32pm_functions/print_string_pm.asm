; prints string in protected mode by writing directly to VGA memory

[bits 32]		; force 32 bit code for protected mode

; constants
%define VIDEO_MEMORY 0xb8000
%define GRAY_ON_BLACK 0x07

print_string_pm:
	; eax - string address

	; save registers
	push eax
	push ebx
	push ecx
	push edx

	mov ebx, VIDEO_MEMORY	; set ebx to point to VGA memory
	mov ch, GRAY_ON_BLACK	; set colors
	mov cl, [eax]	; move character in cl

.print_loop:	
	mov [ebx], cx	; move whole word to VGA memory
	add ebx, 2	; increment for next character
	inc eax		; increment for next character
	mov cl, [eax]	; check character
	cmp cl, 0	; if not null print again
	jnz .print_loop

	; restore and return
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret