CFLAGS=-Wall -Wextra -g

all: default fizzbuzz reverse-bits array-size

default:
	mkdir bin

fizzbuzz: fizzbuzz.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

reverse-bits: reverse-bits.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

array-size: array-size.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

.PHONY: clean

clean:
	rm -rf bin