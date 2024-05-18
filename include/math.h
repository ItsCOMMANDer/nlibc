#pragma once

#include "stdtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MIN_M(x,y) (x < y ? x : y)
#define MAX_M(x,y) (x > y ? x : y)

#define ABS_M(x) (x < 0 ? -x : x)
#define SGN_M(x) (x < 0 ? -1 : x > 0 ? 1 : 0)

int64_t min(int64_t a, int64_t b);
int64_t max(int64_t a, int64_t b);
uint64_t abs(int64_t n);
int64_t power(int64_t a, int64_t b);

#ifdef __cplusplus
}
#endif