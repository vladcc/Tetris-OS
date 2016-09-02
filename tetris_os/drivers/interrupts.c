/* installs idt and deals with interrupts */

// includes
#include "interrupts.h"
#include "pic.h"
#include "pit.h"
#include "../kernel/util.h"
#include "monitor_mode_txt.h"
#include "../kernel/low_level_io.h"

// globals
static idt_desc _idt[MAX_INTERRUPTS];
static idtr	_idtr;

// code
void idt_install()
{
	/* set the idtr register, installs the interrupt
	 * descriptor table */
	
	__asm__("lidt %0" ::"m"(_idtr));
}

int install_ir_handler(uint32_t i, uint8_t flags, uint16_t selector, IRQ_HNDLR irq)
{
	/* inserts an interrupt handler in the idt */
	
	// check for interrupt bounds and for valid handler pointer
	if (i > MAX_INTERRUPTS)
		return 0;
	if (!irq)
		return 0;
	
	// get function address
	uint32_t handler_address = (uint32_t)irq;
	
	// set structure
	_idt[i].base_low = (uint16_t)(handler_address & 0xffff);
	_idt[i].base_high = (uint16_t)((handler_address >> 16) & 0xffff);
	_idt[i].reserved = 0;
	_idt[i].flags = (uint8_t)flags;
	_idt[i].selector = selector;
	
	return 0;
}

int idt_init(uint16_t code_selector)
{
	/* fills the exceptions entries with the default handler */
	
	// get size of idt and base address
	_idtr.limit = sizeof(idt_desc) * MAX_INTERRUPTS - 1;
	_idtr.base = (uint32_t)&_idt[0];
	
	int i;
	// fill the first 32 entries (onyl the CPU exceptions)
	for (i = 0; i < INTERRUPTS_IVT; ++i)
		install_ir_handler(32, FLAGS, code_selector, default_handler);
	
	// install idt
	idt_install();
	
	return 0;
}

void default_handler(void)
{
	/* the default handler */
	
	// save registers
	__asm__("pusha");
	
	print("An exception has occured.\n");
	halt();
	end_of_interrupt();

	// restore registers
	__asm__("popa");
	__asm__("leave");	// restore stack
	__asm__("iret");	// interrupt return - this is important
}

void end_of_interrupt(void)
{
	/* send end of interrupt to the two PICs */
	port_byte_out(MASTER_PIC_CMD_PORT, END_OF_INTERRUPT);
	port_byte_out(SLAVE_PIC_CMD_PORT, END_OF_INTERRUPT);
}
