#include <stdio.h>
#include "buses.h"
#include "exception.h"
#include "ces.h"
#include "memory.h"

int in_buf[400];
int i_sp = 0;

int o_buf[400];
int o_sp = 0;

int get_in_state() {
	return 1; //En el futuro lo cambiaremos
}

int get_out_state() {
	return 1; //En el futuro lo cambiaremos
}

int input() {
	int a = 0;
	printf("INPUT: ");
	scanf("%d", &a);
	in_buf[i_sp] = a;
	i_sp++;
	printf("\n");
	return a; 
}

void dump_output() {
	printf("The program wrote %d chars to output:\n", o_sp);
	for (int i = 0; i < o_sp; i++)
		printf("%c", o_buf[i]);
	printf("\n");
}

int get_in_data() {
	if (i_sp == 0) return NOTHING_NEW;
	int a = in_buf[i_sp];
	i_sp--;
	return a;
}

int output(int data) {
	if (data == NULL_CHAR) return 0;
	o_buf[o_sp] = data;
	o_sp++;
	printf("OUTPUT: ");
	printf("%c", data);
	printf("\n");
}

int get_mode(data * d) {
	return d->binary.d0;	
}

void load_ces() {
	bus_a_set(data_from_int(OUT_D));
	bus_c_set(data_from_int(RAM_WM));
	bus_d_set(data_from_int(NULL_CHAR));
	mp_cycle();
}


int ces_cycle() {
	check_bus_sanity();
	int out_d, in_d;

	bus_a_set(data_from_int(IN_S));
	bus_d_set(data_from_int(get_in_state()));
	bus_c_set(data_from_int(RAM_WM));
	mp_cycle();

	bus_a_set(data_from_int(OUT_S));
	bus_d_set(data_from_int(get_out_state()));
	bus_c_set(data_from_int(RAM_WM));
	mp_cycle();	

	bus_a_set(data_from_int(OUT_D));
	bus_c_set(data_from_int(RAM_RM));
	mp_cycle();

	out_d = (bus_d_get()->wrapper);
	output(out_d);

	bus_a_set(data_from_int(OUT_D));
	bus_c_set(data_from_int(RAM_WM));
	bus_d_set(data_from_int(NULL_CHAR));
	mp_cycle();

	if (get_in_data() == NOTHING_NEW) return 0;
	bus_a_set(data_from_int(IN_D));
	bus_d_set(data_from_int(get_in_data()));
	bus_c_set(data_from_int(RAM_WM));
	mp_cycle();

	
	return 1;
}
