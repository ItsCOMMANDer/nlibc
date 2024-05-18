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

void memoryChangeAllocator(void* (*allocator)(size_t)) {g_mem_allocConfig.mem_alloc = allocator;}
void memoryChangeDeallocator(void (*deallocator)(void*)) {g_mem_allocConfig.mem_free = deallocator;}

void* memoryAlloc(size_t size) {return g_mem_allocConfig.mem_alloc(size);}
void memoryFree(void* block) {g_mem_allocConfig.mem_free(block);}

void* memoryClearedMalloc(size_t unitSize, uint64_t units) {
    void* ptr = memoryAlloc(unitSize * units);
    if(ptr == NULL_PTR) return NULL_PTR;
    memoryFill(ptr, 0, units*unitSize);
    return ptr;
}