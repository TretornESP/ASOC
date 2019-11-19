#include <stdlib.h>
#include "bus_a.h"

#include "memory.h"

data * bus_a_data;

data * bus_a_get() {
	return bus_a_data;
}

void bus_a_init() {
	bus_a_data = malloc(sizeof(data));
	bus_a_data-> wrapper = 0x0;
}

void bus_a_set(data * d) {
	bus_a_data  = d;
}
