/******************************************************************
 * @file HotakusMemUtil.c
 * @author Hotakus (...)
 * @email ttowfive@gmail.com
 * @brief ...
 * @version 1.0
 * @date 2021/10/8 4:57
 * @copyright Copyright (c) 2021/10/8
*******************************************************************/
#include "HotakusMemUtil.h"

static uint32_t alloc_size = 0;

void* hotakusAlloc(size_t size)
{
    return heap_caps_calloc(1, size, MALLOC_CAP_SPIRAM);
}

void* hotakusRealloc(void* ptr, size_t size)
{
    return heap_caps_realloc(ptr, size, MALLOC_CAP_SPIRAM);
}

void hotakusFree(void* ptr)
{
    heap_caps_free(ptr);
}
