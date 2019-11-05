#include <stdlib.h>
#include <stdio.h>

#include "bus_a.h"
#include "bus_c.h"
#include "bus_d.h"

#include "memory.h"

data *RAM;

int set_ram_from_int(int pos, int i) {
	data d = {.wrapper  = i};

	if (pos < RAM_SIZE) {
		RAM[pos].wrapper = i;
		return 0;
	} 

	return -1;
}

void load_ram() {
	RAM = calloc(RAM_SIZE, sizeof(data));
}

int int_from_data(data * d) {
	return d->wrapper;
}

data* data_from_int(int i) {
	data *d = malloc(sizeof(data));
	d->wrapper = i;

	return d;
}

void dump_ram_at(int pos) {
	int w = RAM[pos].wrapper;
	bitfield r = RAM[pos].binary;

	printf("+----- RAM AT %03x Hex: %03x ------+\n", pos, w);
	printf("|    d0: %1d d1: %1d  d2: %1d  d3: %1d   |\n", r.d0, r.d1, r.d2, r.d3);
	printf("|    d4: %1d d5: %1d  d6: %1d  d7: %1d   |\n", r.d4, r.d5, r.d6, r.d7);
	printf("|    d8: %1d d9: %1d d10: %1d d11: %1d   |\n", r.d8, r.d9, r.d10, r.d11);	
	printf("+--------------------------------+\n");
}

int mp_cycle() {
	int mode = bus_c_get()->wrapper;
	int addr = bus_a_get()->wrapper;
	int data = bus_d_get()->wrapper;

	if (addr >= RAM_SIZE) return -1;

	if (mode == RAM_RM) {
		bus_d_set(RAM[addr]);
 	} else if (mode == RAM_WM) {
		set_ram_from_int(addr, data);
	} else {
		return -2;	
	}

	return 0;
}
