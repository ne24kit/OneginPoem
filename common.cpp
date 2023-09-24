#include "common.h"

void swap(void *a, void *b, size_t size)
{
    void **temp = (void **)calloc(size, sizeof(char));
    memmove(temp, a, size);
    memmove(a, b, size);
    memmove(b, temp, size);
    free(temp);
}