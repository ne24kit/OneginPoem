#pragma once

#include "common.h"
#include <stdio.h>
#include <stdlib.h>


#define POINTER_ELEM(data, index, size) ((char *)(data) + (index) * (size))

void sort(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *));

void sort_data(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *));
size_t Partition(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *));
