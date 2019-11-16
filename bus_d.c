#include <stdlib.h>
#include "bus_d.h"
#include "memory.h"

data * bus_d_data;

data * bus_d_get() {
	return bus_d_data;
}

void bus_d_init() {
	bus_d_data = malloc(sizeof(data));
	bus_d_data-> wrapper = 0x0;
}

void bus_d_set(data * d) {
	bus_d_data  = d;
}

