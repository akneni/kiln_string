#ifndef KILN_STRING_H
#define KILN_STRING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>


typedef struct {
    char* ptr;
    uint64_t __length;
    size_t __capacity;
} kiln_string_t;

// Reference is not guarenteed to be null terminated
typedef struct {
    char* ptr;
    uint64_t __length;
} kstring_ref_t;


/// @brief Copies the data from string to it's own internal buffer
/// @param string 
/// @return 
kiln_string_t kiln_string_from_cstr(const char* string);

/// @brief Creates a string from a kstring_ref_t by compying the contents. 
/// @param str_ref 
/// @return 
extern inline kiln_string_t kiln_string_from_kstring_ref(kstring_ref_t str_ref);

/// @brief Creates a string with capacity `capacity`
/// @param capacity 
/// @return 
kiln_string_t kiln_string_with_capacity(size_t capacity);

/// @brief Creates a string from a kstring_ref_t by compying the contents. 
/// @param str_ref 
/// @return 
extern inline kiln_string_t kstring_ref_to_kiln_string(kstring_ref_t str_ref);

extern inline kstring_ref_t kiln_string_to_kstring_ref(const kiln_string_t* string);

extern inline kstring_ref_t kstring_ref_from_kiln_string(const kiln_string_t* string);

extern inline kstring_ref_t kstring_ref_from_cstr(char* string);

/// @brief Frees the memory allocated by the kiln string. Sets the pointer to NULL
/// @param str 
/// @return 
extern inline void kiln_string_free(kiln_string_t* str);

/// @brief Appends the content of a char* to a KilnString
/// @param string 
/// @param cstr 
extern inline void kiln_string_push_cstr(kiln_string_t* string, char* cstr);

/// @brief Appends the content of a kstring_ref_t to a KilnString
/// @param string The kiln_string_t to append to
/// @param str_ref The kstring_ref_t to append
void kiln_string_push_kstring_ref(kiln_string_t* string, kstring_ref_t str_ref);

/// @brief Checks if a kiln_string_t ends with the specified suffix
/// @param string The string to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool kiln_string_ends_with(const kiln_string_t* string, const char* suffix);

/// @brief Checks if a kiln_string_t starts with the specified prefix
/// @param string The string to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool kiln_string_starts_with(const kiln_string_t* string, const char* prefix);

/// @brief Checks if a kstring_ref_t ends with the specified suffix
/// @param string The string reference to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool kstring_ref_ends_with(kstring_ref_t string, const char* suffix);

/// @brief Checks if a kstring_ref_t starts with the specified prefix
/// @param string The string reference to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool kstring_ref_starts_with(kstring_ref_t string, const char* prefix);

/// @brief Removes the specified suffix from the string if it has the suffix, does nothing if otherwise
/// @param string 
/// @param suffix 
/// @return true if the suffix was found and removed, false if the suffix wasn't found
bool kiln_string_remove_suffix(kiln_string_t* string, kstring_ref_t suffix);

/// @brief Removes the specified prefix from the string if it has the prefix, does nothing if otherwise
/// @param string 
/// @param prefix 
/// @return true if the prefix was found and removed, false if the prefix wasn't found
bool kiln_string_remove_prefix(kiln_string_t* string, kstring_ref_t prefix);

/// @brief Gets a substring from the string passed
/// @param string The source kstring_ref_t to extract substring from
/// @param start_idx -1 to default to the start (or 0)
/// @param end_idx  -1 to default to the end
/// @return A kstring_ref_t pointing to the requested substring
kstring_ref_t kstring_ref_substring(kstring_ref_t string, int64_t start_idx, int64_t end_idx);

/// @brief Gets a substring from the KilnString
/// @param string The kiln_string_t to extract substring from
/// @param start_idx -1 to default to the start (or 0)
/// @param end_idx -1 to default to the end
/// @return A kstring_ref_t pointing to the requested substring
extern inline kstring_ref_t kiln_string_substring(const kiln_string_t* string, int64_t start_idx, int64_t end_idx);

/// @brief Checks if a kstring_ref_t equals a C-style string
/// @param string The kstring_ref_t to compare
/// @param other The C-style string to compare against
/// @return true if the strings are equal, false otherwise
extern inline bool kstring_ref_equals_cstr(kstring_ref_t string, const char* other);

/// @brief Checks if a kstring_ref_t equals kiln_string_t
/// @param string The kstring_ref_t to compare
/// @param other The kiln string to compare against
/// @return true if the strings are equal, false otherwise
extern inline bool kstring_ref_equals_kiln_string(kstring_ref_t string, const kiln_string_t* other);

/// @brief Checks if two StringRefs are equal
/// @param s1 The first kstring_ref_t to compare
/// @param s2 The second kstring_ref_t to compare
/// @return true if the strings are equal, false otherwise
extern inline bool kstring_ref_equals(kstring_ref_t s1, kstring_ref_t s2);

/// @brief Checks if a kiln_string_t equals a C-style string
/// @param string The kiln_string_t to compare
/// @param other The C-style string to compare against
/// @return true if the strings are equal, false otherwise
extern inline bool kiln_string_equals_cstr(const kiln_string_t* string, const char* other);

extern inline bool kiln_string_equals_kstring_ref(const kiln_string_t* string, kstring_ref_t other);

/// @brief Checks if two KilnStrings are equalg
/// @param s1 The first kiln_string_t to compare
/// @param s2 The first kiln_string_t to compare
/// @return true if the strings are equal, false otherwise
extern inline bool kiln_string_equals(const kiln_string_t* s1, const kiln_string_t* s2);

/// @brief Compares two StringRefs lexicographically
/// @param s1 First kstring_ref_t to compare
/// @param s2 Second kstring_ref_t to compare
/// @return 0 if equal, negative if s1 < s2, positive if s1 > s2
int32_t kstring_ref_compare(kstring_ref_t s1, kstring_ref_t s2);

/// @brief Compares two KilnStrings lexicographically
/// @param s1 First kiln_string_t to compare
/// @param s2 Second kiln_string_t to compare
/// @return 0 if equal, negative if s1 < s2, positive if s1 > s2
extern inline int32_t kiln_string_compare(const kiln_string_t* s1, const kiln_string_t* s2);

/// @brief Converts ASCII characters in a kiln_string_t to lowercase, ignoring non-ASCII characters
/// @param string The kiln_string_t to convert
void kiln_string_to_ascii_lower(kiln_string_t* string);

/// @brief Converts ASCII characters in a kiln_string_t to uppercase, ignoring non-ASCII characters
/// @param string The kiln_string_t to convert
void kiln_string_to_ascii_upper(kiln_string_t* string);

/// @brief Converts a kiln_string_t to uppercase, handling both ASCII and basic Unicode
/// @param string The kiln_string_t to convert to uppercase
void kiln_string_to_unicode_upper(kiln_string_t* string);

/// @brief Converts a kiln_string_t to lowercase, handling both ASCII and basic Unicode
/// @param string The kiln_string_t to convert to lowercase
void kiln_string_to_unicode_lower(kiln_string_t* string);

/// @brief Removes whitespace from the beginning and end of a kiln_string_t in place
/// @param string The kiln_string_t to trim
void kiln_string_trim_inplace(kiln_string_t* string);

/// @brief Returns a new kstring_ref_t with whitespace removed from beginning and end
/// @param string The kstring_ref_t to trim
/// @return A new kstring_ref_t pointing to the trimmed portion of the original string
kstring_ref_t kstring_ref_trim(kstring_ref_t string);

/// @brief Returns a reference to the substring of the string with the whitespace removed
/// @param string 
/// @return 
kstring_ref_t kiln_string_trim(const kiln_string_t* string);

/// @brief Replaces all instances of old_s with new_s
/// @param string 
/// @param old_s
/// @param new_s
void kiln_string_replace(kiln_string_t* string, const char* old_s, const char* new_s);

/// @brief Returns the index of the first character of the first occurance of `target`. 
/// @param string The kstring_ref_t to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
int64_t kstring_ref_find(kstring_ref_t string, const char* target);

/// @brief Finds the last occurrence of a target string within a StringRef
/// @param string The kstring_ref_t to search in
/// @param target The string to search for
/// @return The position of the last occurrence, or -1 if not found
int64_t kstring_ref_rfind(kstring_ref_t string, const char* target);

/// @brief Returns the index of the first character of the first occurance of `target` in a KilnString. 
/// @param string The kiln_string_t to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
extern inline int64_t kiln_string_find(const kiln_string_t* string, const char* target);

/// @brief Returns the index of the first character of the last occurance of `target` in a KilnString. 
/// @param string The kiln_string_t to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
extern inline int64_t kiln_string_rfind(const kiln_string_t* string, const char* target);

/// @brief Partitions a kstring_ref_t into two parts based on the first occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before delimiter, second part after delimiter
void kstring_ref_partition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]);

/// @brief Partitions a kstring_ref_t into two parts based on the last occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for from the end
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before last delimiter, second part after last delimiter
void kstring_ref_rpartition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]);

/// @brief Partitions a kiln_string_t into two parts based on the first occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before delimiter, second part after delimiter
extern inline void kiln_string_partition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]);

/// @brief Partitions a kiln_string_t into two parts based on the last occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for from the end
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before last delimiter, second part after last delimiter
extern inline void kiln_string_rpartition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]);


#endif // KILN_STRING_H