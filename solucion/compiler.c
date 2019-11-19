#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_VALUE 0x000
#define MAX_VALUE 0xFFF
#define EXIT_CODE 0x1000

int * buffer;

int main(int argc, char* argv[]) {

	int wrapper = 0;
	int idx = 0;

	int memory = -1;
	char filename[64] = "out.simplez";

	printf("How much memory do you have? (in doubt use: 4096) \n");
	scanf("%d", &memory);
	if (memory == -1 || memory == 0) memory = 4096;

	buffer = calloc(memory, sizeof(int));
	if (!buffer) {printf("Error allocating memory\n"); return 1;}

	printf("Output file: (Max: 64 chars or else... ;) \n");
	scanf("%s", filename);
	if (!strcmp(filename, "\0")) strcpy(filename, "out.simplez");
	
	printf("Write now the code in hex, WITHOUT 0x prefix, example: RAM[0]: 0a2\n");

	while (1) {
		printf("RAM[%x]: ", idx);
		scanf("%x", &wrapper);
		if (wrapper == EXIT_CODE) break;
		if (wrapper < MIN_VALUE || wrapper > MAX_VALUE)	{
			printf("Invalid input, valid [%d,%d] or %d to write and exit\n", MIN_VALUE, MAX_VALUE, EXIT_CODE);
		} else {			
			buffer[idx] = wrapper;
			wrapper = 0x0;
			idx++;
		}
	}

	FILE *fp = fopen(filename, "w+");

	fwrite(buffer, sizeof(int), idx, fp);

	fclose(fp);

	printf("%ld bytes written to %s\n", sizeof(buffer), filename);

	return 0;
}
