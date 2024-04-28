#pragma once

#include "stdtypes.h"

#include <stdlib.h>

void* memoryFill(void *dest, int val, size_t length);
void* memoryBufferFill(void* dest, void* src, size_t unitSize, uint64_t units);
void memoryCopy(void* dest, void* src, size_t size);

void memoryChangeAllocator(void* (*allocator)(size_t));
void memoryChangeDeallocator(void (*deallocator)(void*));

void* memoryAlloc(size_t size);
void memoryFree(void* block);

void* memoryClearedMalloc(size_t unitSize, uint64_t units);