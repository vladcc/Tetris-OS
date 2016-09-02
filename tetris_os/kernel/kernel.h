// typedefs
typedef void(*INPUT_HNDLR)(int code); /* pointer to keyboard input handler */

// functions
void greeting(void);
void kbd_dispatch(int kbd_scan_code);
void set_input_function(INPUT_HNDLR proc_input);
void default_input(int code);
