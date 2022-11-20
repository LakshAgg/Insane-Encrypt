#include "InternalShuffle.h"

unsigned int calc_size_each(key k)
{
    return (gen_num(k) % (k->max_row_size - k->min_row_size + 1)) + k->min_row_size;
}

/**
 * @brief Shifts the data in row by n.
 * @param data Index of starting byte of the row
 * @param size Number of bytes in the row
 * @param n
 */
static void shuffle_row(void *data, unsigned short size, unsigned int n)
{
    n = n % size;
    if (n == 0)
        n = 1;
    char temp[n];
    memcpy(temp, data + size - n, n);
    memmove(data + n, data, size - n);
    memcpy(data, temp, n);
}

/**
 * @brief Unshifts the row by n
 * @param data Index of starting byte of the row
 * @param size Number of bytes in the row
 * @param n 
 */
static void unshuffle_row(void *data, unsigned short size, unsigned int n)
{
    n = n % size;
    if (n == 0)
        n = 1;
    char temp[n];
    memcpy(temp, data, n);
    memmove(data, data + n, size - n);
    memcpy(data + size - n, temp, n);
}

/**
 * @brief Shifts data in columns by n.
 * @param data Starting byte of the column
 * @param size Number of bytes in each row
 * @param clmns Number of rows.
 * @param n 
 */
static void shuffle_clmn(char *data, unsigned short size, unsigned long clmns, unsigned int n)
{
    n = n % clmns;
    if (n == 0)
        n = 1;
    char temp[n];
    for (int i = clmns - n, j = 0; i < clmns; i++)
        temp[j++] = data[i * size];

    for (int i = clmns - 1; i >= n; i--)
        data[i * size] = data[(i - n) * size];

    for (int i = 0; i < n; i++)
        data[i * size] = temp[i];
}


/**
 * @brief Unshifts data in columns by n.
 * @param data Starting byte of the column
 * @param size Number of bytes in each row
 * @param clmns Number of rows.
 * @param n 
 */
static void unshuffle_clmn(char *data, unsigned short size, unsigned long clmns, unsigned int n)
{
    n = n % clmns;
    if (n == 0)
        n = 1;
    char temp[n];
    for (int i = 0; i < n; i++)
        temp[i] = data[i * size];

    for (int i = 0; i < clmns - n; i++)
        data[i * size] = data[(i + n) * size];

    for (int i = clmns - n, j = 0; i < clmns; i++)
        data[i * size] = temp[j++];
}

static void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}