#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "debug.h"
#include "memory.h"
#include "alu.h"
#define clear() printf("\033[H\033[J")

int debug_mode = 0;
pthread_t debug_thread;

void debug(const char* str) {
	if (debug_mode)	printf("[DEBUG] %s\n", str);
}

void * dump(void * args) {
	while (1) {
		clear();
		dump_ram(5, 5);
		dump_registers();
		sleep(1);
	}
}

int debuggin() {
	return debug_mode;
}

void enable_debug(int enabled) {
	debug_mode = enabled;
	if (enabled) {
		//pthread_create(&debug_thread, 0, dump, 0);		
	}
}
