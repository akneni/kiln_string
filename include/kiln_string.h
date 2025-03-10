#ifndef KILN_STRING_H
#define KILN_STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


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
KilnString KilnString_from_string_ref(StringRef str_ref);
__always_inline StringRef KilnString_as_stringref(const KilnString* string);
__always_inline StringRef StringRef_from_kiln_str(const KilnString* string);
__always_inline StringRef StringRef_from_cstr(const char* string);
__always_inline void KilnString_free(KilnString* str);
__always_inline void KilnString_push_cstr(KilnString* string, const char* cstr);
void KilnString_push_stringref(KilnString* string, StringRef str_ref);
bool KilnString_ends_with(const KilnString* string, const char* suffix);
bool KilnString_starts_with(const KilnString* string, const char* prefix);
bool StringRef_ends_with(StringRef string, const char* suffix);
bool StringRef_starts_with(StringRef string, const char* prefix);
void KilnString_to_ascii_lower(KilnString* string);
void KilnString_to_ascii_upper(KilnString* string);
void KilnString_to_unicode_upper(KilnString* string);
void KilnString_to_unicode_lower(KilnString* string);
StringRef KilnString_split_next(const KilnString* string, const char* delimiter, uint64_t start_idx);
StringRef StringRef_split_next(StringRef string, const char* delimiter, uint64_t start_idx);
StringRef StringRef_partition_left(StringRef string, const char* delimiter);
StringRef StringRef_partition_right(StringRef string, const char* delimiter);
StringRef StringRef_rpartition_left(StringRef string, const char* delimiter);
StringRef StringRef_rpartition_right(StringRef string, const char* delimiter);
__always_inline StringRef KilnString_partition_left(const KilnString* string, const char* delimiter);
__always_inline StringRef KilnString_partition_right(const KilnString* string, const char* delimiter);
__always_inline StringRef KilnString_rpartition_left(const KilnString* string, const char* delimiter);
__always_inline StringRef KilnString_rpartition_right(const KilnString* string, const char* delimiter);

#endif // KILN_STRING_H