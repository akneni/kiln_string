#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../include/kiln_string.h"


/// @brief Copies the data from string to it's own internal buffer
/// @param string 
/// @return 
kiln_string_t kiln_string_from_cstr(const char* string) {
	uint64_t length = strlen(string);

	kiln_string_t k_str = {
		.__length = length,
		.__capacity = length + 1,
	};

	k_str.ptr = (char*) malloc(length + 1);
	memcpy(k_str.ptr, string, length);
	k_str.ptr[length] = '\0';

	return k_str;
}

/// @brief Creates a string from a kstring_ref_t by compying the contents. 
/// @param str_ref 
/// @return 
inline kiln_string_t kiln_string_from_string_ref(kstring_ref_t str_ref) {
	kiln_string_t str = {
		.__length = str_ref.__length,
		.__capacity = (str_ref.__length + 1)
	};

	str.ptr = (char*) malloc(str.__capacity);
	memcpy(str.ptr, str_ref.ptr, str.__length);
	str.ptr[str.__length] = '\0';

	return str;
}

/// @brief Creates a string from a kstring_ref_t by compying the contents. 
/// @param str_ref 
/// @return 
inline kiln_string_t kstring_ref_to_kiln_string(kstring_ref_t str_ref) {
	return kiln_string_from_string_ref(str_ref);
}

inline kstring_ref_t kiln_string_as_stringref(const kiln_string_t* string) {
	kstring_ref_t ref;
	ref.__length = string->__length;
	ref.ptr = string->ptr;
	return ref;
}

inline kstring_ref_t kstring_ref_from_kiln_str(const kiln_string_t* string) {
	return kiln_string_as_stringref(string);
}

inline kstring_ref_t kstring_ref_from_cstr(const char* string) {
	kstring_ref_t ref;
	ref.__length = strlen(string);
	ref.ptr = string;
	return ref;
}

/// @brief Frees the memory allocated by the kiln string. Sets the pointer to NULL
/// @param str 
/// @return 
inline void kiln_string_free(kiln_string_t* str) {
	free(str->ptr);
	str->ptr = NULL;
}

/// @brief Appends the content of a char* to a KilnString
/// @param string 
/// @param cstr 
inline void kiln_string_push_cstr(kiln_string_t* string, const char* cstr) {
	uint64_t length = strlen(cstr);
	kstring_ref_t str_ref = {
		.__length = length,
		.ptr = cstr
	};

	kiln_string_push_stringref(string, str_ref);
}


/// @brief Appends the content of a kstring_ref_t to a KilnString
/// @param string The kiln_string_t to append to
/// @param str_ref The kstring_ref_t to append
void kiln_string_push_stringref(kiln_string_t* string, kstring_ref_t str_ref) {
    uint64_t new_length = string->__length + str_ref.__length;
    
    if (new_length + 1 > string->__capacity) {
        uint64_t new_capacity = string->__capacity * 2;
        if (new_capacity < new_length + 1) {
            new_capacity = new_length + 1;
        }
        
        string->ptr = (char*)realloc(string->ptr, new_capacity);
        string->__capacity = new_capacity;
    }
    
    memcpy(string->ptr + string->__length, str_ref.ptr, str_ref.__length);
    
    string->__length = new_length;
    
    string->ptr[string->__length] = '\0';
}


/// @brief Checks if a kiln_string_t ends with the specified suffix
/// @param string The string to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool kiln_string_ends_with(const kiln_string_t* string, const char* suffix) {
    uint64_t suffix_len = strlen(suffix);
    
    if (suffix_len > string->__length) {
        return false;
    }
    
    return memcmp(string->ptr + (string->__length - suffix_len), suffix, suffix_len) == 0;
}

/// @brief Checks if a kiln_string_t starts with the specified prefix
/// @param string The string to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool kiln_string_starts_with(const kiln_string_t* string, const char* prefix) {    
    uint64_t prefix_len = strlen(prefix);
    
    if (prefix_len > string->__length) {
        return false;
    }
    
    return memcmp(string->ptr, prefix, prefix_len) == 0;
}

/// @brief Checks if a kstring_ref_t ends with the specified suffix
/// @param string The string reference to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool kstring_ref_ends_with(kstring_ref_t string, const char* suffix) {    
    uint64_t suffix_len = strlen(suffix);
    
    if (suffix_len > string.__length) {
        return false;
    }
    
    return memcmp(string.ptr + (string.__length - suffix_len), suffix, suffix_len) == 0;
}

/// @brief Checks if a kstring_ref_t starts with the specified prefix
/// @param string The string reference to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool kstring_ref_starts_with(kstring_ref_t string, const char* prefix) {    
    uint64_t prefix_len = strlen(prefix);
    
    if (prefix_len > string.__length) {
        return false;
    }
    
    return memcmp(string.ptr, prefix, prefix_len) == 0;
}

/// @brief Gets a substring from the string passed
/// @param string The source kstring_ref_t to extract substring from
/// @param start_idx -1 to default to the start (or 0)
/// @param end_idx  -1 to default to the end
/// @return A kstring_ref_t pointing to the requested substring
kstring_ref_t kstring_ref_substring(kstring_ref_t string, int64_t start_idx, int64_t end_idx) {
    kstring_ref_t result = {NULL, 0};
    
    if (start_idx < 0) {
        start_idx = 0;
    }
    
    if (end_idx < 0 || end_idx > string.__length) {
        end_idx = string.__length;
    }
    
    if (start_idx > string.__length || start_idx > end_idx) {
        return result;
    }
    
    result.ptr = string.ptr + start_idx;
    result.__length = end_idx - start_idx;
    
    return result;
}

/// @brief Gets a substring from the KilnString
/// @param string The kiln_string_t to extract substring from
/// @param start_idx -1 to default to the start (or 0)
/// @param end_idx -1 to default to the end
/// @return A kstring_ref_t pointing to the requested substring
inline kstring_ref_t kiln_string_substring(const kiln_string_t* string, int64_t start_idx, int64_t end_idx) {
    kstring_ref_t ref = {string->ptr, string->__length};
    return kstring_ref_substring(ref, start_idx, end_idx);
}

/// @brief Checks if a kstring_ref_t equals a C-style string
/// @param string The kstring_ref_t to compare
/// @param other The C-style string to compare against
/// @return true if the strings are equal, false otherwise
inline bool kstring_ref_equals_cstr(kstring_ref_t string, const char* other) {
    uint64_t other_len = strlen(other);
    
    if (string.__length != other_len) {
        return false;
    }
    
    return memcmp(string.ptr, other, string.__length) == 0;
}

/// @brief Checks if two StringRefs are equal
/// @param s1 The first kstring_ref_t to compare
/// @param s2 The second kstring_ref_t to compare
/// @return true if the strings are equal, false otherwise
inline bool kstring_ref_equals(kstring_ref_t s1, kstring_ref_t s2) {    
    if (s1.__length != s2.__length) {
        return false;
    }
    return memcmp(s1.ptr, s2.ptr, s1.__length) == 0;
}

/// @brief Checks if a kiln_string_t equals a C-style string
/// @param string The kiln_string_t to compare
/// @param other The C-style string to compare against
/// @return true if the strings are equal, false otherwise
inline bool kiln_string_equals_cstr(const kiln_string_t* string, const char* other) {
    kstring_ref_t ref = {string->ptr, string->__length};
    return kstring_ref_equals_cstr(ref, other);
}

/// @brief Checks if two KilnStrings are equalg
/// @param s1 The first kiln_string_t to compare
/// @param s2 The first kiln_string_t to compare
/// @return true if the strings are equal, false otherwise
inline bool kiln_string_equals(const kiln_string_t* s1, const kiln_string_t* s2) {
	kstring_ref_t ref_1 = {s1->ptr, s1->__length};
	kstring_ref_t ref_2 = {s2->ptr, s2->__length};
	return kstring_ref_equals(ref_1, ref_2);
}

/// @brief Compares two StringRefs lexicographically
/// @param s1 First kstring_ref_t to compare
/// @param s2 Second kstring_ref_t to compare
/// @return 0 if equal, negative if s1 < s2, positive if s1 > s2
int32_t kstring_ref_compare(kstring_ref_t s1, kstring_ref_t s2) {
    uint64_t min_len = s1.__length < s2.__length ? s1.__length : s2.__length;
    
    int result = memcmp(s1.ptr, s2.ptr, min_len);
    
    if (result != 0) {
        return result;
    } else if (s1.__length < s2.__length) {
        return -1;
    } else if (s1.__length > s2.__length) {
        return 1;
    }
    
    return 0;
}

/// @brief Compares two KilnStrings lexicographically
/// @param s1 First kiln_string_t to compare
/// @param s2 Second kiln_string_t to compare
/// @return 0 if equal, negative if s1 < s2, positive if s1 > s2
inline int32_t kiln_string_compare(const kiln_string_t* s1, const kiln_string_t* s2) {
    kstring_ref_t r1 = {s1->ptr, s1->__length};
    kstring_ref_t r2 = {s2->ptr, s2->__length};
    return kstring_ref_compare(r1, r2);
}

/// @brief Converts ASCII characters in a kiln_string_t to lowercase, ignoring non-ASCII characters
/// @param string The kiln_string_t to convert
void kiln_string_to_ascii_lower(kiln_string_t* string) {
    if (string->__length == 0 || string->ptr == NULL) {
        return;
    }
    
    for (uint64_t i = 0; i < string->__length; i++) {
        unsigned char c = (unsigned char)string->ptr[i];
        if (c >= 'A' && c <= 'Z') {
            string->ptr[i] = c + 32;
        }
    }
}

/// @brief Converts ASCII characters in a kiln_string_t to uppercase, ignoring non-ASCII characters
/// @param string The kiln_string_t to convert
void kiln_string_to_ascii_upper(kiln_string_t* string) {
    if (string->__length == 0 || string->ptr == NULL) {
        return;
    }
    
    for (uint64_t i = 0; i < string->__length; i++) {
        unsigned char c = (unsigned char)string->ptr[i];
        if (c >= 'a' && c <= 'z') {
            string->ptr[i] = c - 32;
        }
    }
}

/// @brief Converts a kiln_string_t to uppercase, handling both ASCII and basic Unicode
/// @param string The kiln_string_t to convert to uppercase
void kiln_string_to_unicode_upper(kiln_string_t* string) {
    if (string->__length == 0 || string->ptr == NULL) {
        return;
    }
    
    // First check if it's a simple ASCII string for fast path
    bool is_ascii = true;
    for (uint64_t i = 0; i < string->__length; i++) {
        if ((unsigned char)string->ptr[i] > 127) {
            is_ascii = false;
            break;
        }
    }
    
    if (is_ascii) {
        // Fast path for ASCII
        for (uint64_t i = 0; i < string->__length; i++) {
            string->ptr[i] = toupper((unsigned char)string->ptr[i]);
        }
    } else {
        // Handle UTF-8 encoding
        uint64_t i = 0;
        while (i < string->__length) {
            unsigned char c = (unsigned char)string->ptr[i];
            
            if (c <= 127) {
                string->ptr[i] = toupper(c);
                i++;
            } else if (c >= 192 && c <= 223) {
                if (i + 1 < string->__length) {
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

/// @brief Converts a kiln_string_t to lowercase, handling both ASCII and basic Unicode
/// @param string The kiln_string_t to convert to lowercase
void kiln_string_to_unicode_lower(kiln_string_t* string) {
    if (string->__length == 0 || string->ptr == NULL) {
        return;
    }
    
    // First check if it's a simple ASCII string for fast path
    bool is_ascii = true;
    for (uint64_t i = 0; i < string->__length; i++) {
        if ((unsigned char)string->ptr[i] > 127) {
            is_ascii = false;
            break;
        }
    }
    
    if (is_ascii) {
        // Fast path for ASCII
        for (uint64_t i = 0; i < string->__length; i++) {
            string->ptr[i] = tolower((unsigned char)string->ptr[i]);
        }
    } else {
        // Handle UTF-8 encoding
        uint64_t i = 0;
        while (i < string->__length) {
            unsigned char c = (unsigned char)string->ptr[i];
            
            if (c <= 127) {
                string->ptr[i] = tolower(c);
                i++;
            } else if (c >= 192 && c <= 223) {
                if (i + 1 < string->__length) {
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

/// @brief Removes whitespace from the beginning and end of a kiln_string_t in place
/// @param string The kiln_string_t to trim
void kiln_string_trim_inplace(kiln_string_t* string) {
    uint64_t start = 0;
    while (start < string->__length && isspace((unsigned char)string->ptr[start])) {
        start++;
    }
    
    if (start == string->__length) {
        string->ptr[0] = '\0';
        string->__length = 0;
        return;
    }
    
    uint64_t end = string->__length - 1;
    while (end > start && isspace((unsigned char)string->ptr[end])) {
        end--;
    }
    
    uint64_t new_length = end - start + 1;
    
    if (start > 0) {
        memmove(string->ptr, string->ptr + start, new_length);
    }
    
    string->ptr[new_length] = '\0';
    string->__length = new_length;
}

/// @brief Returns a new kstring_ref_t with whitespace removed from beginning and end
/// @param string The kstring_ref_t to trim
/// @return A new kstring_ref_t pointing to the trimmed portion of the original string
kstring_ref_t kstring_ref_trim(kstring_ref_t string) {
    kstring_ref_t result = {NULL, 0};
    
    if (string.ptr == NULL || string.__length == 0) {
        return result;
    }
    
    uint64_t start = 0;
    while (start < string.__length && isspace((unsigned char)string.ptr[start])) {
        start++;
    }
    
    if (start == string.__length) {
        result.ptr = string.ptr + string.__length;
        result.__length = 0;
        return result;
    }
    
    uint64_t end = string.__length - 1;
    while (end > start && isspace((unsigned char)string.ptr[end])) {
        end--;
    }
    
    result.ptr = string.ptr + start;
    result.__length = end - start + 1;
    
    return result;
}

/// @brief Returns a reference to the substring of the string with the whitespace removed
/// @param string 
/// @return 
kstring_ref_t kiln_string_trim(const kiln_string_t* string) {
	kstring_ref_t ref = {string->ptr, string->__length};
	return kstring_ref_trim(ref);
}


/// @brief Replaces all instances of old_s with new_s
/// @param string 
/// @param old_s
/// @param new_s
void kiln_string_replace(kiln_string_t* string, const char* old_s, const char* new_s) {   
	const size_t old_len = strlen(old_s);
	if (old_len == 0) {
		return;
	}
	
	const size_t new_len = strlen(new_s);
	
	size_t count = 0;
	const char* pos = string->ptr;
	while ((pos = strstr(pos, old_s)) != NULL) {
		count++;
		pos += old_len;
	}
	
	if (count == 0) {
		return;
	}
	
	const size_t new_total_len = string->__length + count * (new_len - old_len);
	
	size_t new_capacity = new_total_len + 1;
	if (new_capacity < string->__capacity) {
		new_capacity = string->__capacity;
	}
	
	char* new_buffer = (char*)malloc(new_capacity);
	if (!new_buffer) {
		return;
	}
	
	char* src = string->ptr;
	char* dst = new_buffer;
	const char* end = string->ptr + string->__length;
	
	while (src < end) {
		if (src + old_len <= end && strncmp(src, old_s, old_len) == 0) {
			memcpy(dst, new_s, new_len);
			dst += new_len;
			src += old_len;
		} else {
			*dst++ = *src++;
		}
	}
	
	*dst = '\0';
	
	free(string->ptr);
	string->ptr = new_buffer;
	string->__length = new_total_len;
	string->__capacity = new_capacity;
}


/// @brief Returns the index of the first character of the first occurance of `target`. 
/// @param string The kstring_ref_t to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
int64_t kstring_ref_find(kstring_ref_t string, const char* target) {
    uint64_t target_len = strlen(target);
    if (target_len == 0) {
        return 0;
    }
    if (target_len > string.__length) {
        return -1;
    }

    char* found = strstr(string.ptr, target);
    if (found == NULL) {
        return -1;
    }
    
    return (int64_t)(found - string.ptr);
}

/// @brief Finds the last occurrence of a target string within a StringRef
/// @param string The kstring_ref_t to search in
/// @param target The string to search for
/// @return The position of the last occurrence, or -1 if not found
int64_t kstring_ref_rfind(kstring_ref_t string, const char* target) {
    size_t target_len = strlen(target);
    
    if (target_len == 0 || target_len > string.__length) {
        return -1;
    }
    
    for (int64_t i = string.__length - target_len; i >= 0; i--) {
        bool match = true;
        
        for (size_t j = 0; j < target_len; j++) {
            if (string.ptr[i + j] != target[j]) {
                match = false;
                break;
            }
        }        
        if (match) {
            return i;
        }
    }
    
    return -1;
}

/// @brief Returns the index of the first character of the first occurance of `target` in a KilnString. 
/// @param string The kiln_string_t to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
inline int64_t kiln_string_find(const kiln_string_t* string, const char* target) {
    kstring_ref_t ref = {string->ptr, string->__length};
    return kstring_ref_find(ref, target);
}

/// @brief Returns the index of the first character of the last occurance of `target` in a KilnString. 
/// @param string The kiln_string_t to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
inline int64_t kiln_string_rfind(const kiln_string_t* string, const char* target) {
    kstring_ref_t ref = {string->ptr, string->__length};
    return kstring_ref_rfind(ref, target);
}

/// @brief Partitions a kstring_ref_t into two parts based on the first occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before delimiter, second part after delimiter
void kstring_ref_partition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]) {
    // Find the first occurrence of the delimiter
    int64_t delimiter_pos = kstring_ref_find(string, delimiter);
    
    if (delimiter_pos == -1) {
        // Delimiter not found, first part is the entire string, second part is empty
        output_buffer[0] = string;
        output_buffer[1] = (kstring_ref_t){ .ptr = string.ptr + string.__length, .__length = 0 };
    } else {
        // Delimiter found, split the string into two parts
        // First part: from start to delimiter
        output_buffer[0] = (kstring_ref_t) {
            .ptr = string.ptr,
            .__length = delimiter_pos
        };
        
        // Second part: after delimiter to end
        size_t delimiter_len = strlen(delimiter);
        output_buffer[1] = (kstring_ref_t){
            .ptr = string.ptr + delimiter_pos + delimiter_len,
            .__length = string.__length - delimiter_pos - delimiter_len
        };
    }
}

/// @brief Partitions a kstring_ref_t into two parts based on the last occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for from the end
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before last delimiter, second part after last delimiter
void kstring_ref_rpartition(kstring_ref_t string, const char* delimiter, kstring_ref_t output_buffer[2]) {
    // Find the last occurrence of the delimiter
    int64_t delimiter_pos = kstring_ref_rfind(string, delimiter);
    
    if (delimiter_pos == -1) {
        // Delimiter not found, first part is the entire string, second part is empty
        output_buffer[0] = string;
        output_buffer[1] = (kstring_ref_t){ .ptr = string.ptr + string.__length, .__length = 0 };
    } else {
        // Delimiter found, split the string into two parts
        // First part: from start to last delimiter
        output_buffer[0] = (kstring_ref_t){
            .ptr = string.ptr,
            .__length = delimiter_pos
        };
        
        // Second part: after last delimiter to end
        size_t delimiter_len = strlen(delimiter);
        output_buffer[1] = (kstring_ref_t){
            .ptr = string.ptr + delimiter_pos + delimiter_len,
            .__length = string.__length - delimiter_pos - delimiter_len
        };
    }
}

/// @brief Partitions a kiln_string_t into two parts based on the first occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before delimiter, second part after delimiter
inline void kiln_string_partition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]) {
    kstring_ref_t ref = {string->ptr, string->__length};
    kstring_ref_partition(ref, delimiter, output_buffer);
}

/// @brief Partitions a kiln_string_t into two parts based on the last occurrence of a delimiter
/// @param string The kstring_ref_t to be partitioned
/// @param delimiter The delimiter string to search for from the end
/// @param output_buffer Array of 2 kstring_ref_t's to store the results - first part before last delimiter, second part after last delimiter
inline void kiln_string_rpartition(const kiln_string_t* string, const char* delimiter, kstring_ref_t output_buffer[2]) {
    kstring_ref_t ref = {string->ptr, string->__length};
    kstring_ref_rpartition(ref, delimiter, output_buffer);
}
