CFLAGS=-Wall -Wextra -g

.PHONY: all
all: fizzbuzz reverse-bits array-size life

$(shell mkdir -p bin)

fizzbuzz: fizzbuzz.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

reverse-bits: reverse-bits.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

array-size: array-size.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

life: life.c
	gcc $(CFLAGS) -o bin/$@ $^ -I. -lncurses

.PHONY: clean
clean:
	rm -rf bin