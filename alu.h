#ifndef _ALU_H
#define _ALU_H
typedef int reg;
char *get_register_names(int);

reg alu_get_reg(int);
void alu_set_reg(int, reg);
reg alu_get_acc();
void alu_set_acc(reg);
reg alu_get_x();
void alu_set_x(reg);
void dump_registers();
#endif
