#include <stdlib.h>
#include <stdio.h>

#include "iset.h"
#include "alu.h"
#include "uc.h"
#include "memory.h"
#include "iset.h"
#include "addressing.h"
#include "buses.h"
#include "historic.h"
#include "ces.h"

#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)
#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

int PC = 0;
int cycle = 0;

data * state;

data * get_state() {
	return state;
}

void set_state(data * s) {
	state = s;	
}

void set_pc(int pc) {
	PC = pc;
}

void dump_status() {
	int idx = 0;
	printf("S: XXXXXXXCOZTH\nS: ");
	for (int i = 0x001; i < 4096; i*=2) {
		printf("%d", (state->wrapper & i) >> idx);
		idx++;
	}
	printf("\n");
}

data * fetch() {
	bus_a_set(data_from_int(PC));
	bus_c_set(data_from_int(RAM_RM));

	mp_cycle();
	
	return bus_d_get();
}

uc_data * decode(data * d) {
	uc_data *decomposed = malloc(sizeof(uc_data));

	instr ins = decode_opc(d->wrapper);
	
	decomposed -> func = ins.func;
	decomposed -> reg = decode_reg(d->wrapper);
	decomposed -> ed = decode_cd(d->wrapper, ins.opc, decomposed -> reg, ins.is_extended);
	
	push(ins.nemo, get_register_names(decomposed -> reg), get_addressing_names((d->wrapper & 0x0C0)>>6), d->wrapper & 0x03F);
	//printf("[DEBUG][ASSEMBLY] %s %s %s:%d\n", ins.nemo, get_register_names(decomposed -> reg), get_addressing_names((d->wrapper & 0x0C0)>>6), d->wrapper & 0x03F);
	return decomposed;
}

instr decode_opc(int i) {
	int index = (i & 0xE00) >> 9;

	if (iset[index].opc == 0x7) {
		index = (i & 0x180) >> 7;
		return extended_iset[index];
	} else {
		return iset[index];	
	}
}

unsigned int decode_reg(int i) {
	return (i & 0x100) >> 8;
}

unsigned int decode_cd(int i, int opc, unsigned int reg, int is_extended) {
	int cd  = (i & 0x03F); //el cd 
	if (is_extended || opc == 0x3 || opc == 0x4) {
		return cd;	
	}

	if ( opc == 0x1 || opc == 0x5 || opc == 0x6) { //En el inmediato, opcodes 0x5 y 0x6 con BITS JI == 00 -> el dato efectivo es el cd
		if (! ((i & 0x0C0) >> 6)) //Si JI == 00
			return (i & 0x03F); //Extraemos el cd	
	}
	
	int option = (i & 0x0C0) >> 6; //Si no, extraemos el modo de direccionamiento

	return addressing(cd, alu_get_x(), option); //Y aplicamos el direccionamiento
}

void execute(uc_data * decoded) {
	unsigned int in[] = {decoded->reg, decoded->ed};
	decoded->func((void*)in);
}

void dump_decoded(uc_data * d) {
	printf("[DEBUG] DATA at %p (func: %p, reg: %s contains: %x, cd: %x\n", d, d->func, get_register_names(d -> reg), alu_get_reg(d -> reg), d -> ed);
}

void load_uc() {
	state = calloc(1, sizeof(data));
}

void enable_trap(int trap) {
	state -> binary.d10 = trap;
}

int trap() {
	return state->binary.d10;
}

void uc_overflow(int idx) {
	state -> binary.d8 = idx;
}

void uc_carry(int idx) {
	state -> binary.d7 = idx;
}

void uc_zero(int idx) {
	state -> binary.d9 = idx;
}

void uc_hlt(int idx) {
	state -> binary.d11 = idx;
}

void uc_backstep() {
	PC--;
}

void examine() {
	printf("Address: \n");
	int addr;
	scanf("%d", &addr);

	dump_ram_at(addr);
	scanf("%d", &addr);
}

void setaddr() {
	printf("Address: \n");
	int addr, data;
	scanf("%d", &addr);

	printf("Data: \n");
	scanf("%d", &data);
	
	set_ram_from_int(addr, data);
	dump_ram_at(addr);
	scanf("%d", &addr);
}

void help() {
	printf("TRAP CATCHED\n");
	printf("Options:\n");
	printf("c continue\n");
	printf("h this help\n");
	printf("l list executed instructions\n");
	printf("s set memory at\n");
	printf("x examine addr\n");
	printf("i write to input\n");
	printf("q quit\n");
}

void finish() {
	clear();
	printf("EXECUTION ENDED IN %d cycles\n", cycle);
	dump_ram(64, 64);
	dump_registers();
	dump_status();
	print_historic();
	dump_output();
	exit(0);
}

void loop() {
	while (1) {
		data * raw = fetch(); //Retrieve from ram
		uc_data * decoded = decode(raw); //Decode into opc, register, efective direction
		//clear();
		dump_ram(5,5); 	
		dump_registers();
		dump_status();
		//print_historic();
		execute(decoded); //Execute from alu
		//dump_decoded(decoded);
		//printf("[DEBUG][RUNTIME] CYCLE %d EXECUTED: %d RESULT: %d\n", cycle, PC, result);
		//printf("[DEBUG] YIELDING TO CES\n");
		ces_cycle();
		cycle++;
		PC++;
		if (trap()) {
			int flag = 1;
			while (flag) { 
				printf("$");
				char c = getchar();
		
				if (c=='c') {	
					flag = 0;
				} else if (c=='h') {
					help();
				} else if (c=='l') {
					print_historic();
				} else if (c=='s') {
					setaddr();
				} else if (c=='x') {
					examine();
				} else if (c=='i') {
					input();
				} else if (c=='q') {
					exit(0);
				}
			}
		} else {
			if (state->binary.d11) {
				printf("CPU is halted, finish execution? (s/n)\n");
				char c = getchar();
				if (c=='s')
					finish();
			}		
		}
	}
}


