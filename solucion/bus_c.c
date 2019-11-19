#include <stdlib.h>
#include "bus_c.h"
#include "memory.h"

data * bus_c_data;

data * bus_c_get() {
	return bus_c_data;
}

void bus_c_init() {
	bus_c_data = malloc(sizeof(data));
	bus_c_data-> wrapper = 0x0;
}

void bus_c_set(data * d) {
	bus_c_data  = d;
}
