#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Reverse the bits in an interger.
 */
unsigned int reverse_bits(unsigned int n)
{
    long rev = 0;
    int bits = sizeof(n) * 8;

    for (int i = 0; (i < bits) && n; ++i) {
        if (n & 1)
            rev |= 1 << ((bits - 1) - i);
        n >>= 1;
    }

    return rev;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return EINVAL;

    int n = (int)strtol(argv[1], NULL, 10);
    if (errno != 0)
        return EINVAL;
    if (n < 0 || n > UINT_MAX)
        return ERANGE;

    printf("%d\n", reverse_bits(n));

    return 0;
}