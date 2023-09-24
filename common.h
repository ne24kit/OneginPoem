#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MY_ASSERT(cond, msg, ret, line, func, filename)  \
    do{                                                  \
        if(!cond){                                       \
            printf(msg);                                 \
            printf("FILE: %s\n", filename);              \
            printf("FUNC: %s\n", func);                  \
            printf("LINE: %d\n", line);                  \
        }                                                \
        return ret;                                      \
    } while (0)

#define MY_ASSERT_UPG(cond, msg, ret) MY_ASSERT(cond, msg, ret, __LINE__, __PRETTY_FUNCTION__, __FILE__ )

void swap(void *a, void *b, size_t size);