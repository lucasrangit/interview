CFLAGS=-Wall -Wextra

all: fizzbuzz reverse-bits

fizzbuzz: fizzbuzz.c
	gcc $(CFLAGS) -o $@ $^ -I.

reverse-bits: reverse-bits.c
	gcc $(CFLAGS) -o $@ $^ -I.
