; boot sector for Tetris OS

[bits 16]		; force 16 bit code for real mode
[org 0x7c00]		; set base address

start:
	cli		; no interrupts
	xor ax, ax	; zero out
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, STACK	; set stack address
	mov sp, bp
	jmp 0:main	; far jump for cs
	
main:
	sti			; set interrupts

	mov [BOOT_DRV], dl	; remember the boot device

	call clear_screen	; clear the screen

	mov ax, RM_MSG		; print real mode message
	call print_cstring

	call load_kernel	; actually load the system

	call pm_switch		; switch to protected mode

	hlt			; halt - shouldn't execute

; constants
KERNEL_OFFSET equ 0x1000
STACK equ 0x9000

; variables
BOOT_DRV db 0

; includes
%include "./pre32_functions/print_char.asm"
%include "./pre32_functions/print_cstring.asm"
%include "./pre32_functions/clear_screen.asm"
%include "./pre32_functions/load_sectors.asm"
%include "./pre32_functions/pm_switch.asm"
%include "./pre32_functions/load_kernel.asm"
%include "./gdt/gdt.asm"
%include "./32pm_functions/print_string_pm.asm"

; real mode part
[bits 32] ; pm_switch lands here
BEGIN_PM:
	mov eax, PM_LANDED_MSG	; print success message
	call print_string_pm
	call KERNEL_OFFSET	; call into our kernel

	hlt			; halt - shouldn't execute

; strings
RM_MSG: db "Real mode entered.", 0
PM_LANDED_MSG: db "Protected mode entered successfully!", 0

; boot sector padding
times 510-($-$$) db 0	; padding
dw 0xaa55		; magic number
