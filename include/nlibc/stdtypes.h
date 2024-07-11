#ifndef NLIBC_TYPES_H
#define NLIBC_TYPES_H

typedef long long int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

typedef unsigned long long uint64_t;
typedef int short uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202000L)
typedef _Decimal128 float128_t;
typedef _Decimal64 float64_t;
typedef _Decimal32 float32_t;
#endif

 
/*
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) c99
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) c11
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 202203L) c23
*/



#define bool _Bool

#define true 1
#define false 0


#define NULL 0
#define NULL_PTR (void*)0

typedef unsigned long long size_t;

#endif