/* the programmable interrupt controler driver */

// includes
#include <stdint.h>
#include <stddef.h>
#include "pic.h"
#include "../kernel/low_level_io.h"

// code
void pic_initialize(void)
{
	/* initializes the pic and mask all interrupts 
	 * except the timer and keyboard */
	uint8_t master_mask = 0xFC;	// only timer and kbd
	uint8_t	slave_mask = 0xFF;	// disable the slave
	
	// send control words and mask
	port_byte_out(MASTER_PIC_CMD_PORT, ICW1_INIT_ICW4);
	io_wait();
	port_byte_out(SLAVE_PIC_CMD_PORT, ICW1_INIT_ICW4);
	io_wait();
	
	port_byte_out(MASTER_PIC_DATA_PORT, ICW2_MASTER_OFFSET);
	io_wait();
	port_byte_out(SLAVE_PIC_DATA_PORT, ICW2_SLAVE_OFFSET);
	io_wait();
	
	port_byte_out(MASTER_PIC_DATA_PORT, ICW3_MASTER_SLAVE_IRQ);
	io_wait();
	port_byte_out(SLAVE_PIC_DATA_PORT, ICW3_SLAVE_MASTER_CASCADE);
	io_wait();
	
	port_byte_out(MASTER_PIC_DATA_PORT, ICW4_8086);
	io_wait();
	port_byte_out(SLAVE_PIC_DATA_PORT, ICW4_8086);
	io_wait();
	
	port_byte_out(MASTER_PIC_DATA_PORT, master_mask);
	port_byte_out(SLAVE_PIC_DATA_PORT, slave_mask);
}

uint8_t pic_read_irr(void)
{
	/* see which interrupt has been raised */
	port_byte_out(MASTER_PIC_CMD_PORT, PIC_READ_IRR);
	
	return port_byte_in(MASTER_PIC_CMD_PORT);
}

uint8_t pic_read_isr(void)
{
	/* see which interrupt is being currently serviced */
	port_byte_out(MASTER_PIC_CMD_PORT, PIC_READ_ISR);
	
	return port_byte_in(MASTER_PIC_CMD_PORT);
}

void io_wait(void)
{
	/* a "wait" function used only here 
	 * gives the controller time to respond */
	int i;
	for (i = 0; i < 32; ++i)
		__asm__("nop");
}
