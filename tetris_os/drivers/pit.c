/* the programmable interval timer driver */

// includes
#include "pit.h"
#include "interrupts.h"
#include "monitor_mode_txt.h"
#include "../kernel/util.h"
#include "../kernel/low_level_io.h"

// globals
TI irq_f;				// pointer to the timer interrupt handler
int ticks = 0;			// increases every n ticks

/* this is used with ticks to measure
 * a desired interval; e.g. if you increase it
 * every 1000 ticks and one tick is 1 ms, it measures secods */
int interval = 0;		
int interval_size = 0; // sets the number of ticks in one interval

// code
void pit_initialize(int frequency)
{
	/* initialize the timer at frequency */
	
	uint16_t freq = 1193182 / frequency;
	
	// install handler
	install_ir_handler(PIT_IRQ, FLAGS, IDT, (IRQ_HNDLR)pit_irq);
	
	// talk to pit
	port_byte_out(CTRL_WORD, SQR_WAVE_BIN_COUNTER);
	port_byte_out(COUNTER_0, (freq & 0xFF));
	port_byte_out(COUNTER_0, ((freq >> 8) & 0xFF));
}

void pit_irq(void)
{
	/* default pit handler */
	
	// save registers
	__asm__("pusha");
	
	// count ticks
	++ticks;
	
	// check interval
	if (interval_size == ticks)
	{
		++interval;
		ticks = 0;
	}

	end_of_interrupt();	// let pic know we are done
	__asm__("popa");	// restore registers
	__asm__("leave");	// restore stack
	__asm__("iret");	// interrupt return - important
}

void set_interval_size(int how_many_ticks)
{
	/* sets the interval variable 
	 * also resets the interval number */
	
	interval_size = how_many_ticks;
	interval = 0;
	ticks = 0;
}

int get_ticks(void)
{
	/* return current number of ticks */
	return ticks;
}

void set_timer_irq(TI custom_irq)
{
	/* set a custom timer handler */
	irq_f = custom_irq;
}
