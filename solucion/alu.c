#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "iset.h"
#include "instructions.h"
#include "alu.h"
#include "uc.h"
#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)
#define MAX_INT 32

reg x = 0x0;
reg acc = 0x0;
char *register_names[] = {"x", "acc"};

void dump_registers() {
	printf("X: %x, ACC: %x\n", x, acc);
}

char * get_register_names(int index) {
	return register_names[index];
}

reg alu_get_reg(int reg) {
	if (reg) {
		return alu_get_acc();		
	} else {
		return alu_get_x();	
	}
}

void alu_set_reg(int regno, reg val) {
	if (regno) {
		alu_set_acc(val);		
	} else {
		alu_set_x(val);	
	}	
}

reg alu_get_acc() {
	return acc;
}

void alu_set_acc(reg val) {
	acc = val;
}

reg alu_get_x() {
	return x;
}

void alu_set_x(reg val) {
	x = val;
}

void alu_add(void * input) {
	unsigned int * in = (unsigned int*) input;
	int result = alu_get_reg(in[0])+in[1];

	uc_overflow(result > MAX_INT+1 || result < -MAX_INT-1);
	uc_carry(result == MAX_INT+1 || result == -MAX_INT-1);
	
	alu_set_reg(in[0], result%MAX_INT);
	uc_zero (result % MAX_INT == 0);
	return;	
}

void alu_sub(void * input) {
	unsigned int * in = (unsigned int*) input;
	int result = alu_get_reg(in[0])-in[1];

	uc_overflow(result > MAX_INT+1 || result < -MAX_INT-1);
	uc_carry(result == MAX_INT+1 || result == -MAX_INT-1);
	
	alu_set_reg(in[0], result%MAX_INT);
	uc_zero (result % MAX_INT == 0);	
	return;	
}
