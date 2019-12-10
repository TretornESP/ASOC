#include <stdio.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <unistd.h>
#include "buses.h"
#include "exception.h"
#include "ces.h"
#include "memory.h"
#include "int.h"

int in_buf[400];
int i_sp = 0;

int o_buf[400];
int o_sp = 0;

int get_in_state() {
	return 1; //En el futuro lo cambiaremos
}

int get_out_state() {
	return 1; //En el futuro lo cambiaremos
}

int input() {
	int a = 0;
	scanf(" %lc", &a);
	in_buf[i_sp] = a;
	i_sp++;
	push_int(KEYBOARD_READ_INT);
	printf("\n");
	return a; 
}

void *input_as(void* args) {
	key_t key1;
        key_t key2;
        if (-1 != open("/tmp/data", O_CREAT, 0777)) {
	        key1 = ftok("/tmp/data", 0);
        } else {
	        ces_shm_err();
        }
        if (-1 != open("/tmp/status", O_CREAT, 0777)) {
	        key2 = ftok("/tmp/status", 0);
        } else {
 	       ces_shm_err();
        }
 
        int id1 = shmget(key1, 0x1000, IPC_CREAT | SHM_R | SHM_W);
        int id2 = shmget(key2, 0x2000, IPC_CREAT | SHM_R | SHM_W);

	char *data = (char*) shmat(id1,0,0);
	char *status = (char*) shmat(id2,0,0);

	*data = '0';
	*status  = '0';

	while (1) {
		if (*status == '1') {
			in_buf[i_sp] = *data; //Si tecleas a muestra b
			i_sp++;
			push_int(KEYBOARD_READ_INT);
			*status = '0';

		}
	}
}

void load_async_input() { 
  
	pthread_t in;
	pthread_create(&in, NULL, input_as, NULL);
}

void dump_output() {
	printf("The program wrote %d chars to output:\n", o_sp);
	for (int i = 0; i < o_sp; i++)
		printf("%c", o_buf[i]);
	printf("\n");
}

int get_in_data() {
	if (i_sp <= 0) return NOTHING_NEW;
	int a = in_buf[i_sp-1];
	i_sp--;
	return a;
}

int output(int data) {
	if (data == NULL_CHAR) return 0;
	o_buf[o_sp] = data;
	o_sp++;
	printf("%c", data);
	printf("\n"); //CHECKMEIN
}

int get_mode(data * d) {
	return d->binary.d0;	
}

void load_ces() {
	bus_a_set(data_from_int(OUT_D));
	bus_c_set(data_from_int(RAM_WM));
	bus_d_set(data_from_int(NULL_CHAR));
	mp_cycle();
}


int ces_cycle() {
	check_bus_sanity();
	int out_d, in_d;

	bus_a_set(data_from_int(IN_S));
	bus_d_set(data_from_int(get_in_state()));
	bus_c_set(data_from_int(RAM_WM));
	mp_cycle();

	bus_a_set(data_from_int(OUT_S));
	bus_d_set(data_from_int(get_out_state()));
	bus_c_set(data_from_int(RAM_WM));
	mp_cycle();	

	bus_a_set(data_from_int(OUT_D));
	bus_c_set(data_from_int(RAM_RM));
	mp_cycle();

	out_d = (bus_d_get()->wrapper);
	output(out_d);

	bus_a_set(data_from_int(OUT_D));
	bus_c_set(data_from_int(RAM_WM));
	bus_d_set(data_from_int(NULL_CHAR));
	mp_cycle();

	int in = get_in_data();
	if (in == NOTHING_NEW) return 0;
	bus_a_set(data_from_int(IN_D));
	bus_d_set(data_from_int(in));
	bus_c_set(data_from_int(RAM_WM));
	mp_cycle();
	
	return 1;
}
