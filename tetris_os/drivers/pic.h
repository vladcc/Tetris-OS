// constants
#define MASTER_PIC_CMD_PORT		0x20
#define MASTER_PIC_DATA_PORT	0x21
#define SLAVE_PIC_CMD_PORT		0xA0
#define SLAVE_PIC_DATA_PORT		0xA1

#define END_OF_INTERRUPT		0x20
#define PIC_READ_IRR			0x0A
#define PIC_READ_ISR			0x0B

/* initialize + wait for ICW 4 */
#define ICW1_INIT_ICW4		0x11

#define ICW2_MASTER_OFFSET	0x20
#define ICW2_SLAVE_OFFSET	0x28

#define ICW3_MASTER_SLAVE_IRQ		0x4
#define ICW3_SLAVE_MASTER_CASCADE	0x2

#define ICW4_8086	0x01

// functions
void pic_initialize(void);
uint8_t pic_read_irr(void);
uint8_t pic_read_isr(void);
void io_wait(void);
