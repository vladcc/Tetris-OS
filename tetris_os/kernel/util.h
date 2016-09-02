// constants
#define RAND_MAX 32767

// functions
void mem_cpy(char * src, char * dest, int num_of_bytes);
int strlen(const char * str);
void base_convert(int num, int base);
void print_number(int num, int base);
void print_n(int num);
void print(char * str);
void print_c(char ch);
int rand(void);
void srand(unsigned int seed);
void sleep(unsigned int ms);
void halt(void);
