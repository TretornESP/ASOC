#include "historic.h"
#include "debug.h"
#include <string.h>
#include <stdio.h>

struct command hd[HISTORY_SIZE];
int idx = 0;

void push(char* nemo, char* reg, char* addr, int mem) {

	if (idx >= HISTORY_SIZE - 1 && debuggin()) {
		printf("Historic is full\n");
		return;
	}

	strcpy(hd[idx].nemo, nemo);
	strcpy(hd[idx].reg, reg);
	strcpy(hd[idx].addr, addr);
	hd[idx].mem = mem;

	idx++;
}

void print_historic() {
	for (int i = 0; i < idx; i++) {
		printf("[DEBUG][ASSEMBLY] %s %s %s:%d\n", hd[i].nemo, hd[i].reg, hd[i].addr, hd[i].mem);
	}
}
