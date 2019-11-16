#!/bin/bash
rm emulator
gcc -g main.c uc.c alu.c memory.c iset.c instructions.c buses.c bus_a.c bus_d.c bus_c.c addressing.c debug.c exception.c historic.c -o emulator -lpthread
./emulator
