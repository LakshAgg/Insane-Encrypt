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
 */
void add_xor(key k, void *data, unsigned size);

/**
 * @param k 
 * @param data 
 * @param size 
 */
void sub_xor(key k, void *data, unsigned size);
#endif