; links with kernel.o and serves to call the main kernel function

[bits 32]		; force 32 bit code for protected mode
[extern k_main]		; tell nasm that k_main() is not here
	
	call k_main	; call kernel main
	hlt		; halt on return	