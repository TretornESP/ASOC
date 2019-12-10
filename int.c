#include <stdlib.h>
#include "int.h"
#include "exception.h"
#include "uc.h"

interrupt * i_list;
int buffered;

void load_interrupt() {
	i_list = malloc(sizeof(interrupt)*INT_BUFFER);
	buffered = 0;
}

void push_int(int code) {
	if (!can_interrupt()) return;
	if (buffered >= INT_BUFFER-1) int_overflow();
	(i_list[buffered].code) = code;
	buffered++;
}

int interrupted() {
	return (buffered != 0);
}

interrupt pop_int() {
	interrupt in;
	if (buffered <= 0) return in; 
	in = i_list[buffered-1];
	buffered--;
	return in;
}
