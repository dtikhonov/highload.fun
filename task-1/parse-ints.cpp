/*
 * Task 1 - parse integers.
 */

#include <stdio.h>
#include <unistd.h>

#define FORTY_EIGHT_ZEROS \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

static const int lookup[10]['9' + 1] = {
    {
#define F 1
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 10
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 100
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 1'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 10'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 100'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 1'000'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 10'000'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 100'000'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F, 3 * F, 4 * F, 5 * F, 6 * F, 7 * F, 8 * F, 9 * F,
    },
    {
#undef F
#define F 1'000'000'000
        FORTY_EIGHT_ZEROS,
        0, 1 * F, 2 * F,
    },
};

int
main (void)
{
    char bufs[2][0x1000];

    size_t nread;
    long sum;
    int buf_idx, lu_idx;
    const char *p;

    sum = buf_idx = lu_idx = 0;

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
                sum += lookup[lu_idx++][(int)*p];

        buf_idx = !buf_idx;
        for (p = bufs[buf_idx] + sizeof(bufs[0]) - 1; *p != '\n'; --p)
            sum += lookup[lu_idx++][(int)*p];
        lu_idx = 0;
    }
    while (nread == sizeof(bufs[0]));

    printf("%ld\n", sum);

    return 0;
}
