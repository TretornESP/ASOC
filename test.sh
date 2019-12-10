#!/bin/bash
rm emulator
gcc -g main.c uc.c alu.c memory.c iset.c instructions.c buses.c bus_a.c bus_d.c bus_c.c addressing.c ces.c debug.c loader.c exception.c historic.c int.c -o emulator -lpthread
if [[ $# -eq 1 ]]; then
	./emulator $1
else
	./emulator
fi
