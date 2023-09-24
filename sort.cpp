#include "sort.h"

void sort(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *))
{
    MY_ASSERT(data, "Zero pointer to sorted array\n");
    MY_ASSERT((left <= right), "Incorrectly passed the sorting limits\n");
    MY_ASSERT(size, "Array size must be non-zero\n");
    MY_ASSERT(comp, "Pointer to comparator zero\n");

    sort_data(data, left, right, size, comp);
}

size_t Partition(void *data, size_t left, size_t right, size_t size,
                 int (*comp)(const void *, const void *))
{
    void * mid_elem = calloc(size, sizeof(char));
    memcpy(mid_elem, (char *)data + ((left + right) / 2) * size, size);

    while(true){
        while(comp(POINTER_ELEM(data, left, size), mid_elem) < 0){
            left++;
        }

        while(comp(mid_elem, POINTER_ELEM(data, right, size)) < 0){
            right--;
        }

        if (left >= right){
            free(mid_elem);
            return right;
        }

        swap(POINTER_ELEM(data, left, size), POINTER_ELEM(data, right, size), size);
        left++;
        right--;    
    }
}

void sort_data(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *))
{
    if (left + 1 == right){
        if (comp(POINTER_ELEM(data, right, size), POINTER_ELEM(data, left, size)) < 0){
            swap(POINTER_ELEM(data, left, size), POINTER_ELEM(data, right, size), size);
        }
        return;
    }

    if (left < right){
        size_t mid = Partition(data, left, right, size, comp);
        sort_data(data, left, mid, size, comp);
        sort_data(data, mid + 1, right, size, comp);
    }
}