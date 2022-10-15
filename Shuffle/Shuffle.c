#include "Shuffle.h"
#include "InternalShuffle.c"

#define next_random k->map[random_nums[(*(r_index))++] % 256]
#define prev_random k->map[random_nums[(*(r_index))--] % 256]

void shuffle(key k, void *data, unsigned long size, int size_each, unsigned int *random_nums, unsigned long *r_index)
{
    if (data == NULL || k == NULL)
        return;

    // calculate (number of rows and columns)
    int min_num = size / size_each;
    int extra = size % size_each;
    int rows_clmns = extra == 0 ? min_num : min_num + 1;

    // shuffle rows
    for (int i = 0; i < rows_clmns; i++)
        shuffle_row(data + (i * size_each), i == min_num ? extra : size_each, next_random);
    
    // change rows
    char temp[size_each];
    for (int i = 0; i < min_num; i++)
    {
        int new = (next_random + 1 + i) % min_num;
        memcpy(temp, data + i * size_each, size_each);
        memcpy(data + i * size_each, data + new * size_each, size_each);
        memcpy(data + new * size_each, temp, size_each);
    }
    if (min_num < rows_clmns)
    {
        int new = (next_random + 1) % min_num;
        memcpy(temp, data + min_num * extra, extra);
        memcpy(data + min_num * extra, data + new * extra, extra);
        memcpy(data + new * extra, temp, extra);
    }

    // shuffle columns
    for (int i = 0; i < size_each; i++)
        shuffle_clmn(data + i, size_each, i >= extra ? min_num : rows_clmns, next_random);
    
    // swap
    for (unsigned long i = 0; i < size; i++)
        swap(data + i, data + random_nums[(*(r_index))++] % size);
}

void unshuffle(key k, void *data, unsigned long size, int size_each, unsigned int *random_nums, unsigned long *r_index)
{
    if (data == NULL || k == NULL)
        return;

    int min_num = size / size_each;
    int extra = size % size_each;
    int rows_clmns = extra == 0 ? min_num : min_num + 1;

    // swap
    for (unsigned long i = size - 1; ; i--)
    {
        swap(data + i, data + random_nums[(*(r_index))--] % size);
        if (i == 0) break;
    }

    // unshuffle columns
    for (int i = size_each - 1; i >= 0; i--)
        unshuffle_clmn(data + i, size_each, i >= extra ? min_num : rows_clmns, prev_random);

    // revert rows
    char temp[size_each];
    if (min_num < rows_clmns)
    {
        int new = (prev_random + 1) % min_num;
        memcpy(temp, data + min_num * extra, extra);
        memcpy(data + min_num * extra, data + new * extra, extra);
        memcpy(data + new * extra, temp, extra);
    }
    for (int i = min_num - 1; i >= 0; i--)
    {
        int new = (prev_random + 1 + i) % min_num;
        memcpy(temp, data + i * size_each, size_each);
        memcpy(data + i * size_each, data + new * size_each, size_each);
        memcpy(data + new * size_each, temp, size_each);
    }

    // unshuffle rows
    for (int i = rows_clmns - 1; i >= 0; i--)
        unshuffle_row(data + (i * size_each), i == min_num ? extra : size_each, prev_random);
}