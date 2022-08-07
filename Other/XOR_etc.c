#include "XOR_etc.h"
#include <stdio.h>

void add_xor(key k, void *data, unsigned size, unsigned int *random_nums, unsigned long *random_index)
{
    if (size == 0)
        return;

    int s = k->map[random_nums[(*random_index)++] % 256];
    for (unsigned long i = 0; i < size - 1; i++)
    {
        ((char *)data)[i] ^= k->map[(s + i + ((char *)data)[i + 1]) % 256];
        ((char *)data)[i] += k->map[(s + i) % 256];
    }
    ((char *)data)[size - 1] ^= k->map[s];
    ((char *)data)[size - 1] += k->map[s];
}

void sub_xor(key k, void *data, unsigned size, unsigned int *random_nums, unsigned long *random_index)
{
    if (size == 0)
        return;

    int s = k->map[random_nums[(*random_index)--] % 256];
    ((char *)data)[size - 1] -= k->map[s];
    ((char *)data)[size - 1] ^= k->map[s];

    if (size > 1)
        for (unsigned long i = size - 2;; i--)
        {
            ((char *)data)[i] -= k->map[(s + i) % 256];
            ((char *)data)[i] ^= k->map[(s + i + ((char *)data)[i + 1]) % 256];
            if (i == 0)
                break;
        }
}