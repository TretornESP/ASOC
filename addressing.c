#include "addressing.h"
#include "buses.h"
#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)

//Completame
int direct(int cd, int r) {}
int indexed(int cd, int r) {}
int indirect(int cd, int r) {}
int post_indexed(int cd, int r) {}

typedef int (*func_ptr)(int, int); 

func_ptr address_vectors[] = {direct, indirect, indexed, post_indexed};

char *addressing_names[] = {"direct", "indirect", "indexed", "post-indexed"};

char * get_addressing_names(int index) {
	return addressing_names[index];
}

unsigned int addressing(unsigned int cd, unsigned int reg, int option) { 
	if (option == DIRECT || option == INDIRECT) reg = 0;
	return address_vectors[option](cd, reg);
}

