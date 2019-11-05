#include "bus_c.h"
#include "memory.h"

data * bus_c_data;

data * bus_c_get() {
	return bus_c_data;
}

void bus_c_set(data * d) {
	bus_c_data  = d;
}
