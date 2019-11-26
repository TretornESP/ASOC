#ifndef _MEMORY_H
#define _MEMORY_H
#define RAM_SIZE 4096

#define RAM_RM 0 //Vamos a leer de la ram
#define RAM_WM 1 //Vamos a escribir en la ram

typedef struct _bitfield {
	unsigned int d0 : 1;
	unsigned int d1 : 1;
	unsigned int d2 : 1;
	unsigned int d3 : 1;
	unsigned int d4 : 1;
	unsigned int d5 : 1;
	unsigned int d6 : 1;
	unsigned int d7 : 1;
	unsigned int d8 : 1;
	unsigned int d9 : 1;
	unsigned int d10 : 1;
	unsigned int d11 : 1;
} __attribute__((packed)) bitfield;

typedef union _data {
	bitfield binary;
	int wrapper;
} data;

int set_ram_from_int(int,int);

int int_from_data(data*);
data * data_from_int(int);

void load_ram();
void dump_ram_at(int);
int mp_cycle();
void dump_ram(int, int);
int read_mode_from_bus(data *);
int read_disp_from_bus(data *);
void check_bus_sanity();
#endif
