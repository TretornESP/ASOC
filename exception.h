#ifndef _EXCEPTION_H
#define _EXCEPTION_H
void set_catchfire(int);
void bus_exception(const char *);
void mp_overflow(int);
void mp_unknown_code(int);
void int_overflow();
void ces_shm_err();
#endif
