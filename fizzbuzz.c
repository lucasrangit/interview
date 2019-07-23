#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * For numbers 1 to to n, print
 * Fizz for multiples of 3 and
 * Buzz for multiples of 5.
 */
void fizzbuzz(long n)
{
    for (int i = 1; i <= n; ++i) {
        char str[9] = "";

        if (i % 3 == 0)
            strcat(str, "Fizz");
        if (i % 5 == 0)
            strcat(str, "Buzz");

        if (strlen(str) == 0)
            printf("%i\n", i);
        else
            printf("%s\n", str);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return EINVAL;

    long n = strtol(argv[1], NULL, 10);
    if (errno != 0)
        return EINVAL;
    if (n < 0)
        return ERANGE;

    fizzbuzz(n);

    return 0;
}