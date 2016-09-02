/* our kernel */

// includes
#include "kernel.h"
#include "util.h"
#include "stdbool.h"
#include "../drivers/monitor_mode_txt.h"
#include "../drivers/interrupts.h"
#include "../drivers/pic.h"
#include "../drivers/pit.h"
#include "../drivers/kbd.h"
#include "../games/tetris.h"

// globals
static INPUT_HNDLR input_f = default_input;

// code
void k_main()
{
	/* the main kernel function */
	
	// initiate interrupt descriptor table and drivers
	idt_init(IDT);				// set id table
	pic_initialize();			// intialize the pic
	set_interval_size(1000);	// count every 1000 ticks
	pit_initialize(1000);		// start timer ticking every ms
	kbd_initialize();			// enable keyboard
	__asm__("sti"); 			// enable interrupts
	clear_screen();
	greeting();					// say welcome
	//check_kbd();
	tetris_main();				// give control to tetris
	
	// system loop
	while (true)
		halt();					// halts until interrupted
}

void kbd_dispatch(int kbd_scan_code)
{
	/* called by the kbd_irq, dispatches the keyboard
	 * input to the function pointed to by input_f */

	 input_f(kbd_scan_code);
}

void greeting(void)
{
	/* prints the welcome message */
	set_attribute_byte(GRAY_ON_BLACK);
	char msg[] = "Welcome to Tetris OS!\n";
	print_at(msg, MAX_COLS / 2 - strlen(msg) / 2, 1);
}

void set_input_function(INPUT_HNDLR proc_input)
{
	/* with this you can set a custom function
	 * dealing with keyboard input */
	input_f = proc_input;
}

void default_input(int code)
{
	/* default input function does nothing */
	return;
}
