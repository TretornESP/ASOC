#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "iset.h"
#include "instructions.h"
#include "alu.h"

extern data * RAM;
extern data * iset;
extern data * extended_iset;

reg x, acc;

int main(int argc, char* argv[]) {
	
	load_iset();
	load_ram();

	int test_instruction = 0xF00;
	
	set_ram_from_int(0, test_instruction);

	dump_ram_at(0);

	find_instruction_from_data(&RAM[0]);

	return 0;
}

