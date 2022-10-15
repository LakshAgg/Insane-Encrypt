/**
 * @file InternalShuffle.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @brief Contains some helper functions for Shuffle.c
 * @version 0.1
 * @date 2022-08-04
 */

#ifndef INTERNAL_SHUFFLE_HEADER
#define INTERNAL_SHUFFLE_HEADER
#include "../NumGen/NumGen.h"
#include "../Encrypt.h"
#include "Shuffle.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Generates the size for each row and columns
 * @param a
 * @param b
 * @return int 
 */
int calc_size_each(key k);
#endif