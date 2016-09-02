// constants
#define COUNTER_0 				0x40
#define CTRL_WORD				0x43
#define SQR_WAVE_BIN_COUNTER	0x36
#define PIT_IRQ					0x20

#define CHN_0_DATA_PORT			0x40
#define CHN_2_DATA_PORT			0x42
#define MODE_CMD_REG			0x43 // write only

// typedefs
typedef void (*TI)(void);

// functions
void pit_initialize(int frequency);
void pit_irq(void);
void set_interval_size(int how_many_ticks);
int get_ticks(void);
void set_timer_irq(TI custom_irq);
void set_kbd_interval(int wait_ms);
