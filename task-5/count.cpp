/* Task 5: count number of bytes whose value is 127.
 *
 * The trick here is SIMD and bit manipulation.
 */

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

/* Assume: that word size is 8 bytes for now */

/* Assume: input size is divisible by 8.  The problem states:
 *
 *   " Numbers quantity is 250 000 000."
 */

/* Assume: reading from stdin never fails */

int
main (void)
{
    unsigned char buf[0x1000];
    const uintptr_t *el, *last;
    uintptr_t v;
    size_t nread;
    unsigned res;

    res = 0;

    do
    {
        nread = (size_t) read(STDIN_FILENO, buf, sizeof(buf));
        last = (uintptr_t *) (buf + nread);
        for (el = (uintptr_t *) buf; el < last; ++el)
        {
            v = (*el & 0x7F7F7F7F7F7F7F7F) + ((~*el & 0x8080808080808080) >> 7);
            v &= 0x8080808080808080;
            v >>= 7;
            v = (v >> 32) + (v & 0xFFFFFFFF);
            v = (v >> 16) + (v & 0xFFFF);
            v = (v >> 8)  + (v & 0xFF);
            res += v;
        }
    }
    while (nread == sizeof(buf));

    printf("%u\n", res);

    return 0;
}
