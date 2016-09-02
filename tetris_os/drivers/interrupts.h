// includes
#include <stdint.h>
#include <stddef.h>

// constants
#define IDT 			0x8
#define MAX_INTERRUPTS 	256
#define INTERRUPTS_IVT 	32
#define FLAGS 			0x8E

// structs
struct idt_descriptor {
	uint16_t	base_low;	// offset bits 0 to 15
	uint16_t	selector;	// a code seg selector in GDT or LDT
	uint8_t		reserved;	// unused, set to 0	
	uint8_t		flags;		// type and attributes
	uint16_t	base_high;	// offset bits 16 to 31
} __attribute__((packed));

struct idtr {
	uint16_t	limit;	// size of idt
	uint32_t	base;	// base address
} __attribute__((packed));

// typedefs
typedef struct idt_descriptor idt_desc;
typedef struct idtr idtr;
typedef void(*IRQ_HNDLR)(void);	// pointer to interrupt handler function

// functions
void default_handler(void);
void idt_install(void);
void generate_interrupt(void);
int install_ir_handler(uint32_t i, uint8_t flags, uint16_t selector, IRQ_HNDLR irq);
int idt_init(uint16_t code_selector);
void default_handler(void);
void end_of_interrupt(void);
