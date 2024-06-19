#include "../include/error.h"
#include "../include/memory.h"




static error_t error_list[DEFAULT_ERROR_LIST_SIZE];

error_t error_getLastError(void) {
    return error_list[0];
}

void error_pushError(error_t error) {
    if(error_list[DEFAULT_ERROR_LIST_SIZE].freeString != NULL) error_list[DEFAULT_ERROR_LIST_SIZE].freeString(error_list[DEFAULT_ERROR_LIST_SIZE].description);
    memory_copy(&error_list[1], &error_list[0], (DEFAULT_ERROR_LIST_SIZE - 1) * sizeof(error_t));
    error_list[0] = error;
}

uint64_t error_summary(char summary[5]) {return *((uint64_t*)summary);}

error_t error_make(uint8_t type, uint64_t summary, char* description) {
    return (error_t){
        .type = type,
        .summary = summary,
        .description = description,
    };
}