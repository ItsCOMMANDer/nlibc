#include "../include/math.h"
#include  "../include/stdtypes.h"


int64_t minimum(int64_t a, int64_t b) {return a < b ? a : b;}
int64_t maximum(int64_t a, int64_t b) {return a > b ? a : b;}

uint64_t absoulute(int64_t n) {return n < 0 ? n * -1 : n;}

int64_t power(int64_t base, int64_t exponent) {
    int64_t result = base;
    for(int i = 0; i < exponent - 1; i++) {
        result*=base;
    }
    return result;
}

int8_t sing(int64_t n) {return (n < 0 ? -1 : n > 0 ? 1 : 0);}