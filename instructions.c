#include "instructions.h"
#include "buses.h"
#include "alu.h"
#include "uc.h"

void* ld(void* input){
	unsigned int * in = (unsigned int*)input;
	alu_set_reg(in[0], in[1]);
	return 0;
}

void* st(void* input){
	unsigned int * in = (unsigned int*)input;
	int reg = alu_get_reg(in[0]);
	
	bus_a_set(data_from_int(in[1]));
	bus_d_set(data_from_int(reg));
	bus_c_set(data_from_int(RAM_WM));

	mp_cycle();
	return 0;
}

void* add(void* input){
	unsigned int * in = (unsigned int*) input;
	alu_set_reg(in[0], alu_get_reg(in[0])+in[1]);	
	return 0;
}

void* br(void* input){
	unsigned int * in = (unsigned int*) input;
	set_pc(in[1]);
}

void* bz(void* input){
	data * state = get_state();
	if (state->binary.d9) br(input);
}

void* ldh(void* input){	
	unsigned int * in = (unsigned int*) input;
	alu_set_reg(in[0], in[1]);
	return 0;
}

void* subh(void* input){
	unsigned int * in = (unsigned int*) input;
	alu_set_reg(in[0], alu_get_reg(in[0])-in[1]);
	return 0;
}

void* ext(void* input){hlt(input);return 0;}

void* hlt(void* input){
	data * state = get_state();
	state->binary.d11 = 1;
	
	while (1);
}

void* ei(void* input){return 0;}
void* di(void* input){return 0;}
