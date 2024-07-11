#pragma once

#include <nlibc/stdtypes.h>

void* memory_fill(void *dest, int val, size_t length);
void* memory_bufferFill(void* dest, void* src, size_t unitSize, uint64_t units);
void memory_copy(void* dest, void* src, size_t size);