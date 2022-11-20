/**
 * @file Key.c
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @version 0.1
 * @date 2022-07-30
 */
#include <stdio.h>
#include "Key.h"
#include <stdlib.h>
#include <time.h>
#include <sys/random.h>

static void genchar(int *store, unsigned char *done, int i, unsigned char k());
static unsigned char get_random();

key generate_key(unsigned char random_number_gen())
{
    // allocate the memory required
    key rv = malloc(sizeof(struct s_key));
    if (rv == NULL) return NULL;

    // characters already included
    unsigned char done[256];
    int temp_key[256];

    // initialize variables
    for (int i = 0; i < 256; i++)
    {
        done[i] = 0;
        temp_key[i] = -1;
    }

    if (!random_number_gen)
        random_number_gen = get_random;

    // generate the sequence
    for (int i = 0; i < 256; i++)
        genchar((int *)temp_key, (unsigned char *)done, i, random_number_gen);
    
    // copy to the key
    for (int i = 0; i < 256; i++)
    {
        rv->map[i] = temp_key[i];
        rv->unmap[temp_key[i]] = i;
    }

    rv->seed = 0;
    rv->set_seed = false;

    // set default values
    rv->max_iterations = 9;
    rv->min_iterations = 3;
    rv->max_row_size = 10;
    rv->min_row_size = 3;
    return rv;
}

// randomly generates a character that has not been used before
static void genchar(int *store, unsigned char *done, int i, unsigned char k())
{
    if (store[i] != -1) return;

    unsigned char x;
    do
    {
        x = k();
        x = x % 256;
    } while (done[x]);

    store[i] = x;
    done[x] = 1;
}

void *get_key(key k)
{
    if (k == NULL) return NULL;

    // allocate required memory
    char *rv = malloc(256);
    if (rv == NULL) return NULL;

    // copy the key
    for (int i = 0; i < 256; i++)
        rv[i] = k->map[i];
    return rv;
}

key load_key(void *k)
{
    if (k == NULL) return NULL;

    // allocate the key
    key rv = malloc(sizeof(struct s_key));
    if (rv == NULL) return NULL;

    // load the key
    for (int i = 0; i < 256; i++)
    {
        rv->map[i] = ((unsigned char *)k)[i];
        rv->unmap[((unsigned char *) k)[i]] = i;
    }

    rv->seed = 0;
    rv->set_seed = false;

    // set default values
    rv->max_iterations = 9;
    rv->min_iterations = 3;
    rv->max_row_size = 10;
    rv->min_row_size = 3;
    return rv;
}

bool verify_key(key k)
{
    if (k->min_iterations == 0 || k->max_iterations == 0 || k->min_row_size == 0 || k->max_row_size == 0)
        return false;
    if (k->min_iterations == k->max_iterations || k->min_row_size == k->max_row_size)
        return false;

    char done[256];
    for (int i = 0; i < 256; i++)
        done[i] = 0;
    for (int i = 0; i < 256; i++)
    {
        if (done[i] || k->unmap[k->map[i]] != i)
            return false;
        done[i] = true;
    }
    for (int i = 0; i < 256; i++)
        if (done[i] != 1)
            return false;
    return true;
}

static unsigned char get_random()
{
    unsigned char x;
    getentropy(&x, 1);
    return x;
}