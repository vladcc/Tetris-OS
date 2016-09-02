// constants
#define KBD_IRQ			0x21 // kbr irq address in IDT (33 dec)

// ports and codes
#define KBD_ENC_INPUT	0x60
#define KBD_ENC_CMD		0x60
#define KBD_CTRL_STAT	0x64
#define KBD_CTRL_CMD 	0x64

#define KBD_CTRL_WRITE_OUT_PORT 0xD1

#define KBD_OUTPUT_FULL	0x01
#define KBD_INPUT_FULL	0x02

/* keys */
#define LEFT_DOWN	0x4B
#define RIGHT_DOWN	0x4D
#define UP_DOWN		0x48
#define DOWN_DOWN	0x50
#define SPACE_DOWN	0x39
#define ESC_DOWN	0x01
#define P_DOWN		0x19
#define P_UP		0x99
#define S_DOWN		0x1F
#define R_DOWN		0x13
#define Y_DOWN		0x15
#define Y_UP		0x95
#define N_DOWN		0x31
#define N_UP		0xB1

// functions
void kbd_initialize(void);
void kbd_irq(void);
