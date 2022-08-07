/**
 * @file XOR_etc.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @version 0.1
 * @date 2022-07-31
 */
#ifndef XOR_etc_HEADER
#define XOR_etc_HEADER
#include "../Key/Key.h"

/**
 * @param k 
 * @param data 
 * @param size 
 * @param random_nums
 * @param random_index
 */
void add_xor(key k, void *data, unsigned size, unsigned int *random_nums, unsigned long *random_index);

/**
 * @param k 
 * @param data 
 * @param size 
 * @param random_nums
 * @param random_index
 */
void sub_xor(key k, void *data, unsigned size, unsigned int *random_nums, unsigned long *random_index);
#endif