/* Task 5: count number of bytes whose value is 127.
 *
 * The trick here is SIMD and bit manipulation.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

/* Assume: that word size is 8 bytes for now */

/* Assume: input size is divisible by 8.  The problem states:
 *
 *   " Numbers quantity is 250 000 000."
 */

/* Assume: reading from stdin never fails */

int
main (void)
{
    const uintptr_t *el, *last;
    uintptr_t v;
    unsigned res;
    struct stat st;

    res = 0;

    int s = fstat(STDIN_FILENO, &st);
    if (s != 0)
    {
        perror("fstat");
        return 1;
    }

    const char *buf = (char *) mmap(0, st.st_size, PROT_READ,
                            MAP_PRIVATE | MAP_POPULATE, STDIN_FILENO, 0);
    last = (uintptr_t *) (buf + st.st_size);
    for (el = (uintptr_t *) buf; el + 7 < last; el += 8)
    {
        uintptr_t acc = 0;

#define DO_ELEM(_idx) do { \
        v = (el[_idx] & 0x7F7F7F7F7F7F7F7F) + \
                        ((~el[_idx] & 0x8080808080808080) >> 7); \
        v &= 0x8080808080808080; \
        v >>= 7; \
        acc += v; \
} while (0)

        DO_ELEM(0);
        DO_ELEM(1);
        DO_ELEM(2);
        DO_ELEM(3);
        DO_ELEM(4);
        DO_ELEM(5);
        DO_ELEM(6);
        DO_ELEM(7);

        acc = (acc >> 32) + (acc & 0xFFFFFFFF);
        acc = (acc >> 16) + (acc & 0xFFFF);
        acc = (acc >> 8)  + (acc & 0xFF);
        res += acc;

    }

    printf("%u\n", res);

    return 0;
}
