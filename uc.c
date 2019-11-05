#include <stdlib.h>

#include "uc.h"
#include "memory.h"
#include "iset.h"

int PC = 0;
int cycle = 0;

data * fetch() {
	bus_a_set(data_from_int(PC));
	bus_c_set(data_from_int(RAM_RM));

	mp_cycle();
	
	return bus_d_get();
}

uc_data * decode(data * d) {
	uc_data decomposed = malloc(sizeof(uc_data));

	instr = decode_opc(d->wrapper);

	decomposed -> func = instr.func;
	decomposed -> reg = decode_reg(d->wrapper);
	decomposed -> ed = decode_cd(d->wrapper, instr.opc);
}

instr decode_opc(int i) {
	int index = (i & 0xE00) >> 9;

	if (iset[index].opc == 0x7) {
		index = (d->wrapper & 0x180) >> 7;
		return extended_iset[index];
	} else {
		return iset[index];	
	}
}

unsigned int decode_reg(int i) {
	return (i & 0x100) >> 8;
}

OPCR JICD CDCD
0000 0000 0000
0     4   0

void decode_cd(int i, int opc) {
	if (opc == 0x5 || opc == 0x6) {
		
	}

	int j = (i & 0x080) >> 7;
	int i = (i & 0x040) >> 6;

	if (// ADDRESSING
}



void execute() {

}

void memory() {

}


void loop() {
	data * raw = fetch(); //Retrieve from ram
	uc_data * decoded = decode(raw); //Decode into opc, register, efective direction
	data * res = execute(decoded) //Execute from alu
	int result = memory(res); //Write to memory

	printf("CYCLE %d EXECUTED: %d RESULT: %d\n", cycle, pc, result);

	cycle++;
	PC++;
}
