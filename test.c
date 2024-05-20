#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef union linkedListTypes {
    char char_t;
    short short_t;
    int int_t;
    long long_t;
    long long longlong_t;
    float float_t;
    _Bool bool_t;
    double double_t;
    void* ptr_t;

    //_Decimal32 decimal32_t;
    //_Decimal64 decimal64_t;
    //_Decimal128 decimal128_t;
} type_t;

void test(type_t a) {
    printf("0x%X\n", a);
    return;
}

int main() {
    test((type_t){ .ptr_t = -1});

    return 0;
}