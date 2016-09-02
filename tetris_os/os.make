# generate list of asm sources
ASM_SOURCES = $(wildcard boot/pre32_functions/*.asm boot/gdt/*.asm boot/32pm_functions/*.asm)

# generate list of c sources
C_SOURCES = $(wildcard kernel/*.c drivers/*.c games/*.c)

# generate list of headers
HEADERS = $(wildcard kernel/*.h drivers/*.h games/*.h)

# convert .c to .o
OBJ = ${C_SOURCES:.c=.o}

# $^ - all dependencies
# $< - the first dependency
# $@ - the target file

#run: os.img
#	./run.sh

# making the disk image
images/os.img: boot/bootsec.bin kernel/kernel.bin images/floppy/floppy.img	
	cat $^ > images/os.img
	dd if=images/os.img of=TetOS.img bs=512 count=2880

kernel/kernel.bin: boot/k_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ --oformat binary

# all .c files to object files
%.o : %.c ${HEADERS}
	gcc -ffreestanding -c $< -o $@

boot/k_entry.o: boot/k_entry.asm
	nasm $< -f elf -o $@

# make the boot sector
boot/bootsec.bin: boot/bootsec.asm $(ASM_SOURCES)
	nasm $< -f bin -I 'boot/' -o $@