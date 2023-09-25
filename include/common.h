#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MY_ASSERT(cond, msg)                             \
    do{                                                  \
        if(!cond){                                       \
            printf(msg);                                 \
            printf("FILE: %s\n", __FILE__);              \
            printf("FUNC: %s\n", __PRETTY_FUNCTION__);   \
            printf("LINE: %d\n", __LINE__);              \
            exit(0);                                     \
        }                                                \
    } while (0)

void swap(void *a, void *b, size_t size);