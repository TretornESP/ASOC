#include "instructions.h"
#include "buses.h"
#include "alu.h"
#include "uc.h"
#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)

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

	//printf("ADDR: %d DATA: %d MODE: %d\n", in[1], reg, RAM_WM);

	mp_cycle();
	return 0;
}

void* add(void* input){
	alu_add(input);
	return 0;
}

void* br(void* input){
	unsigned int * in = (unsigned int*) input;
	set_pc(in[1]-1);
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
	alu_sub(input);
	return 0;
}

void* ext(void* input){hlt(input);return 0;}

void* hlt(void* input){
	uc_hlt(1);
	uc_backstep();
}

void* ei(void* input){return 0;}
void* di(void* input){return 0;}

void* subr(void* input) {
	unsigned int * in = (unsigned int*) input;

	in[0] = (in[1] & 0x2) >> 1;
	in[1] = alu_get_reg(in[1] & 0x1);

	alu_sub(in);
	return 0;
}
