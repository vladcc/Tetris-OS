/* implements low level input output functions */

// code
unsigned char port_byte_in(unsigned short port)
{	
	// port in dx
	// al in result when done
	unsigned char result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result;
}

void port_byte_out(unsigned short port, unsigned char data) 
{
	// data in al
	// port in dx
	__asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}
unsigned short port_word_in(unsigned short port) 
{
	// port in dx
	// al in result
	unsigned short result;
	__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result;
}

void port_word_out(unsigned short port, unsigned short data) 
{
	// data in al
	// port in dx
	__asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}
