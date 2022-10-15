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

    int size_each = calc_size_each(k) % size + 1;

    // number of operations
    int max = (gen_num(k) % (k->max_iterations - k->min_iterations)) + k->min_iterations;

    unsigned long numbers_required = get_nums_required(k, size, size_each);
    numbers_required *= 2;   // shuffle is called twice every iteration
    numbers_required += 1;   // for xor
    numbers_required *= max; // number of iterations

    unsigned int *random_numbers = gen_random_numbers(k, numbers_required);
    if (random_numbers == NULL)
        return false;

    unsigned long random_index = 0;
    for (int i = 0; i < max; i++)
    {
        map(k, data, size);
        shuffle(k, data, size, size_each, random_numbers, &random_index);
        add_xor(k, data, size, random_numbers, &random_index);
        shuffle(k, data, size, size_each, random_numbers, &random_index);
    }

    free(random_numbers);
    k->seed = 0;
    k->set_seed = false;
    return true;
}

bool idecrypt(key k, void *data, unsigned long size)
{
    if (size == 0 || data == NULL || k == NULL)
        return false;

    int size_each = calc_size_each(k) % size + 1;

    int max = (gen_num(k) % (k->max_iterations - k->min_iterations)) + k->min_iterations;

    unsigned long numbers_required = get_nums_required(k, size, size_each);
    numbers_required *= 2;   // shuffle is called twice every iteration
    numbers_required += 1;   // for xor
    numbers_required *= max; // number of iterations

    unsigned int *random_numbers = gen_random_numbers(k, numbers_required);
    if (random_numbers == NULL)
        return false;

    unsigned long random_index = numbers_required - 1;
    for (int i = 0; i < max; i++)
    {
        unshuffle(k, data, size, size_each, random_numbers, &random_index);
        sub_xor(k, data, size, random_numbers, &random_index);
        unshuffle(k, data, size, size_each, random_numbers, &random_index);
        unmap(k, data, size);
    }

    free(random_numbers);
    k->seed = 0;
    k->set_seed = false;
    return true;
}