#pragma once

#include "../include/stdtypes.h"
#include "../include/memory.h"

void* memoryFill(void *dest, int val, size_t length) {
  char *ptr = (char*)dest;
  while (length-- > 0) {*ptr++ = val;}
  return dest;
}

void* memoryBufferFill(void* dest, void* src, size_t unitSize, uint64_t units) {
    char* dest_ptr = (char*)dest;
    char* src_ptr = (char*)src;
    for(uint64_t index = 0; index < unitSize*units; index++) {
        *dest_ptr++ = src_ptr[index % unitSize];
    }
    return dest_ptr;
}

void memoryCopy(void* dest, void* src, size_t size) {
    for(int i = 0; i < size; i++) {
        ((char*)dest)[i]= ((char*)src)[i];
    }
}

void* memoryClearedMalloc(size_t unitSize, uint64_t units) {
    void* ptr = g_mem_allocConfig.mem_alloc(unitSize * units);
    memoryFill(ptr, 0, units*unitSize);
    return ptr;
}