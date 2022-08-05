/**
 * @file InternalShuffle.h
 * @author Laksh Aggarwal (aggarwallaksh54@gmail.com)
 * @brief Contains some helper functions for Shuffle.c
 * @version 0.1
 * @date 2022-08-04
 */

#ifndef INTERNAL_SHUFFLE_HEADER
#define INTERNAL_SHUFFLE_HEADER
#include "Shuffle.h"
#include "../Encrypt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Generates the size for each row and columns
 * @param a
 * @param b
 * @return int 
 */
int calc_size_each(int a, int b);

/**
 * @brief Swaps the bytes at the given addresses
 * @param x 
 * @param y 
 */
void swap(char *x, char *y);

void shuffle_row(void *data, unsigned short size, unsigned int n);

void unshuffle_row(void *data, unsigned short size, unsigned int n);

void shuffle_clmn(char *data, unsigned short size, unsigned short clmns, unsigned int n);

void unshuffle_clmn(char *data, unsigned short size, unsigned short clmns, unsigned int n);

#endif