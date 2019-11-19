#include <stdlib.h>
#include <stdio.h>

#include "bus_a.h"
#include "bus_c.h"
#include "bus_d.h"
#include "exception.h"
#include "debug.h"
#include "memory.h"

#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)


data *RAM[RAM_SIZE];

int set_ram_from_int(int pos, int i) {

	if (pos < RAM_SIZE) {
		RAM[pos]->wrapper = i;
		return 0;
	} 

	return -1;
}

void load_ram() {

	for (int i = 0; i < RAM_SIZE; i++)
		RAM[i] = malloc(sizeof(data));
		
}

int int_from_data(data * d) {
	return d->wrapper;
}

data* data_from_int(int i) {
	data *d = malloc(sizeof(data));
	d->wrapper = i;

	return d;
}

void dump_ram(int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int addr = ((i*cols)+j);
			if (addr >= RAM_SIZE) mp_overflow(addr);
			printf(" %3x ", RAM[addr] -> wrapper);
		}
		printf("\n");
	}
}

void dump_ram_at(int pos) {
	int w = RAM[pos]->wrapper;
	bitfield r = RAM[pos]->binary;

	printf("+----- RAM AT %03x Hex: %03x ------+\n", pos, w);
	printf("|    d0: %1d d1: %1d  d2: %1d  d3: %1d   |\n", r.d0, r.d1, r.d2, r.d3);
	printf("|    d4: %1d d5: %1d  d6: %1d  d7: %1d   |\n", r.d4, r.d5, r.d6, r.d7);
	printf("|    d8: %1d d9: %1d d10: %1d d11: %1d   |\n", r.d8, r.d9, r.d10, r.d11);	
	printf("+--------------------------------+\n");
}

void check_bus_sanity() {
	if (bus_c_get() == NULL) bus_exception("c");
	if (bus_d_get() == NULL && bus_c_get()->wrapper == RAM_WM) bus_exception("d");
	if (bus_a_get() == NULL) bus_exception("a");
}

int mp_cycle() {
	check_bus_sanity();
	int mode = bus_c_get()->wrapper;
	int addr = bus_a_get()->wrapper;

	if (addr >= RAM_SIZE) mp_overflow(addr);

	if (mode == RAM_RM) {
		bus_d_set(RAM[addr]);
		//printf("READING %x FROM: %x\n", RAM[addr]->wrapper, addr);
 	} else if (mode == RAM_WM) {
		int data = bus_d_get()->wrapper;
		//printf("WRITING %x TO: %x\n", data, addr);
		set_ram_from_int(addr, data);
	} else {
		mp_unknown_code(mode);
	}

	return 0;
}
