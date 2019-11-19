#!/bin/bash

#Usage: ./test.sh [name_of_program.simplez]
rm emulator
gcc -g main.c uc.c alu.c memory.c iset.c instructions.c buses.c bus_a.c bus_d.c bus_c.c addressing.c debug.c loader.c exception.c historic.c -o emulator -lpthread
if [[ $# -eq 1 ]]; then
	./emulator $1
else
	./emulator
fi
