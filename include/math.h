#ifndef MYSTD_MATH_H
#define MYSTD_MATH_H

#include "stdtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MIN_M(x,y) (x < y ? x : y)
#define MAX_M(x,y) (x > y ? x : y)

#define ABS_M(x) (x < 0 ? -x : x)
#define SGN_M(x) (x < 0 ? -1 : x > 0 ? 1 : 0)

int64_t minimum(int64_t a, int64_t b);
int64_t maximum(int64_t a, int64_t b);
uint64_t absoulute(int64_t n);
int64_t power(int64_t a, int64_t b);

#ifdef __cplusplus
}
#endif

#endif