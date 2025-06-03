#ifndef KILN_STRING_H
#define KILN_STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct {
    char* ptr;
    uint64_t __length;
    uint64_t __capacity;
} kiln_string_t;


// Reference is *not* guarenteed to be null terminated
typedef struct {
    char* ptr;
    uint64_t __length;
} kstring_ref_t;


kiln_string_t KilnString_from_cstr(const char* string);
extern inline kiln_string_t KilnString_from_string_ref(kstring_ref_t str_ref);
extern inline kiln_string_t StringRef_to_kiln_string(kstring_ref_t str_ref);
extern inline kstring_ref_t KilnString_as_stringref(const kiln_string_t* string);
extern inline kstring_ref_t StringRef_from_kiln_str(const kiln_string_t* string);
extern inline kstring_ref_t StringRef_from_cstr(const char* string);
extern inline void KilnString_free(kiln_string_t* str);
extern inline void KilnString_push_cstr(kiln_string_t* string, const char* cstr);
void KilnString_push_stringref(kiln_string_t* string, kstring_ref_t str_ref);
bool KilnString_ends_with(const kiln_string_t* string, const char* suffix);
bool KilnString_starts_with(const kiln_string_t* string, const char* prefix);
bool StringRef_ends_with(kstring_ref_t string, const char* suffix);
bool StringRef_starts_with(kstring_ref_t string, const char* prefix);
kstring_ref_t StringRef_substring(kstring_ref_t string, int64_t start_idx, int64_t end_idx);
extern inline kstring_ref_t KilnString_substring(const kiln_string_t* string, int64_t start_idx, int64_t end_idx);
extern inline bool StringRef_equals_cstr(kstring_ref_t string, const char* other);
extern inline bool StringRef_equals(kstring_ref_t s1, kstring_ref_t s2);
extern inline bool KilnString_equals_cstr(const kiln_string_t* string, const char* other);
extern inline bool KilnString_equals(const kiln_string_t* s1, const kiln_string_t* s2);
int32_t StringRef_compare(kstring_ref_t s1, kstring_ref_t s2);
extern inline int32_t KilnString_compare(const kiln_string_t* s1, const kiln_string_t* s2);
void KilnString_to_ascii_lower(kiln_string_t* string);
void KilnString_to_ascii_upper(kiln_string_t* string);
void KilnString_to_unicode_upper(kiln_string_t* string);
void KilnString_to_unicode_lower(kiln_string_t* string);
void KilnString_trim_inplace(kiln_string_t* string);
kstring_ref_t StringRef_trim(kstring_ref_t string);
kstring_ref_t KilnString_trim(const kiln_string_t* string);
void KilnString_replace(kiln_string_t* string, const char* old_s, const char* new_s);
int64_t StringRef_find(kstring_ref_t string, const char* target);
int64_t StringRef_rfind(kstring_ref_t string, const char* target);
extern inline int64_t KilnString_find(const kiln_string_t* string, const char* target);
extern inline int64_t KilnString_rfind(const kiln_string_t* string, const char* target);
void StringRef_partition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]);
void StringRef_rpartition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]);
extern inline void KilnString_partition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]);
extern inline void KilnString_rpartition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]);

#endif // KILN_STRING_H