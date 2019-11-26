#include "addressing.h"
#include "buses.h"
#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)

int doi(int cd, int r) {
	bus_a_set(data_from_int(cd+r));
	bus_c_set(data_from_int(RAM_RM));
	mp_cycle();
	
	int wr = bus_d_get() -> wrapper;

	//printf("CD: %x, R: %x, GOT: %x\n",cd ,r, wr);
	return wr;
}

int iop(int cd, int r) {
	int sig = r;
	bus_a_set(data_from_int(cd));
	bus_c_set(data_from_int(RAM_RM));

	mp_cycle();
	int addr = bus_d_get()->wrapper;
	//printf("AFTER STEP ONE GOT: %d\n", addr);
	bus_a_set(data_from_int(addr+sig));
	bus_c_set(data_from_int(RAM_RM));
	
	mp_cycle();

	addr = bus_d_get() -> wrapper;
	//printf("AFTER STEP TWO GOT: %d\n", addr);
	return addr;
}

typedef int (*func_ptr)(int, int);

func_ptr address_vectors[] = {doi, doi, iop, iop};

char *addressing_names[] = {"direct", "indirect", "indexed", "post-indexed"};

char * get_addressing_names(int index) {
	return addressing_names[index];
}

unsigned int addressing(unsigned int cd, unsigned int reg, int option) {
	if (option == DIRECT || option == INDIRECT) reg = 0;
	return address_vectors[option](cd, reg);
}

