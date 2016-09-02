; switches to protected mode
; note: we do not return from this function

; constants
%define PM_STACK 0x90000

[bits 16]			; force 16 bit code for real mode

pm_switch:
	call clear_screen	; clear the screen

	cli			; clear interrupts
	lgdt [gdt_descriptor]	; load the gdt descriptor

	mov eax, cr0		; set the 1st bit of the control register to 1
	or eax, 0x1
	mov cr0, eax

	jmp CODE_SEG:init_pm	; make a far jump the flush CPU cache

[bits 32]			; force 32 bit code for protected mode

init_pm:
	mov ax, DATA_SEG	; point to PM segments
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, PM_STACK	; initialize pm stack
	mov esp, ebp

	call BEGIN_PM		; start using protected mode, see bootsec.asm