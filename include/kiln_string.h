#ifndef KILN_STRING_H
#define KILN_STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct KilnString {
    char* ptr;
    uint64_t __length;
    uint64_t __capacity;
} KilnString;

typedef struct StringRef {
    char* ptr;
    uint64_t __length;
} StringRef;


KilnString KilnString_from_cstr(const char* string);
extern inline KilnString KilnString_from_string_ref(StringRef str_ref);
extern inline KilnString StringRef_to_kiln_string(StringRef str_ref);
extern inline StringRef KilnString_as_stringref(const KilnString* string);
extern inline StringRef StringRef_from_kiln_str(const KilnString* string);
extern inline StringRef StringRef_from_cstr(const char* string);
extern inline void KilnString_free(KilnString* str);
extern inline void KilnString_push_cstr(KilnString* string, const char* cstr);
void KilnString_push_stringref(KilnString* string, StringRef str_ref);
bool KilnString_ends_with(const KilnString* string, const char* suffix);
bool KilnString_starts_with(const KilnString* string, const char* prefix);
bool StringRef_ends_with(StringRef string, const char* suffix);
bool StringRef_starts_with(StringRef string, const char* prefix);
StringRef StringRef_substring(StringRef string, int64_t start_idx, int64_t end_idx);
extern inline StringRef KilnString_substring(const KilnString* string, int64_t start_idx, int64_t end_idx);
extern inline bool StringRef_equals_cstr(StringRef string, const char* other);
extern inline bool StringRef_equals(StringRef s1, StringRef s2);
extern inline bool KilnString_equals_cstr(const KilnString* string, const char* other);
extern inline bool KilnString_equals(const KilnString* s1, const KilnString* s2);
int32_t StringRef_compare(StringRef s1, StringRef s2);
extern inline int32_t KilnString_compare(const KilnString* s1, const KilnString* s2);
void KilnString_to_ascii_lower(KilnString* string);
void KilnString_to_ascii_upper(KilnString* string);
void KilnString_to_unicode_upper(KilnString* string);
void KilnString_to_unicode_lower(KilnString* string);
void KilnString_trim_inplace(KilnString* string);
StringRef StringRef_trim(StringRef string);
StringRef KilnString_trim(const KilnString* string);
void KilnString_replace(KilnString* string, const char* old_s, const char* new_s);
int64_t StringRef_find(StringRef string, const char* target);
int64_t StringRef_rfind(StringRef string, const char* target);
extern inline int64_t KilnString_find(const KilnString* string, const char* target);
extern inline int64_t KilnString_rfind(const KilnString* string, const char* target);
void StringRef_partition(StringRef string, const char* delimiter, StringRef output_buffer[2]);
void StringRef_rpartition(StringRef string, const char* delimiter, StringRef output_buffer[2]);
extern inline void KilnString_partition(const KilnString* string, const char* delimiter, StringRef output_buffer[2]);
extern inline void KilnString_rpartition(const KilnString* string, const char* delimiter, StringRef output_buffer[2]);

#endif // KILN_STRING_H