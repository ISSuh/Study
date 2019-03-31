#!/bin/sh

# make a static library with the mylib.c
# compile them 


gcc -c mylib.c
ar crv libmy.a mylib.o
ranlib libmy.a
gcc -o m main.c -L. -lm -lmy
./m
