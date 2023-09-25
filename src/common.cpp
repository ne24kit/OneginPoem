#include "common.h"

void swap(void *a, void *b, size_t size)
{
    MY_ASSERT(a, "Pointer to variable 'a' is NULL");
    MY_ASSERT(b, "Pointer to variable 'b' is NULL");

    void *temp = calloc(size, sizeof(char));
    
    MY_ASSERT(temp, "Pointer to variable 'temp' is NULL");
    
    memmove(temp, a, size);
    memmove(a, b, size);
    memmove(b, temp, size);
    free(temp);
}