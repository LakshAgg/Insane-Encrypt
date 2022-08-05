#include "InternalShuffle.h"

int calc_size_each(int a, int b)
{
    int size_each = ((a + b) % MAX_ROW_CLMN_SIZE);
    if (size_each < MIN_ROW_CLMN_SIZE)
        size_each = MIN_ROW_CLMN_SIZE;
    return size_each;
}

void shuffle_row(void *data, unsigned short size, unsigned int n)
{
    n = n % size;
    if (n == 0)
        n = 1;
    char temp[n];
    memcpy(temp, data + size - n, n);
    memmove(data + n, data, size - n);
    memcpy(data, temp, n);
}

void unshuffle_row(void *data, unsigned short size, unsigned int n)
{
    n = n % size;
    if (n == 0)
        n = 1;
    char temp[n];
    memcpy(temp, data, n);
    memmove(data, data + n, size - n);
    memcpy(data + size - n, temp, n);
}

void shuffle_clmn(char *data, unsigned short size, unsigned short clmns, unsigned int n)
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

void unshuffle_clmn(char *data, unsigned short size, unsigned short clmns, unsigned int n)
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

void swap(char *x, char *y)
{
    char temp = *x;
    *x = *y;
    *y = temp;
}