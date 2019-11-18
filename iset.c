#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "iset.h"
#include "instructions.h"

char * opcode_names[] = {
	"LD", "ST", "ADD", "BR", "BZ", "LDH", "SUBH", "EXT"
};

char * extended_opcode_names[] = {
	"HLT", "EI", "DI", "SUBR"
};

func_ptr opcode_funcs[] = {
	ld, st, add, br, bz, ldh, subh, ext
};

func_ptr extended_opcode_funcs[] = {
	hlt, ei, di, subr
};

void load_iset() {
	iset = malloc(sizeof(instr)*ISET_SIZE);
	for (int i = 0; i < ISET_SIZE; i++) {
		instr ins = {.func = opcode_funcs[i], .opc = i};
		strcpy(ins.nemo, opcode_names[i]);
		ins.is_extended = 0;
		iset[i] = ins;
		
	}

	extended_iset = malloc(sizeof(instr)*ISET_SIZE);
	for (int i = 0; i < EXTENDED_ISET_SIZE; i++) {
		instr ins = {.func = extended_opcode_funcs[i], .opc = i};
		strcpy(ins.nemo, extended_opcode_names[i]);
		ins.is_extended = 1;
		extended_iset[i] = ins;
	}
}

instr *find_instruction_from_data(data *d) {
	int index = (d->wrapper & 0xE00) >> 9;

	printf("NAME: %s\n", iset[index].nemo);
	printf("FUNC: %p\n", iset[index].func);
	printf("OPCD: %d\n", iset[index].opc);
	printf("IS EXTENDED: %d\n", iset[index].opc==0x7);
	
	if (iset[index].opc == 0x7) {
		index = (d->wrapper & 0x180) >> 7;

		printf("NAME: %s\n", extended_iset[index].nemo);
		printf("FUNC: %p\n", extended_iset[index].func);
		printf("OPCD: %d\n", extended_iset[index].opc);	
	}

	return &iset[d->wrapper & 0xE00];
}


