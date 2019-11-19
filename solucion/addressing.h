#ifndef _ADDRESSING_H
#define _ADDRESSING_H

#define DIRECT 	 0x0
#define INDIRECT 0x1
#define INDEXED  0x2
#define POSTIND	 0x3	

int direct(int cd);
int indirect(int cd);
int indexed(int r, int cd);
int postind(int r, int cd);

unsigned int addressing(unsigned int, unsigned int, int);
char * get_addressing_names(int);

#endif
