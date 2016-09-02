; loads the kernel from the drive
; note: for some reason LBA loading works automatically even on real hardware
; and CHS addressing fails 
; at least when using a floppy image, or iso boot with floppy emulation

[bits 16]			; force 16 bit code for real mode
load_kernel:
	; save all 16 bit general purpose registers
	pusha

	mov bx, KERNEL_OFFSET	; offset to load the sectors at
	mov al, 50		; number of sectors
	mov dl, [BOOT_DRV]	; id of the drive
	mov ch, 0		; cylinder (0 based)
	mov cl, 2		; sector (1 based), skip the MBR and start from sector 2
	mov dh, 0		; head one (0 based)
	call load_sectors
	
	; restore registers and return
	popa
	ret
