#pragma once

#include "../include/stdtypes.h"
#include "../include/memory.h"

static struct {
    void* (*mem_alloc)(size_t);
    void (*mem_free)(void*);
} g_mem_allocConfig = {
    malloc,
    free
};

void* memory_fill(void *dest, int val, size_t length) {
  char *ptr = (char*)dest;
  while (length-- > 0) {*ptr++ = val;}
  return dest;
}

void* memory_bufferFill(void* dest, void* src, size_t unitSize, uint64_t units) {
    char* dest_ptr = (char*)dest;
    char* src_ptr = (char*)src;
    for(uint64_t index = 0; index < unitSize*units; index++) {
        *dest_ptr++ = src_ptr[index % unitSize];
    }
    return dest_ptr;
}

void memory_copy(void* dest, void* src, size_t size) {
    for(int i = 0; i < size; i++) {
        ((char*)dest)[i]= ((char*)src)[i];
    }
}