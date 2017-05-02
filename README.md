# Tetris-OS
Tetris running on bare x86 hardware

Hello and welcome to the future! (not really)

Tired of flashy windows? Try Tetris OS!

Review:
This is my attempt at OS programming. 
It has it's own bootloader and runs in 32 bit protected mode using 80x25 text mode for interface.
The boot code is written for NASM, the system written in C and compiled with gcc.
The core of the system consists of drivers for the programmable interrupt controler, the programmable interval timer, the keyboard,
and the monitor. It does not use a file system, instead the BIOS loads the whole binary code chunk into memory on boot.

Now, if you for any reason have thought that I have implemented a tetris game on top of it - you are totally right.
You can boot and play. And if by any chance you are wondering what this .img file is, it's a floppy image. I remember when them floppies 
were used. People came from miles away to exchange them and hide from the dinosaurs.

Anyway, you can use both the .img and the .iso to boot from the floppy or the cd of a virtual machine or a x86 emulator. 
You can even write the .img on a flash drive and boot on real hardware. If you want to try run a Linux and do:

dd if=TetOS.img of=/dev/sdb

where /dev/sdb is your insterted falsh drive. If you are not sure which device it is, try fdisk -l.

IMPORTANT: this will re-write the first sectors of your flash drive, rendering it unusable (for other purposes). You will lose data. 
You can either back up the sectors first or just re-format the drive later.

I haven't tried booting from an actual CD, so if you do please let me know how it went.

Building:
If you want to build the project yourself you will need a Linux, gcc, NASM, and QEMU for running it on the spot.
Download the source, go into the tetris_os directory and do:

make -f os.make

This will get you a TetOS.img file. To make an iso from that do:

make -f iso.make

To run it do:

qemu-system-x86_64 -fda TetOS.img

or use the run.sh script (which does the same thing).
To clean everything and leave only the source code do:

make -f clean.make

And in case you are wondering what's that floppy.img file in images/floppy, it's just a floppy sized file full of 0s. It's used
as a template for the actual system image.

Known issues:
Sometimes crashes :)

Doing the project was a very educational and fun experience. I have written down all the stuff I was rambling about inside
my head, so the code is thoroughly commented. 
If you are interested in this sort of thing (you magnificent person, you!), feel welcome to drop a line and chit-chat.
