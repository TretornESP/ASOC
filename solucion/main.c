#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "buses.h"
#include "memory.h"
#include "iset.h"
#include "instructions.h"
#include "alu.h"
#include "uc.h"
#include "exception.h"
#include "loader.h"


unsigned int example_program[] = {
      //INSTRUCTION POS ASSEMBLY    BINARY         HEX
	0xA1E, //   0   LDH x 30    1010 0001 1110 0xA1E
	0xB1E, //   1   LDH acc 30  1011 0001 1110 0xB1E
	0xF82, //   2 	subr acc, x 1111 1000 0010 0xF82
	0x806, //   3 	bz 6        1000 0000 0110 0x806
	0xB00, //   4 	LDH acc 0   1011 0000 0000 0xB00
	0xE00, //   5 	hlt         1110 0000 0000 0xE00
	0xB01, //   6 	LDH acc 1   1011 0000 0001 0xB01
	0xE00, //   7   hlt         1110 0000 0000 0xE00
};

#define EXAMPLE_SIZE 8 //Tamaño del programa de ejemplo

void load_test_program() {
	for (int i = 0; i < EXAMPLE_SIZE; i++)
		set_ram_from_int(i, example_program[i]);

	for (int i = EXAMPLE_SIZE; i < RAM_SIZE; i++)
		set_ram_from_int(i, 0x0);
}

int main(int argc, char* argv[]) {
	
	load_uc();
	load_iset();
	load_ram();
	load_buses();

	enable_trap(1);
	enable_debug(1);
	set_catchfire(1);

	if (argc == 2) {
		if (load_ram_from_file(argv[1])) {
			printf("INVALID PROGRAM, ABORTING\n");
			return 1;
		}
	} else {
		printf("NO PROGRAM SPECIFIED, USING TEST PROGRAM\n");
		load_test_program();	
	}

	printf("PRESS ENTER TO RUN PROGRAM\n");
	getchar();
	loop();	

	return 0;
}

