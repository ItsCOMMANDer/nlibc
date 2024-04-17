#pragma once

#include "../include/stdtypes.h"


void memcpy(void* dest, void* src, size_t size) {
    for(int i = 0; i < size; i++) {
        ((char*)dest)[i]= ((char*)src)[i];
    }
}