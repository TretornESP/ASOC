#include <stdio.h>
#include "exception.h"
#include "instructions.h"

int catchfire = 0;

void set_catchfire(int c) {
	catchfire = c;
}

void header() {printf("[EXCEPTION] ");}
void halted() {printf(", CPU HALTED\n"); if (!catchfire) hlt(0);}
void bus_exception(const char * str) {
	header();
	printf("BUS %s CONTENT IS INVALID", str);
	halted();
}

void mp_overflow(int size) {
	header();
	printf("MEMORY OVERFLOW ADDR: %d", size);
	halted();
}

void mp_unknown_code(int code) {
	header();
	printf("UNKNOWN CONTROL CODE: %d", code);
	halted();
}

void int_overflow() {
	header();
	printf("TOO MANY INTERRUPTS");
	halted();
}

void ces_shm_err() {
	header();
	printf("Shared memory doesnt work, disable load_async_interrupts()\n");
	halted();
}
