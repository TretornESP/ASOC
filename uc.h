#ifndef _UC_H
#define _UC_H
#define MAX_CPU_CYCLES 0x32000
#include "iset.h"

typedef struct _uc_data {
	func_ptr func;
	unsigned int reg;
	unsigned int ed;
} uc_data;

typedef struct _uc_info {
	char opc[8];
	char reg[4];
	unsigned int cd;
} uc_info;

data * fetch();
uc_data * decode(data *);
instr decode_opc(int);
unsigned int decode_reg(int);
unsigned int decode_cd(int, int, unsigned int, int);
void execute(uc_data *);
void dump_decoded(uc_data *);
void loop();
void load_uc();
void set_state(data *);
data * get_state();
int trap();
void enable_trap(int);
int can_interrupt();
void enable_interrupts(int);
void set_pc(int);
void uc_overflow(int);
void uc_carry(int);
void uc_zero(int);
void uc_hlt(int);
void uc_backstep();
void uc_reti();
#endif
