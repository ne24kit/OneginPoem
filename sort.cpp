#include "sort.h"
#include "text.h"

void swap(void *a, void *b, size_t size)
{
    void **temp = (void **)calloc(size, sizeof(char));
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}


size_t Partition(void *data, size_t left, size_t right, size_t size, int (*comp)(const void *, const void *))
{
    void ** mid_elem = (void **)calloc(size, sizeof(char));
    memcpy(mid_elem, (char *)data + ((left + right) / 2) * size, size);
       
    
    while(true){
        while(comp((char *)data + left * size, mid_elem) < 0){
            left++;
        }

        while(comp(mid_elem, (char *)data + right * size) < 0){
            right--;
        }

        if (left >= right){
            free(mid_elem);
            return right;
        }
            

        swap((char *)data + left * size, (char *)data + right * size, size);
        left++;
        right--;
    }
    

}

void Sort(void *data, size_t left, size_t right, size_t size, int (*comp)(const void *, const void *))
{
    if (left + 1 == right){
        if (comp((char *) data + right * size, (char *) data + left * size) < 0){
            swap((char *) data + left * size, (char *) data + right * size, size);
        }
        return;
    }

    if (left < right){
        size_t mid = Partition(data, left, right, size, comp);
        Sort(data, left, mid, size, comp);
        Sort(data, mid + 1, right, size, comp);
    }
}