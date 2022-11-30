#include "Shuffle.h"
#include "../Map/Map.h"
#include "../NumGen/Powers.h"
#include "InternalShuffle.c"


#define next_random k->map[random_nums[(*(r_index))++] % 256]
#define prev_random k->map[random_nums[(*(r_index))--] % 256]

void shuffle(key k, void *data, unsigned long size, unsigned int size_each, unsigned int *random_nums, unsigned long *r_index)
{
    if (data == NULL || k == NULL)
        return;

    // calculate (number of rows and columns)
    unsigned long min_num = size / size_each;                      // number of rows
    unsigned int extra = size % size_each;                         // number of columns in the last row
    unsigned long rows_clmns = extra == 0 ? min_num : min_num + 1; // total number of rows including the less one

    // shuffle rows
    for (unsigned int i = 0; i < rows_clmns; i++)
        shuffle_row(data + (i * size_each), i == min_num ? extra : size_each, next_random);

    // swap rows
    char temp[size_each];
    for (unsigned long i = 0; i < min_num; i++)
    {
        unsigned int new = (next_random + 1 + i) % min_num;
        memcpy(temp, data + i * size_each, size_each);
        memcpy(data + i * size_each, data + new *size_each, size_each);
        memcpy(data + new *size_each, temp, size_each);
    }
    if (extra)
    {
        unsigned int new = (next_random + 1) % min_num;
        memcpy(temp, data + min_num * extra, extra);
        memcpy(data + min_num * extra, data + new *extra, extra);
        memcpy(data + new *extra, temp, extra);
    }

    // shuffle columns
    for (int i = 0; i < size_each; i++)
        shuffle_clmn(data + i, size_each, i >= extra ? min_num : rows_clmns, next_random);

    // swap
    for (unsigned long i = 0; i < size; i++)
        swap(data + i, data + random_nums[(*(r_index))++] % size);
}

void unshuffle(key k, void *data, unsigned long size, unsigned int size_each, unsigned int *random_nums, unsigned long *r_index)
{
    if (data == NULL || k == NULL)
        return;

    unsigned long min_num = size / size_each;
    unsigned int extra = size % size_each;
    unsigned long rows_clmns = extra == 0 ? min_num : min_num + 1;

    // swap
    for (unsigned long i = size - 1;; i--)
    {
        swap(data + i, data + random_nums[(*(r_index))--] % size);
        if (i == 0)
            break;
    }
    
    // unshuffle columns
    for (int i = size_each - 1; i >= 0; i--)
        unshuffle_clmn(data + i, size_each, i >= extra ? min_num : rows_clmns, prev_random);

    // swap rows
    char temp[size_each];
    if (extra)
    {
        unsigned int new = (prev_random + 1) % min_num;
        memcpy(temp, data + min_num * extra, extra);
        memcpy(data + min_num * extra, data + new *extra, extra);
        memcpy(data + new *extra, temp, extra);
    }
    for (unsigned long i = min_num - 1;; i--)
    {
        unsigned int new = (prev_random + 1 + i) % min_num;
        memcpy(temp, data + i * size_each, size_each);
        memcpy(data + i * size_each, data + new *size_each, size_each);
        memcpy(data + new *size_each, temp, size_each);
        if (i == 0)
            break;
    }

    // unshuffle rows
    for (unsigned int i = rows_clmns - 1;; i--)
    {
        unshuffle_row(data + (i * size_each), i == min_num ? extra : size_each, prev_random);
        if (i == 0)
            break;
    }
}

bool shuffle_powers(key k)
{
    unsigned int size_each = sizeof(unsigned long);

    unsigned long num_req = 256;
    unsigned int random_nums[num_req];

    map(k, powers, 256 * sizeof(unsigned long));
    gen_random_numbers(k, random_nums, num_req);
    unsigned long random_index = 0;

    unsigned long temp;
    for (int i = 0; i < 256; i++)
    {
        unsigned int new = (k->map[random_nums[random_index++] % 256] + 1) % 256;
        temp = powers[i];
        powers[i] = powers[new];
        powers[new] = temp;
    }
    return true;
}