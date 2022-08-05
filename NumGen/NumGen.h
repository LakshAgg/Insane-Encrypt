/**
 * @file NumGen.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @version 0.1
 * @date 2022-08-01
 */
#ifndef NUM_GEN_HEADER
#define NUM_GEN_HEADER
#include "../Key/Key.h"

/**
 * @brief Generates a random number dependent on key k.
 * @param k 
 * @return int 
 */
int gen_num(key k);

/**
 * @brief Get the number of random numbers required.
 * @param k 
 * @param size 
 * @param size_each 
 * @return unsigned long 
 */
unsigned long get_nums_required(key k, unsigned long size, int size_each);

/**
 * @brief Generates the random numbers.
 * @param k 
 * @param count 
 * @return unsigned int* | to be freed by using free() from stdlib.h
 */
unsigned int *gen_random_numbers(key k, unsigned long count);
#endif