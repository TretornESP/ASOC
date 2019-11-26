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
	0xA00, //   0   LDH x 0           1010 0000 0000 0xA00
	0x1CD, //   1   LD acc post(0xD)  0001 1100 1100 0x1CD
	0x34C, //   2   ST acc indi(0xC)  0011 0100 1011 0x34C
	0x40B, //   3   ADD x dir(0xB)    0100 0000 1010 0x40B
	0x10A, //   4	LD acc 0x00A      0001 0000 1001 0x10A
	0xD01, //   5	subh acc, 1       1101 0000 0001 0xD01
	0x30A, //   6   st acc 0x00A      0011 0000 1010 0x30A
	0x809, //   7	bz 0x009          1000 0000 1001 0x809
	0x601, //   8   BR 1              0110 0000 0001 0x601
	0xE00, //   9   HLT               1110 0000 0000 0xE00
        0x004, //   A   size of string 4
        0x001, //   B   increment of x in 1 (addh would be awesome)
        0xFFC, //   C   io vectors
        0xF01, //   D   asoc string  
       [0x00E ... 0xF00] = 0x0,
	0x041, //   F01 A
	0x073, //   F02 s
	0x06F, //   F03 o
	0x063, //   F04 c
       [0xF05 ... 0xFFF] = 0x0, // FF5 to FFF
};

void load_test_program() {
	size_t size = sizeof(example_program)/sizeof(example_program[0]);
	for (int i = 0; i < size; i++)
		set_ram_from_int(i, example_program[i]);

	for (int i = size; i < RAM_SIZE; i++)
		set_ram_from_int(i, 0x0);
}

int main(int argc, char* argv[]) {
	
	load_uc();
	load_iset();
	load_ram();
	load_buses();

	enable_trap(0);
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

	loop();
}

