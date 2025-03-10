#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
KilnString KilnString_from_string_ref(StringRef str_ref) {
	KilnString str = {
		.length = str_ref.length,
		.capacity = (str_ref.length + 1)
	};

	str.ptr = (char*) malloc(str.capacity);
	memcpy(str.ptr, str_ref.ptr, str.length);
	str.ptr[str.length] = '\0';

	return str;
}

__always_inline StringRef KilnString_as_stringref(const KilnString* string) {
	StringRef ref;
	ref.length = string->length;
	ref.ptr = string->ptr;
	return ref;
}

__always_inline StringRef StringRef_from_kiln_str(const KilnString* string) {
	return KilnString_as_stringref(string);
}

__always_inline StringRef StringRef_from_cstr(const char* string) {
	StringRef ref;
	ref.length = strlen(string);
	ref.ptr = string;
	return ref;
}

/// @brief Frees the memory allocated by the kiln string
/// @param str 
/// @return 
__always_inline void KilnString_free(KilnString* str) {
	free(str->ptr);
	str->ptr = NULL;
}


/// @brief Appends the content of a char* to a KilnString
/// @param string 
/// @param cstr 
__always_inline void KilnString_push_cstr(KilnString* string, const char* cstr) {
	uint64_t length = strlen(cstr);
	StringRef str_ref = {
		.length = length,
		.ptr = cstr
	};

	KilnString_push_stringref(string, str_ref);
}


/// @brief Appends the content of a StringRef to a KilnString
/// @param string The KilnString to append to
/// @param str_ref The StringRef to append
void KilnString_push_stringref(KilnString* string, StringRef str_ref) {
    uint64_t new_length = string->length + str_ref.length;
    
    if (new_length + 1 > string->capacity) {
        uint64_t new_capacity = string->capacity * 2;
        if (new_capacity < new_length + 1) {
            new_capacity = new_length + 1;
        }
        
        string->ptr = (char*)realloc(string->ptr, new_capacity);
        string->capacity = new_capacity;
    }
    
    memcpy(string->ptr + string->length, str_ref.ptr, str_ref.length);
    
    string->length = new_length;
    
    string->ptr[string->length] = '\0';
}


/// @brief Checks if a KilnString ends with the specified suffix
/// @param string The string to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool KilnString_ends_with(const KilnString* string, const char* suffix) {
    uint64_t suffix_len = strlen(suffix);
    
    if (suffix_len > string->length) {
        return false;
    }
    
    return memcmp(string->ptr + (string->length - suffix_len), suffix, suffix_len) == 0;
}

/// @brief Checks if a KilnString starts with the specified prefix
/// @param string The string to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool KilnString_starts_with(const KilnString* string, const char* prefix) {    
    uint64_t prefix_len = strlen(prefix);
    
    if (prefix_len > string->length) {
        return false;
    }
    
    return memcmp(string->ptr, prefix, prefix_len) == 0;
}

/// @brief Checks if a StringRef ends with the specified suffix
/// @param string The string reference to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool StringRef_ends_with(StringRef string, const char* suffix) {    
    uint64_t suffix_len = strlen(suffix);
    
    if (suffix_len > string.length) {
        return false;
    }
    
    return memcmp(string.ptr + (string.length - suffix_len), suffix, suffix_len) == 0;
}

/// @brief Checks if a StringRef starts with the specified prefix
/// @param string The string reference to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool StringRef_starts_with(StringRef string, const char* prefix) {    
    uint64_t prefix_len = strlen(prefix);
    
    if (prefix_len > string.length) {
        return false;
    }
    
    return memcmp(string.ptr, prefix, prefix_len) == 0;
}

/// @brief Converts ASCII characters in a KilnString to lowercase, ignoring non-ASCII characters
/// @param string The KilnString to convert
void KilnString_to_ascii_lower(KilnString* string) {
    if (string->length == 0 || string->ptr == NULL) {
        return;
    }
    
    for (uint64_t i = 0; i < string->length; i++) {
        unsigned char c = (unsigned char)string->ptr[i];
        if (c >= 'A' && c <= 'Z') {
            string->ptr[i] = c + 32;
        }
    }
}

/// @brief Converts ASCII characters in a KilnString to uppercase, ignoring non-ASCII characters
/// @param string The KilnString to convert
void KilnString_to_ascii_upper(KilnString* string) {
    if (string->length == 0 || string->ptr == NULL) {
        return;
    }
    
    for (uint64_t i = 0; i < string->length; i++) {
        unsigned char c = (unsigned char)string->ptr[i];
        if (c >= 'a' && c <= 'z') {
            string->ptr[i] = c - 32;
        }
    }
}

/// @brief Converts a KilnString to uppercase, handling both ASCII and basic Unicode
/// @param string The KilnString to convert to uppercase
void KilnString_to_unicode_upper(KilnString* string) {
    if (string->length == 0 || string->ptr == NULL) {
        return;
    }
    
    // First check if it's a simple ASCII string for fast path
    bool is_ascii = true;
    for (uint64_t i = 0; i < string->length; i++) {
        if ((unsigned char)string->ptr[i] > 127) {
            is_ascii = false;
            break;
        }
    }
    
    if (is_ascii) {
        // Fast path for ASCII
        for (uint64_t i = 0; i < string->length; i++) {
            string->ptr[i] = toupper((unsigned char)string->ptr[i]);
        }
    } else {
        // Handle UTF-8 encoding
        uint64_t i = 0;
        while (i < string->length) {
            unsigned char c = (unsigned char)string->ptr[i];
            
            if (c <= 127) {
                string->ptr[i] = toupper(c);
                i++;
            } else if (c >= 192 && c <= 223) {
                if (i + 1 < string->length) {
                    unsigned char c2 = (unsigned char)string->ptr[i+1];
                    if (c == 195 && c2 >= 160 && c2 <= 182) { 
                        string->ptr[i+1] = c2 - 32; 
                    } else if (c == 195 && c2 >= 184 && c2 <= 191) { 
                        string->ptr[i+1] = c2 - 32; 
                    }
                }
                i += 2;
            } else if (c >= 224 && c <= 239) {
                i += 3; 
            } else if (c >= 240 && c <= 247) {
                i += 4;
            } else {
                i++;
            }
        }
    }
}

/// @brief Converts a KilnString to lowercase, handling both ASCII and basic Unicode
/// @param string The KilnString to convert to lowercase
void KilnString_to_unicode_lower(KilnString* string) {
    if (string->length == 0 || string->ptr == NULL) {
        return;
    }
    
    // First check if it's a simple ASCII string for fast path
    bool is_ascii = true;
    for (uint64_t i = 0; i < string->length; i++) {
        if ((unsigned char)string->ptr[i] > 127) {
            is_ascii = false;
            break;
        }
    }
    
    if (is_ascii) {
        // Fast path for ASCII
        for (uint64_t i = 0; i < string->length; i++) {
            string->ptr[i] = tolower((unsigned char)string->ptr[i]);
        }
    } else {
        // Handle UTF-8 encoding
        uint64_t i = 0;
        while (i < string->length) {
            unsigned char c = (unsigned char)string->ptr[i];
            
            if (c <= 127) {
                string->ptr[i] = tolower(c);
                i++;
            } else if (c >= 192 && c <= 223) {
                if (i + 1 < string->length) {
                    unsigned char c2 = (unsigned char)string->ptr[i+1];
                    if (c == 195 && c2 >= 128 && c2 <= 150) { 
                        string->ptr[i+1] = c2 + 32; 
                    } else if (c == 195 && c2 >= 152 && c2 <= 159) {
                        string->ptr[i+1] = c2 + 32;
                    }
                }
                i += 2; 
            } else if (c >= 224 && c <= 239) {
                i += 3;
            } else if (c >= 240 && c <= 247) {
                i += 4;
            } else {
                i++;
            }
        }
    }
}

/// @brief Returns a reference to the substring `string[start_idx:x]` where `x` is the index of the first character of the delimiter as it appears in `string`
/// @param string The source KilnString to search within
/// @param delimiter The delimiter to search for
/// @param start_idx The starting index in the string to begin the search
/// @return Returns a string reference type which will be null if `start_idx` is greater than the length of the string
StringRef KilnString_split_next(const KilnString* string, const char* delimiter, uint64_t start_idx) {
    StringRef result = {NULL, 0};
    
    if (start_idx >= string->length) {
        return result;
    }
    
    char* start_ptr = string->ptr + start_idx;
    uint64_t remaining_length = string->length - start_idx;
    
    char* delimiter_ptr = strstr(start_ptr, delimiter);
    
    if (delimiter_ptr == NULL) {
        result.ptr = start_ptr;
        result.length = remaining_length;
    } else {
        result.ptr = start_ptr;
        result.length = delimiter_ptr - start_ptr;
    }
    
    return result;
}

/// @brief Returns a reference to the substring `string[start_idx:x]` where `x` is the index of the first character of the delimiter as it appears in `string`
/// @param string The source StringRef to search within
/// @param delimiter The delimiter to search for
/// @param start_idx The starting index in the string to begin the search
/// @return Returns a string reference type which will be null if `start_idx` is greater than the length of the string
StringRef StringRef_split_next(StringRef string, const char* delimiter, uint64_t start_idx) {
    StringRef result = {NULL, 0};
    
    if (start_idx >= string.length) {
        return result;
    }
    
    char* start_ptr = string.ptr + start_idx;
    uint64_t remaining_length = string.length - start_idx;
    
    char* delimiter_ptr = strstr(start_ptr, delimiter);
    
    if (delimiter_ptr == NULL) {
        result.ptr = start_ptr;
        result.length = remaining_length;
    } else {
        result.ptr = start_ptr;
        result.length = delimiter_ptr - start_ptr;
    }
    
    return result;
}

/// @brief Returns everything before the first occurance of `delimiter`
/// @param string The string to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion before the first delimiter
StringRef StringRef_partition_left(StringRef string, const char* delimiter) {
    StringRef result = {string.ptr, 0};
    
    if (string.length == 0 || delimiter == NULL) {
        return result;
    }
    
    uint64_t delimiter_len = strlen(delimiter);
    if (delimiter_len == 0) {
        return result;
    }
    
    char* found = strstr(string.ptr, delimiter);
    if (found == NULL) {
        result.length = string.length;
    } else {
        result.length = found - string.ptr;
    }
    
    return result;
}

/// @brief Returns everything after the first occurance of `delimiter`
/// @param string The string to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion after the first delimiter (NULL if delimiter does not exist)
StringRef StringRef_partition_right(StringRef string, const char* delimiter) {
    StringRef result = {NULL, 0};
    
    if (string.length == 0 || delimiter == NULL) {
        return result;
    }
    
    uint64_t delimiter_len = strlen(delimiter);
    if (delimiter_len == 0) {
        result = string;
        return result;
    }
    
    char* found = strstr(string.ptr, delimiter);
    if (found == NULL) {
        return result;
    } else {
        result.ptr = found + delimiter_len;
        
        uint64_t offset = result.ptr - string.ptr;
        if (offset < string.length) {
            result.length = string.length - offset;
        } else {
            result.length = 0;
        }
    }
    
    return result;
}

/// @brief Returns everything before the last occurance of `delimiter`
/// @param string The string to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion before the last delimiter
StringRef StringRef_rpartition_left(StringRef string, const char* delimiter) {
    StringRef result = {string.ptr, 0};
    
    if (string.length == 0 || delimiter == NULL) {
        return result;
    }
    
    uint64_t delimiter_len = strlen(delimiter);
    if (delimiter_len == 0) {
        return result;
    }
    
    char* last_found = NULL;
    char* current_pos = string.ptr;
    
    while (1) {
        char* found = strstr(current_pos, delimiter);
        if (found == NULL) {
            break;
        }
        
        last_found = found;
        current_pos = found + 1;
        
        if ((uint64_t)(current_pos - string.ptr) >= string.length) {
            break;
        }
    }
    
    if (last_found == NULL) {
        result.length = string.length;
    } else {
        result.length = last_found - string.ptr;
    }
    
    return result;
}

/// @brief Returns everything after the last occurance of `delimiter`
/// @param string The string to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion after the last delimiter (NULL if delimiter does not exist)
StringRef StringRef_rpartition_right(StringRef string, const char* delimiter) {
    StringRef result = {NULL, 0};
    
    if (string.length == 0 || delimiter == NULL) {
        return result;
    }
    
    uint64_t delimiter_len = strlen(delimiter);
    if (delimiter_len == 0) {
        result = string;
        return result;
    }
    
    char* last_found = NULL;
    char* current_pos = string.ptr;
    
    while (1) {
        char* found = strstr(current_pos, delimiter);
        if (found == NULL) {
            break;
        }
        
        last_found = found;
        current_pos = found + 1;
        
        if ((uint64_t)(current_pos - string.ptr) >= string.length) {
            break;
        }
    }
    
    if (last_found == NULL) {
        return result;
    } else {
        result.ptr = last_found + delimiter_len;
        
        uint64_t offset = result.ptr - string.ptr;
        if (offset < string.length) {
            result.length = string.length - offset;
        } else {
            result.length = 0;
        }
    }
    
    return result;
}

/// @brief Returns everything before the first occurrence of `delimiter` in a KilnString
/// @param string The KilnString to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion before the first delimiter
__always_inline StringRef KilnString_partition_left(const KilnString* string, const char* delimiter) {
	StringRef ref = KilnString_as_stringref(string);
	return StringRef_partition_left(ref, delimiter);
}

/// @brief Returns everything after the first occurrence of `delimiter` in a KilnString
/// @param string The KilnString to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion after the first delimiter (NULL if delimiter does not exist)
__always_inline StringRef KilnString_partition_right(const KilnString* string, const char* delimiter) {
	StringRef ref = KilnString_as_stringref(string);
	return StringRef_partition_right(ref, delimiter);
}

/// @brief Returns everything before the last occurrence of `delimiter` in a KilnString
/// @param string The KilnString to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion before the last delimiter
__always_inline StringRef KilnString_rpartition_left(const KilnString* string, const char* delimiter) {
	StringRef ref = KilnString_as_stringref(string);
	return StringRef_rpartition_left(ref, delimiter);
}

/// @brief Returns everything after the last occurrence of `delimiter` in a KilnString
/// @param string The KilnString to search in
/// @param delimiter The delimiter to search for
/// @return A StringRef containing the portion after the last delimiter (NULL if delimiter does not exist)
__always_inline StringRef KilnString_rpartition_right(const KilnString* string, const char* delimiter) {
	StringRef ref = KilnString_as_stringref(string);
	return StringRef_rpartition_right(ref, delimiter);
}