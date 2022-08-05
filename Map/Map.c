#include "Map.h"
#include <stdlib.h>

void map(key k, void *data, unsigned long size)
{
    if (k == NULL || data == NULL || size == 0) return;
    for (size--; ; size--)
    {
        ((unsigned char *) data)[size] = k->map[((unsigned char *) data)[size]];
        if (size == 0) break;
    }
}

void unmap(key k, void *data, unsigned long size)
{
    if (k == NULL || data == NULL || size == 0) return;
    for (size--; ; size--)
    {
        ((unsigned char *) data)[size] = k->unmap[((unsigned char *) data)[size]];
        if (size == 0) break;
    }
}