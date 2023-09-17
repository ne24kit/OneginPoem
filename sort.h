#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void Sort(void *data, size_t left, size_t right, size_t size, int (*comp)(const void *, const void *));
size_t Partition(void *data, size_t left, size_t right, size_t size, int (*comp)(const void *, const void *));


void swap(void *a, void *b, size_t size);
