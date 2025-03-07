#ifndef KILN_STRING_H
#define KILN_STRING_H

#include <stdint.h>


typedef struct KilnString {
    char* ptr;
    uint64_t length;
    uint64_t capacity;
} KilnString;

typedef struct StringRef {
    char* ptr;
    uint64_t length;
} StringRef;



#endif // KILN_STRING_H