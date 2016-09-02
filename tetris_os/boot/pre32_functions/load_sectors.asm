; does the actual loading from the drive

[bits 16]		; force 16 bit code for real mode
load_sectors:
	; uses BIOS int 13h to read from disk
	; al - number of sectors
	; bx - load address base
	; dh - head (0 based)
	; dl - drive
	; ch - cylinder (0 based)
	; cl - sector to begin reading from (1 based)
	
	; save registers
	push ax
	push bx
	push cx
	push dx

	push ax		; push requested number of sectors

.reset:
	mov ah, 0	; reset disk
	int 0x13
	jc .reset	; reset again if error

	mov ah, 0x02	; BIOS read
	int 0x13

	jc read_error	; carry flag is set on error

	pop cx		; pop requested number of sectors
	cmp al, cl	; al - number of read sectors returned
	jne read_error

	; restore registers and return
	pop dx
	pop cx
	pop bx
	pop ax
	ret

; on read error come here
read_error:
	mov ax, DISK_ERROR	; print message
	call print_cstring
	cli			; halt and catch fire
	hlt

; string message
DISK_ERROR: db "Disk read error!", 0
