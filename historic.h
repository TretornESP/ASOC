#ifndef _HISTORIC_H
#define _HISTORIC_H
#define HISTORY_SIZE 65536

struct command {
	char nemo[16];
	char reg[4];
	char addr[32];
	int  mem;
};
void push(char*,char*,char*,int);
void print_historic();
#endif
