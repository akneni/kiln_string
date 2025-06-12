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


kiln_string_t kiln_string_from_cstr(const char* string);
extern inline kiln_string_t kiln_string_from_string_ref(kstring_ref_t str_ref);
extern inline kiln_string_t kstring_ref_to_kiln_string(kstring_ref_t str_ref);
extern inline kstring_ref_t kiln_string_as_stringref(const kiln_string_t* string);
extern inline kstring_ref_t kstring_ref_from_kiln_str(const kiln_string_t* string);
extern inline kstring_ref_t kstring_ref_from_cstr(const char* string);
extern inline void kiln_string_free(kiln_string_t* str);
extern inline void kiln_string_push_cstr(kiln_string_t* string, const char* cstr);
void kiln_string_push_stringref(kiln_string_t* string, kstring_ref_t str_ref);
bool kiln_string_ends_with(const kiln_string_t* string, const char* suffix);
bool kiln_string_starts_with(const kiln_string_t* string, const char* prefix);
bool kstring_ref_ends_with(kstring_ref_t string, const char* suffix);
bool kstring_ref_starts_with(kstring_ref_t string, const char* prefix);
kstring_ref_t kstring_ref_substring(kstring_ref_t string, int64_t start_idx, int64_t end_idx);
extern inline kstring_ref_t kiln_string_substring(const kiln_string_t* string, int64_t start_idx, int64_t end_idx);
extern inline bool kstring_ref_equals_cstr(kstring_ref_t string, const char* other);
extern inline bool kstring_ref_equals(kstring_ref_t s1, kstring_ref_t s2);
extern inline bool kiln_string_equals_cstr(const kiln_string_t* string, const char* other);
extern inline bool kiln_string_equals(const kiln_string_t* s1, const kiln_string_t* s2);
int32_t kstring_ref_compare(kstring_ref_t s1, kstring_ref_t s2);
extern inline int32_t kiln_string_compare(const kiln_string_t* s1, const kiln_string_t* s2);
void kiln_string_to_ascii_lower(kiln_string_t* string);
void kiln_string_to_ascii_upper(kiln_string_t* string);
void kiln_string_to_unicode_upper(kiln_string_t* string);
void kiln_string_to_unicode_lower(kiln_string_t* string);
void kiln_string_trim_inplace(kiln_string_t* string);
kstring_ref_t kstring_ref_trim(kstring_ref_t string);
kstring_ref_t kiln_string_trim(const kiln_string_t* string);
void kiln_string_replace(kiln_string_t* string, const char* old_s, const char* new_s);
int64_t kstring_ref_find(kstring_ref_t string, const char* target);
int64_t kstring_ref_rfind(kstring_ref_t string, const char* target);
extern inline int64_t kiln_string_find(const kiln_string_t* string, const char* target);
extern inline int64_t kiln_string_rfind(const kiln_string_t* string, const char* target);
void kstring_ref_partition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]);
void kstring_ref_rpartition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]);
extern inline void kiln_string_partition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]);
extern inline void kiln_string_rpartition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]);

#endif // KILN_STRING_H