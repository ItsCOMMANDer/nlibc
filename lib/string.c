#include "../include/string.h"

#include "../include/stdtypes.h"
#include "../include/math.h"
#include "../include/limits.h"

size_t stringLength(const char* source) {
    if(source == NULL_PTR) return 0;
    size_t length = 0;
    while(source[length] != '\0') length++;
    return length;
}

size_t stringLimitLength(const char* source, const size_t limit) {
    if(source == NULL_PTR) return 0;
    size_t length = 0;
    for(int index = 0; index < limit && source[index] != '\0'; index++) {length++;}
    return length;
}

bool is_digit(const char c) {return (c >= '0' && c <= '9');}
bool is_uppercase(const char c) {return (c >= 'A' && c <= 'Z');}
bool isLowercase(const char c) {return (c >= 'a' && c <= 'z');}

bool string_is_number(const char* source) {
    if(source == NULL_PTR) return false;
    for(size_t index = 0; source[index] != '\0'; index++) {if(!is_digit(source[index])) return false;}
    return true;
}

bool stringLimit_is_number(const char* source, const size_t limit) {
    if(source == NULL_PTR) return false;
    for(size_t index = 0; index < limit && source[index] != '\0'; index++) {if(!is_digit(source[index])) return false;}
    return true;
}

bool string_isLowercase(const char* source) {
    if(source == NULL_PTR) return false;
    for(size_t index = 0; source[index] != '\0'; index++) {if(!isLowercase(source[index]))return false;}
    return true;
}

bool stringLimit_isLowercase(const char* source, const size_t limit) {
    if(source == NULL_PTR) return false;
    for(size_t index = 0; index < limit && source[index] != '\0'; index++) {if(!isLowercase(source[index]))return false;}
    return true;
}

bool string_is_uppercase(const char* source) {
    if(source == NULL_PTR) return false;
    for(size_t index = 0; source[index] != '\0'; index++) {if(!is_uppercase(source[index]))return false;}
    return true;
}

bool stringLimit_is_uppercase(const char* source, const size_t limit) {
    if(source == NULL_PTR) return false;
    for(size_t index = 0; index < limit && source[index] != '\0'; index++) {if(!is_uppercase(source[index]))return false;}
    return true;
}

char* relative_substring(char* destination, const char* source, uint64_t start, uint64_t end) {
    if(destination == NULL_PTR || source == NULL_PTR) return NULL_PTR;
    
    uint64_t substr_start = minimum(start, stringLimitLength(source, UINT64_MAX));
    uint64_t substr_end = minimum(end, stringLimitLength(source, UINT64_MAX));
    uint64_t substringLength = substr_end - substr_start;
    
    for(uint64_t index = substr_start; index < substr_end; index++) {
        destination[index - substr_start] = source[index];
    }

    destination[substringLength] = '\0';
    
    return destination;
}

char* absolute_substring(char* destination, const char* source, uint64_t start, uint64_t end) {
    if(destination == NULL_PTR || source == NULL_PTR) return NULL_PTR;
    
    uint64_t substr_start = minimum(start, stringLimitLength(source, UINT64_MAX));
    uint64_t substr_end = minimum(end, stringLimitLength(source, UINT64_MAX));
    uint64_t substringLength = absolute(substr_end - substr_start);

    if(substr_start < substr_end) {
        for(uint64_t index = substr_start; index < substr_end; index++) {
            destination[index - substr_start] = source[index];
        }
    } else {
        for(uint64_t index = substr_end; index >= substr_start; index--) {
            destination[index - substr_start] = source[index];
        }
    }

    destination[substringLength] = '\0';
    
    return destination;
}

#define MYSTD_STRING_ISEQUAL -1

int string_compare(const char* str1, const char* str2) {
    if(str1 == NULL_PTR || str2 == NULL_PTR) return -2;
    for(uint64_t index = 0; index < max(stringLimitLength(str1, UINT64_MAX), stringLimitLength(str2, UINT64_MAX)); index++) {
        if(str1[index] == '\0' && str2[index] == '\0') return -1;
        if(str1[index] != str2[index]) return index;
    }
    return -1;
}

int stringLimit_compare(const char* str1, const char* str2, uint64_t limit) {
    if(str1 == NULL_PTR || str2 == NULL_PTR) return -2;
    for(uint64_t index = 0; index < limit; index++) {
        if(str1[index] == '\0' && str2[index] == '\0') return -1;
        if(str1[index] != str2[index]) return index;
    }
    return -1;
}

char character_to_uppercase(char c) {return is_uppercase(c) ? c : c + 32;}
char character_toLowercase(char c) {return isLowercase(c) ? c : c - 32;}

char* string_toLowercase(char* destination, const char* source) {
    for(uint64_t index = 0; index < stringLength(source); index++) {
        destination[index] = character_toLowercase(source[index]);
    }
    return destination;
}

char* string_to_uppercase(char* destination, const char* source) {
    for(uint64_t index = 0; index < stringLength(source); index++) {
        destination[index] = character_to_uppercase(source[index]);
    }
    return destination;
}

char* stringLimit_toLowercase(char* destination, const char* source, uint64_t limit) {
    for(uint64_t index = 0; index < stringLimitLength(source, limit); index++) {
        destination[index] = character_toLowercase(source[index]);
    }
    return destination;
}

char* stringLimit_to_uppercase(char* destination, const char* source, uint64_t limit) {
    for(uint64_t index = 0; index < stringLimitLength(source, limit); index++) {
        destination[index] = character_to_uppercase(source[index]);
    }
    return destination;
}

