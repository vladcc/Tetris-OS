# Tetris-OS
Tetris running on bare x86 hardware

Programming at the hardware level is so much fun.

It has it's own boot loader and runs in 32 bit protected mode.
The boot code is written for NASM, the system written in C and compiled with gcc.
The core of the system consists of drivers for the programmable interrupt controller, the programmable interval timer, the keyboard,
and the monitor. It does not use a file system, instead the BIOS loads the whole binary code chunk into memory on boot.

You can use both the .img and the .iso to boot from the floppy or the cd of a virtual machine, or a x86 emulator. 
You can write the .img on a flash drive and boot on real hardware. If you want to try run a Linux and do:

dd if=TetOS.img of=/dev/sdb

where /dev/sdb is your inserted falsh drive. If you are not sure which device it is, try fdisk -l.

IMPORTANT: this will re-write the first sectors of your flash drive, rendering it unusable (for other purposes). You may lose data. 
Back up the sectors first or you'll have to re-format the drive.

I haven't tried booting from an actual CD, but I did manage to boot on an old EeePC (remember those?) from a flash drive. It crashes
after a while, though.

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
