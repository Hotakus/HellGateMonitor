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
#include <Arduino.h>

using namespace HgmApplication;

HotakusMem::HotakusMem()
{
}

HotakusMem::~HotakusMem()
{
}

void* HotakusMem::alloc(size_t size)
{
	return heap_caps_calloc(1, size, MALLOC_CAP_SPIRAM);
}

void* HotakusMem::realloc(void* ptr, size_t size)
{
	return heap_caps_realloc(ptr, size, MALLOC_CAP_SPIRAM);
}

void HotakusMem::free(void* ptr)
{
	heap_caps_free(ptr);
}

