#include "Encrypt.h"
#include "NumGen/NumGen.h"
#include "Other/XOR_etc.h"
#include "Map/Map.h"
#include "Shuffle/Shuffle.h"
#include "Shuffle/InternalShuffle.h"
#include "NumGen/NumGen.h"

bool iencrypt(key k, void *data, unsigned long size)
{
    if (size == 0 || data == NULL || k == NULL)
        return false;

    if (!shuffle_powers(k))
        return false;

    // size of each row
    unsigned int size_each = calc_size_each(k) % size + 1;

    // number of operations
    unsigned int max = (gen_num(k) % (k->max_iterations - k->min_iterations)) + k->min_iterations;

    // number of random numbers that will be used
    unsigned long numbers_required = get_nums_required(k, size, size_each);
    numbers_required *= 2;   // shuffle is called twice
    numbers_required += 1;   // for xor

    // allocate required memory for random numbers
    unsigned int *random_numbers = malloc(sizeof(unsigned int) * numbers_required);
    if (random_numbers == NULL)
        return false;

    for (int i = 0; i < max; i++)
    {
        // used by helper functions
        // index of random number to be used next
        unsigned long random_index = 0;

        // load random numbers that will be used
        gen_random_numbers(k, random_numbers, numbers_required);

        if (random_numbers == NULL)
            return false;

        // map each byte using the key
        map(k, data, size);
        shuffle(k, data, size, size_each, random_numbers, &random_index);


        // do some xor operation
        add_xor(k, data, size, random_numbers, &random_index);
        shuffle(k, data, size, size_each, random_numbers, &random_index);
    }

    k->seed = 0;
    k->set_seed = false;
    free(random_numbers);
    return true;
}

bool idecrypt(key k, void *data, unsigned long size)
{
    if (size == 0 || data == NULL || k == NULL)
        return false;

    if (!shuffle_powers(k))
        return false;

    // size of each row
    unsigned int size_each = calc_size_each(k) % size + 1;

    // number of operations
    unsigned int max = (gen_num(k) % (k->max_iterations - k->min_iterations)) + k->min_iterations;

    // number of random numbers that will be used
    unsigned long numbers_required = get_nums_required(k, size, size_each);
    numbers_required *= 2;   // shuffle is called twice every iteration
    numbers_required += 1;   // for xor
    numbers_required *= max; // number of iterations

    // allocate required memory for random numbers
    unsigned int *random_numbers = malloc(sizeof(unsigned int) * numbers_required);
    if (random_numbers == NULL)
        return false;

    // generate all random numbers at once as we need them in the reverse order
    gen_random_numbers(k, random_numbers, numbers_required);

    unsigned long random_index = numbers_required - 1;
    for (int i = 0; i < max; i++)
    {
        unshuffle(k, data, size, size_each, random_numbers, &random_index);

        // undo the xor operation
        sub_xor(k, data, size, random_numbers, &random_index);
        unshuffle(k, data, size, size_each, random_numbers, &random_index);

        // replace each byte using key->unmap
        unmap(k, data, size);
    }

    free(random_numbers);
    k->seed = 0;
    k->set_seed = false;
    return true;
}