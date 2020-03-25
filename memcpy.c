#include <assert.h>
#include <memory.h>
#include <stdint.h>
#include <sys/types.h>

void *memcpy_duff(void * __dst, const void * __src, size_t count)
{
    uint8_t * dst = __dst;
    const uint8_t * src = __src;
    ssize_t n = count;

    assert(count); // doesn't support 0 length
    assert(n == count); // signed size_t range is smaller

    switch (n % 8)
    {
    case 0: while (n > 0) { *dst++ = *src++;
    case 7:                 *dst++ = *src++;
    case 6:                 *dst++ = *src++;
    case 5:                 *dst++ = *src++;
    case 4:                 *dst++ = *src++;
    case 3:                 *dst++ = *src++;
    case 2:                 *dst++ = *src++;
    case 1:                 *dst++ = *src++;
            n -= 8; };
    }

    return __dst;
}

void *memcpy_my(void * __dst, const void * __src, size_t count)
{
    uint8_t *dst = --__dst;
    const uint8_t *src = --__src;
    ssize_t n = count;

    while (count--) // leverage branch-not-equal instructions (checks for zero without immediate)
        *++dst = *++src; // leverage pre-increment pointer instruction (e.g. PowerPC)

    return __dst;
}

void test(void *(*memcpy_test)(void * , const void *, size_t))
{
    uint8_t a[16] = {};
    uint8_t b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    // length < 8
    memcpy_test(a, b, 6);
    assert(!memcmp(a, b, 6));
    memset(a, 0, sizeof(a));

    // length == 8
    memcpy_test(a, b, 8);
    assert(!memcmp(a, b, 8));
    memset(a, 0, sizeof(a));

    // length > 8
    memcpy_test(a, b, 10);
    assert(!memcmp(a, b, 10));
    memset(a, 0, sizeof(a));

    // length == 2*8
    memcpy_test(a, b, 2*8);
    assert(!memcmp(a, b, 2*8));
    memset(a, 0, sizeof(a));
}

int main()
{
    test(&memcpy);

    test(&memcpy_duff);

    test(&memcpy_my);

    return 0;
}