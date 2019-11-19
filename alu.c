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
	printf("X: %d, ACC: %d\n", SIGN(x), acc);
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

//Completame o rehazme mejor
void alu_add(void * input) {}
void alu_sub(void * input) {}
