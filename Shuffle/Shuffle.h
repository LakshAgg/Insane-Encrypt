/**
 * @file Shuffle.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @version 0.1
 * @date 2022-07-30
 */
#ifndef SHUFFLE_HEADER
#define SHUFFLE_HEADER
#include "../Key/Key.h"

/**
 * @brief Shuffles data using the key k.
 * @param k 
 * @param data 
 * @param size 
 * @param size_each
 * @param random_nums
 * @param r_index
 */
void shuffle(key k, void *data, unsigned long size, int size_each, unsigned int *random_nums, unsigned long *r_index);

/**
 * @brief Undoes the effect of shuffle using the key k.
 * @param k 
 * @param data 
 * @param size 
 * @param size_each
 * @param random_nums
 * @param r_index
 */
void unshuffle(key k, void *data, unsigned long size, int size_each, unsigned int *random_nums, unsigned long *r_index);
#endif