//includes
#include "../kernel/stdbool.h"

// address and dimensions
#define VGA_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// default color attribute
#define GRAY_ON_BLACK 0x07

// screen I/O ports
#define REG_SCR_CTRL 0x3d4
#define REG_SCR_DATA 0x3d5

#define HIDE_CURSOR 0x200A

// functions
void print_char(char character, int col, int row);
int get_scr_offset(int col, int row);
int get_cursor(void);
void set_cursor(int offset);
void print_at(char * str , int col , int row);
void clear_screen(void);
int handle_scrolling(int cursor_offset);
char get_char_at(int row, int col);
void set_attribute_byte(char attrib);
char get_attribute_byte(void);
void hide_cursor(void);
