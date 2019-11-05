#ifndef _ISET_H
#define _ISET_H

#define ISET_SIZE 8
#define EXTENDED_ISET_SIZE 3

#include "memory.h"

typedef int opcode;
typedef int addressing;
typedef void *(*func_ptr)(void*);

typedef struct _instr {
	char nemo[8];
	func_ptr func;
	opcode opc;
} instr;

void load_iset();
instr *find_instruction_from_data(data*);
#endif
