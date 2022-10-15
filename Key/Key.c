/**
 * 
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

static void genchar(int *store, unsigned char *done, int i);

key generate_key()
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
    
    // generate the sequence
    for (int i = 0; i < 256; i++)
        genchar((int *)temp_key, (unsigned char *)done, i);
    
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
    rv->max_row_clmn_size = 10;
    rv->min_row_clmn_size = 3;
    return rv;
}

// randomly generates a character that has not been used before
static void genchar(int *store, unsigned char *done, int i)
{
    if (store[i] != -1) return;

    unsigned char x;
    do
    {
        getentropy(&x, 1);
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
    rv->max_row_clmn_size = 10;
    rv->min_row_clmn_size = 3;
    return rv;
}