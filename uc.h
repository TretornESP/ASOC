#ifndef _UC_H
#define _UC_H

#include "iset.h"

typedef struct _uc_data {
	func_ptr func;
	unsigned int reg;
	unsigned int ed;
} uc_data;

#endif
