#ifndef MYSTD_STRING_H
#define MYSTD_STRING_H

#include "stdtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t stringLength(const char* source);
size_t stringLimitLength(const char* source, const size_t limit);
bool string_is_number(const char* source);
bool stringLimit_is_number(const char* source, const size_t limit);
bool string_isLowercase(const char* source);
bool stringLimit_isLowercase(const char* source, const size_t limit);
bool string_is_upercase(const char* source);
bool stringLimit_is_upercase(const char* source, const size_t limit);
//char* relative_substring(char* destination, const char* source, const uint64_t start, const uint64_t end);
//char* absoulute_substring(char* destination, const char* source, uint64_t start, uint64_t end);
int string_compare(const char* str1, const char* str2);
int stringLimit_compare(const char* str1, const char* str2, uint64_t limit);
char* stringLimit_toLowercase(char* destination, const char* source, uint64_t limit);
char* stringLimit_to_upercase(char* destination, const char* source, uint64_t limit);

#ifdef __cplusplus
}
#endif

#endif