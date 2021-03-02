#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))

static int a[] = {1, 2, 3, 4};

int main()
{
    int *b = (int *)calloc(4, sizeof(int));

    printf("a count %lu\n", ARRAY_SIZE(a));
    printf("b count %lu\n", ARRAY_SIZE(b));

    free(b);

    return 0;
}