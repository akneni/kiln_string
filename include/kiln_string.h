#ifndef KILN_STRING_H
#define KILN_STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


typedef struct KilnString {
    char* ptr;
    uint64_t length;
    uint64_t capacity;
} KilnString;

typedef struct StringRef {
    char* ptr;
    uint64_t length;
} StringRef;


KilnString KilnString_from_cstr(const char* string);
KilnString KilnString_from_string_ref(const StringRef* str_ref);
__always_inline StringRef StringRef_from_kiln_str(const KilnString* string);
__always_inline StringRef StringRef_from_cstr(const char* string);
__always_inline void KilnString_free(KilnString* str);

#endif // KILN_STRING_H