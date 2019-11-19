#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "memory.h"

int load_ram_from_file(char * filename) {
	FILE *infile;
	int * buffer;
	long numbytes;

	infile = fopen(filename, "r");

	if(infile == NULL) {
		printf("[ERROR] Loading file: %s, not found\n", filename);
		return 1;
	}

	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);

	fseek(infile, 0L, SEEK_SET);

	buffer = (int*) calloc(numbytes, sizeof(int));

	if (buffer == NULL) {
		printf("[ERROR] Allocating read buffer\n");
		return 2;
	}

	fread(buffer, sizeof(int), numbytes, infile);
	fclose(infile);

	for (int i = 0; i < numbytes; i++) {
		set_ram_from_int(i, buffer[i]);
	}

	return 0;
}

