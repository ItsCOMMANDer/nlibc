#pragma once

#include "stdtypes.h"

#include <stdlib.h>

struct {
    void* (*mem_alloc)(size_t);
    void (*mem_free)(void*);
} g_mem_allocConfig = {
    malloc,
    free
};

void* memoryFill(void *dest, int val, size_t length);
void* memoryBufferFill(void* dest, void* src, size_t unitSize, uint64_t units);
void memoryCopy(void* dest, void* src, size_t size);
void* memoryClearedMalloc(size_t unitSize, uint64_t units);