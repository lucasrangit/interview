CFLAGS=-Wall -Wextra -g

.PHONY: all
all: fizzbuzz reverse-bits array-size life memcpy power-of-2 sizeof-struct

$(shell mkdir -p bin)

fizzbuzz: fizzbuzz.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

reverse-bits: reverse-bits.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

array-size: array-size.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

life: life.c
	gcc $(CFLAGS) -o bin/$@ $^ -I. -lncursesw

memcpy: memcpy.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

power-of-2: power-of-2.c
	gcc $(CFLAGS) -o bin/$@ $^ -I.

sizeof-struct: sizeof-struct.c
	gcc $(CLAGS) -o bin/$@ $^ -I.

.PHONY: clean
clean:
	rm -rf bin