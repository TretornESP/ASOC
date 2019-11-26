#ifndef _CES_H
#define _CES_H

#define OUT_D 0xFFC
#define OUT_S 0xFFD
#define IN_D 0xFFE
#define IN_S 0xFFF

#define NOTIFY 0x0
#define NOTHING_NEW 0xFFFF
#define NULL_CHAR 0xFFFFF
int ces_cycle();
void load_ces();
void dump_output();
int input();
#endif
