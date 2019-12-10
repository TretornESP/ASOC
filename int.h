#ifndef _INT_H
#define _INT_H
#define INT_BUFFER 8
#define IVT 0x400
#define IV_SIZE 1

#define SCREEN_WRITE_INT   0x0
#define SCREEN_READ_INT    0x1
#define KEYBOARD_WRITE_INT 0x2
#define KEYBOARD_READ_INT  0x3

typedef struct _interrupt {
	int code;
} interrupt;

int interrupted();
void load_interrupt();
interrupt pop_int();
void push_int(int);
#endif
