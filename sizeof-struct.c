#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    long b;
    short a;
    char c;
} my_struct_packed;
#pragma pack(pop)

// alternative form:
// typedef struct {
//     short a;
//     long b;
//     char c;
// } __attribute__((packed)) my_struct_packed;

typedef struct {
    short a;    // 2
    long b;     // 8
    char c;     // 1
} my_struct;

int main()
{
    // Without making any assumptions about architecture, compiler, etc... determine the size of my_struct
    printf("sizeof(short): %zu\n", sizeof(short));
    printf("sizeof(int): %zu\n", sizeof(int));
    printf("sizeof(long): %zu\n", sizeof(long));
    printf("sizeof(long long): %zu\n", sizeof(long long));

    // Determine if CPU is 32 or 64-bit... at compile time (at runtime use uname() on Linux)
    printf("sizeof(size_t): %zu\n", sizeof(size_t));
    printf("sizeof(void *): %zu\n", sizeof(void *));

    // Print the size to stdout
    printf("sizeof(my_struct): %zu\n", sizeof(my_struct));

    // Q: If this is struct is memory mapped registers on ARM. Does alignment matter? How do you align struct members in memory?
    // A: __attribute__((alignment (4), packed))

    // How to do pack it or order it to reduce padding?
    printf("sizeof(my_struct_packed): %zu\n", sizeof(my_struct_packed));

    // TODO sizeof array https://en.wikipedia.org/wiki/Sizeof#Application_to_arrays

    return 0;
}
