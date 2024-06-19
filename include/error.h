#ifndef NLIBC_ERROR_H
#define NLIBC_ERROR_H

#include "../include/stdtypes.h"

#define DEFAULT_ERROR_LIST_SIZE 512

typedef struct nlibc_error {
    uint8_t type;           // error type
    uint64_t summary;       // error summary

    char* description;// string to a description
    void (*freeString)(void*); // function to free string if needed
} error_t;

enum error_types {
    ERROR_MEMORY_ALlOC_FAILED = 0,
};

char error_descriptions[32][225] = {
    "Memory allocation failed",
};

error_t error_getLastError(void);
uint64_t error_summary(char summary[5]);

error_t error_make(uint8_t type, uint64_t summary, char* description);

#endif