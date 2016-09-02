/* prints the scan codes for every pressed key on the kbd
 * used to see which key is what scan code */

#include <stdint.h>
#include "../kernel/stdbool.h"
#include "../kernel/kernel.h"
#include "../kernel/util.h"
#include "../drivers/pic.h"
#include "../drivers/pit.h"
#include "../drivers/monitor_mode_txt.h"
#include "../drivers/kbd.h"

int key_pressed;

void getch1(int scan_code);
void check_kbd(void);


void check_kbd(void)
{
	/* set getch1() as e kbd handler */
	set_input_function(getch1);
}

void getch1(int scan_code)
{
	/* get scan codes and print them */
	key_pressed = scan_code;	
	print_number(scan_code, 16);
	print_c('\n');
}
