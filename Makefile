CFLAGS=-Wall -Wextra

all: fizzbuzz reverse-bits array-size

fizzbuzz: fizzbuzz.c
	gcc $(CFLAGS) -o $@ $^ -I.

reverse-bits: reverse-bits.c
	gcc $(CFLAGS) -o $@ $^ -I.

array-size: array-size.c
	gcc $(CFLAGS) -o $@ $^ -I.
