#include "instructions.h"
#include "buses.h"
#include "alu.h"
#include "uc.h"
#define SIGN(i) ((i & 0x20) >> 5) ? -(i & 0x1F) : (i & 0x1F)

//Completame
void* ld(void* input){}
void* st(void* input){}
void* add(void* input){}
void* br(void* input){}
void* bz(void* input){}
void* ldh(void* input){}
void* subh(void* input){}
void* ext(void* input){hlt(input);return 0;} //De momento dejame así

void* hlt(void* input){
	uc_hlt(1);
	uc_backstep();
}

void* ei(void* input){return 0;}
void* di(void* input){return 0;}


//Esta es una instrucción nueva! Como sub pero le restas un registro a otro
//El formato es: OOOO OXXX XX12
//O: Opcode, 1111 11
//X: Ignorado, da igual
//1: Registro 1 (0 = x, 1 = acc)
//2: Registro 2 (0 = x, 1 = acc)
//Ejemplo: subr x, acc en binario 1111 1000 0001 y el equivalente lenguaje c es: X=X-ACC
void* subr(void* input) {
	unsigned int * in = (unsigned int*) input;

	in[0] = (in[1] & 0x2) >> 1;
	in[1] = alu_get_reg(in[1] & 0x1);

	alu_sub(in);
	return 0;
}
