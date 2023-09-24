#pragma once

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define POINTER_ELEM(data, index, size) ((char *)(data) + (index) * (size))

void Sort(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *));
size_t Partition(void *data, size_t left, size_t right, size_t size, 
            int (*comp)(const void *, const void *));
