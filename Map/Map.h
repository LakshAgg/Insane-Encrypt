/**
 * @file Map.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @version 0.1
 * @date 2022-07-30
 */
#ifndef MAP__HEADER
#define MAP__HEADER
#include "../Key/Key.h"

/**
 * @brief Maps each byte of data using the key k.
 * @param k 
 * @param data 
 * @param size 
 */
void map(key k, void *data, unsigned long size);

/**
 * @brief Retrieves the original data.
 * @param k 
 * @param data 
 * @param size 
 */
void unmap(key k, void *data, unsigned long size);
#endif