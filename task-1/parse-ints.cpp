/*
 * Task 1 - parse integers.
 */

#include <stdio.h>
#include <unistd.h>

int
main (void)
{
    char bufs[2][0x1000];

    size_t nread;
    unsigned counts[10] = {};
    int buf_idx, lu_idx;
    const char *p;

    buf_idx = lu_idx = 0;

    bufs[!buf_idx][ sizeof(bufs[0]) - 1 ] = '\n';

    do
    {
        nread = (size_t)
            /* Pretend that reading from stdin cannot fail... */
            read(STDIN_FILENO, bufs[buf_idx], sizeof(bufs[buf_idx]));

        /* Find last newline: */
        for (p = bufs[buf_idx] + nread - 1; *p != '\n'; --p)
            ;

        for (--p; p >= bufs[buf_idx]; --p)
            if (*p == '\n')
                lu_idx = 0;
            else
                counts[lu_idx++] += *p - '0';

        buf_idx = !buf_idx;
        for (p = bufs[buf_idx] + sizeof(bufs[0]) - 1; *p != '\n'; --p)
            counts[lu_idx++] += *p - '0';
        lu_idx = 0;
    }
    while (nread == sizeof(bufs[0]));

    unsigned long sum = 0;
    for (int c = 0, factor = 1; c <= 9; ++c, factor *= 10)
        sum += (unsigned long) counts[c] * (unsigned long) factor;

    printf("%ld\n", sum);

    return 0;
}
