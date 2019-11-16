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


unsigned int example_program[] = {
	        //OPCR JICD CDCD NEMOTECNICO
	0xA23,  //1010 0010 0011 ldh x, -3
	0xB06,  //1011 0000 0110 ldh acc, 6
	0xD04,  //1101 0000 0100 subh acc, 4
	0x3C6,  //0011 1100 0110 st acc, post-index(x):0x006
	0xE00,  //1110 0000 0000 hlt
	0x000,  //0000 0000 0000 0x0
	0x008,  //0000 0000 1000 0x8
};

void load_test_program() {
	for (int i = 0; i < 7; i++)
		set_ram_from_int(i, example_program[i]);

	for (int i = 7; i < RAM_SIZE; i++)
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

	load_test_program();

	printf("PRESS ENTER TO RUN PROGRAM\n");
	getchar();
	loop();	

	return 0;
}

