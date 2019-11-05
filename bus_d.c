#include "bus_d.h"
#include "memory.h"

data * bus_d_data;

data * bus_d_get() {
	return bus_d_data;
}

void bus_d_set(data * d) {
	bus_d_data  = d;
}
