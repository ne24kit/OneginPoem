#include "sort.h"

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

        if (left >= right)
            return right;
            

        swap(POINTER_ELEM(data, left, size), POINTER_ELEM(data, right, size), size);
        left++;
        right--;    
    }
    

}

void Sort(void *data, size_t left, size_t right, size_t size, 
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
        Sort(data, left, mid, size, comp);
        Sort(data, mid + 1, right, size, comp);
    }
}