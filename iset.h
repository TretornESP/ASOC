#ifndef _ISET_H
#define _ISET_H

#define ISET_SIZE 8
#define EXTENDED_ISET_SIZE 4

#include "memory.h"

typedef int opcode;
typedef void *(*func_ptr)(void*);

typedef struct _instr {
	char nemo[8];
	func_ptr func;
	opcode opc;
	int is_extended;
} instr;

void load_iset();
instr *find_instruction_from_data(data*);

instr *iset;
instr *extended_iset;
#endif
