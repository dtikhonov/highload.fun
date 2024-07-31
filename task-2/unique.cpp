/* Task 2: Count number of unique tokens from stdin
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

/* How much memory do we need?  We need space for the buckets in the
 * hash table and space for individual entries.
 *
 * We know that there are about 1,000,000 unique tokens.  With average
 * chain length of 4, we need 250,000 buckets.
 *
 * Each entry contains the string (maximum 16 bytes, its length, and
 * link to the next entry).  There are some strategies to minimize this
 * space.
 *
 * We will place everything into a single chunk of memory.
 */

unsigned
djb2 (const char *str, unsigned len)
{
    const char *const end = str + len;
    unsigned hash = 5381;
    int c;

    while (str < end)
    {
        c = *str++;
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

#define HASH_BITS 18

#define HASH_MASK ((1u << HASH_BITS) - 1)

#define BUCKET_COUNT (1u << HASH_BITS)

struct el {
    unsigned next_el;
    unsigned len;
    char     str[16];
};

struct hash {
    unsigned buckets[BUCKET_COUNT]; /* indexes els */
    unsigned count;
    struct el els[0];
};

#define NEED_MEM sizeof(struct hash) + sizeof(struct el) * 1'100'000

int
main (void)
{
    struct stat st;

    int s = fstat(STDIN_FILENO, &st);
    if (s != 0)
    {
        perror("fstat");
        return 1;
    }

    const char *buf = (char *) mmap(0, st.st_size, PROT_READ,
                            MAP_PRIVATE | MAP_POPULATE, STDIN_FILENO, 0);

    struct hash *const hash = (struct hash *) malloc(NEED_MEM);
    memset(&hash->buckets, 0, sizeof(hash->buckets));
    hash->count = 1;    /* 0 is not valid */
    const char *const end = (buf + st.st_size);
    struct el *el;
    while (buf < end)
    {
        /* Here we assume that there is always a newline */
        const char *const nl = strchr(buf, '\n');
        const unsigned len = nl - buf;
        const unsigned slot = djb2(buf, len) & HASH_MASK;
        unsigned *next_el = &hash->buckets[slot];
        while (*next_el)
        {
            el = &hash->els[*next_el];
            if (el->len == len && 0 == memcmp(buf, el->str, len))
                goto next;
            next_el = &el->next_el;
        }
        /* Add element */
        *next_el = hash->count++;
        el = &hash->els[ *next_el ];
        el->next_el = 0;
        el->len = len;
        memcpy(el->str, buf, len);
  next:
        buf = nl + 1;
    }

    printf("%u\n", hash->count - 1);

    return 0;
}
