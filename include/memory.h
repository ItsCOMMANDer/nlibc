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


void memcpy(void* dest, void* src, size_t size);