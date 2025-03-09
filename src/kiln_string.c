#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../include/kiln_string.h"


/// @brief Copies the data from string to it's own internal buffer
/// @param string 
/// @return 
KilnString KilnString_from_cstr(const char* string) {
	uint64_t length = strlen(string);

	KilnString k_str = {
		.length = length,
		.capacity = length + 1,
	};

	k_str.ptr = (char*) malloc(length + 1);
	memcpy(k_str.ptr, string, length);
	k_str.ptr[length] = '\0';

	return k_str;
}

/// @brief Creates a string from a StringRef by compying the contents. 
/// @param str_ref 
/// @return 
KilnString KilnString_from_string_ref(const StringRef* str_ref) {
	KilnString str = {
		.length = str_ref->length,
		.capacity = (str_ref->length + 1)
	};

	str.ptr = (char*) malloc(str.capacity);
	memcpy(str.ptr, str_ref->ptr, str.length);
	str.ptr[str.length] = '\0';

	return str;
}

__always_inline StringRef StringRef_from_kiln_str(const KilnString* string) {
	StringRef ref;
	ref.length = string->length;
	ref.ptr = string->ptr;
	return ref;
}

__always_inline StringRef StringRef_from_cstr(const char* string) {
	StringRef ref;
	ref.length = strlen(string);
	ref.ptr = string;
	return ref;
}

__always_inline void KilnString_free(KilnString* str) {
	free(str->ptr);
	str->ptr = NULL;
}

/// @brief Returns a reference to the substring `string[start_idx:x]` where `x` is the index of the first character of the delimiter as it appears in `string`
/// @param string The source KilnString to search within
/// @param delimiter The delimiter to search for
/// @param start_idx The starting index in the string to begin the search
/// @return Returns a string reference type which will be null if `start_idx` is greater than the length of the string
StringRef KilnString_split_next(const KilnString* string, const char* delimiter, uint64_t start_idx) {
    StringRef result = {NULL, 0};
    
    // Check if start_idx is valid
    if (start_idx >= string->length) {
        return result;
    }
    
    // Get pointer to the start position
    char* start_ptr = string->ptr + start_idx;
    uint64_t remaining_length = string->length - start_idx;
    
    // Find the delimiter
    char* delimiter_ptr = strstr(start_ptr, delimiter);
    
    if (delimiter_ptr == NULL) {
        // Delimiter not found, return the rest of the string
        result.ptr = start_ptr;
        result.length = remaining_length;
    } else {
        // Delimiter found, calculate the substring length up to the delimiter
        result.ptr = start_ptr;
        result.length = delimiter_ptr - start_ptr;
    }
    
    return result;
}