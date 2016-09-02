/* the keyboard driver */

// includes
#include "kbd.h"
#include "interrupts.h"
#include "../kernel/kernel.h"
#include "../kernel/low_level_io.h"

// globals
int kbd_scan_code = 0;

// code
void kbd_initialize(void)
{
	/* installs the irq handler at address 0x21 (33 dec) */
	
	install_ir_handler(KBD_IRQ, FLAGS, IDT, (IRQ_HNDLR)kbd_irq);
}

void kbd_irq(void)
{
	/* handles IRQ 1 coming from the keyboard */
	
	__asm__("pusha");	// save registers
	
	if (port_byte_in(KBD_CTRL_STAT) & KBD_OUTPUT_FULL)
	{
		kbd_scan_code = port_byte_in(KBD_ENC_INPUT);
		kbd_dispatch(kbd_scan_code);
	}

	end_of_interrupt();	// let PIC know we are done
	__asm__("popa");	// restore registers
	__asm__("leave");	// restore stack
	__asm__("iret");	// interrupt return - important
}
