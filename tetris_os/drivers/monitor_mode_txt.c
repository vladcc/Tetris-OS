/* the monitor driver for 80x25 text mode */

// includes
#include "monitor_mode_txt.h"
#include "../kernel/low_level_io.h"
#include "../kernel/util.h"

// globals
char attribute_byte = GRAY_ON_BLACK;

// code
void print_char(char character, int col, int row)
{
	/* prints a character at col, row or at the cursor position */
	unsigned char * vid_mem = (unsigned char *)VGA_ADDRESS;
	int offset;
	
	// if we want a specific position or not
	if (col >= 0 && row >= 0)	
		offset = get_scr_offset(col, row);
	else
		offset = get_cursor();
	
	// use only line feed as a new line character	
	if ('\n' == character)
	{
		// move offset to end of line so it'd be advanced to the next line
		offset = get_scr_offset(MAX_COLS - 1, offset / (2*MAX_COLS));
	}
	else
	{
		// or write character
		vid_mem[offset] = character;
		vid_mem[offset + 1] = attribute_byte;
	}
	
	// go to next character cell
	offset += 2;
	
	// make scrolling adjustments
	offset = handle_scrolling(offset);
	
	// update cursor position on the screen
	set_cursor(offset);
}

int get_scr_offset(int col, int row)
{
	/* calculates an offset in VGA memory from col and row */
	int offset = (row * MAX_COLS + col) * 2;
	
	return offset;
}

int get_cursor(void)
{
	/* gets the cursor position from the hardware */
	int offset = 0;
	
	port_byte_out(REG_SCR_CTRL, 0x0E);
	offset = port_byte_in(REG_SCR_DATA) << 8;
	port_byte_out(REG_SCR_CTRL, 0x0F);
	offset |= port_byte_in(REG_SCR_DATA);
	
	// cursor offset is reported as the # of characters
	offset *= 2;
	
	return offset;
}

void set_cursor(int offset)
{
	/* sets the cursor at offset */
	offset /= 2; // convert to char offset
	
	port_byte_out(REG_SCR_CTRL, 0x0E);
	port_byte_out(REG_SCR_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCR_CTRL, 0x0F);
	port_byte_out(REG_SCR_DATA, (unsigned char)offset);
}

void print_at(char * str , int col , int row) 
{
	/* prints str at position */
	int i;
	bool coordinates = false;
	
	// update the cursor if need be
	if ( col >= 0 && row >= 0)
	{
		set_cursor(get_scr_offset(col, row));
		coordinates = true;
	}
	
	// loop chars and print
	if (!coordinates)
		for (i = 0; str[i] != '\0'; ++i)
			print_char(str[i], col, row);
	else
		for (i = 0; str[i] != '\0'; ++i, ++col)
			print_char(str[i], col, row);

}

void clear_screen(void)
{
	/* clears the screen by writing spaces */
	 int row = 0;
	 int col = 0;
	
	for (; row < MAX_ROWS; ++row)
		for (; col < MAX_COLS; ++col)
			print_char(' ', col, row);

	// set cursor to top left
	set_cursor(get_scr_offset(0, 0));
}

int handle_scrolling(int cursor_offset)
{
	/* scrolls the screen */
	
	// return if no need for scrolling
	if (cursor_offset < MAX_ROWS * MAX_COLS * 2)
		return cursor_offset;
		
	/* move all rows up one row */
	int i;
	for (i = 1; i < MAX_ROWS; ++i)
	{
		mem_cpy((char *)(get_scr_offset(0, i) + VGA_ADDRESS),
				(char *)(get_scr_offset(0, i - 1) + VGA_ADDRESS),
				MAX_COLS * 2);
	}
	
	// blank the last line
	char * lst_ln = (char *)(get_scr_offset(0, MAX_ROWS - 1) + VGA_ADDRESS);
	for (i = 0; i < MAX_COLS; i += 2)
		lst_ln[i] = ' ';
		
	cursor_offset -= 2 * MAX_COLS;
	
	return cursor_offset;
}

char get_char_at(int row, int col)
{
	/* reads a character from row, col position */
	unsigned char * vid_mem = (unsigned char *)VGA_ADDRESS;
	int offset = get_scr_offset(row, col);
	
	return vid_mem[offset];
}

void set_attribute_byte(char attrib)
{
	/* sets the atribute byte - colors and stuff */
	attribute_byte = attrib;
}

char get_attribute_byte(void)
{
	/* gets the current attribute byte */
	return attribute_byte;
}

void hide_cursor(void)
{
	/* guess what this does */
	port_word_out(REG_SCR_CTRL, HIDE_CURSOR);
}
