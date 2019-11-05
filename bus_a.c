#include "bus_a.h"

#include "memory.h"

data * bus_a_data;

data * bus_a_get() {
	return bus_a_data;
}

void bus_a_set(data * d) {
	bus_a_data  = d;
}
