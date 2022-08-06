#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "NumGen.h"
#include "../Shuffle/InternalShuffle.h"

// a simple hashing function to generate hash value of the key
unsigned int get_hash(key k)
{
    unsigned long rv = 0x182BE33FFF;
    for (int i = 0; i < 256; i++)
    {
        rv = (rv << 13) + rv + k->map[i] * (unsigned long) pow(131, i);
    }
    return rv;
}

unsigned long get_nums_required(key k, unsigned long size, int size_each)
{
    unsigned long required = 0;

    // min rows with size_each columns
    int min_num = size / size_each;

    // extra columns
    int extra = size % size_each;

    // total rows including half filled
    int rows_clmns = extra == 0 ? min_num : min_num + 1;

    required += rows_clmns;
    required += size_each;
    required += size * 2;
    required += rows_clmns;

    return required;
}

unsigned int *gen_random_numbers(key k, unsigned long count)
{
    if (count == 0) return NULL;

    // allocate required memory
    unsigned int *nums = malloc(sizeof(unsigned int) * count);
    if (nums == NULL)
        return NULL;

    for (count--; ; count--)
    {
        nums[count] = gen_num(k);
        if (count == 0)
            break;
    }
    return nums;
}

int gen_num(key k)
{
    // if seed has not been set
    if (!k->set_seed)
    {
        k->seed = get_hash(k);
        k->set_seed = true;
        srandom(k->seed);
    }
    return random();
}