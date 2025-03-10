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
		.__length = length,
		.__capacity = length + 1,
	};

	k_str.ptr = (char*) malloc(length + 1);
	memcpy(k_str.ptr, string, length);
	k_str.ptr[length] = '\0';

	return k_str;
}

/// @brief Creates a string from a StringRef by compying the contents. 
/// @param str_ref 
/// @return 
inline KilnString KilnString_from_string_ref(StringRef str_ref) {
	KilnString str = {
		.__length = str_ref.__length,
		.__capacity = (str_ref.__length + 1)
	};

	str.ptr = (char*) malloc(str.__capacity);
	memcpy(str.ptr, str_ref.ptr, str.__length);
	str.ptr[str.__length] = '\0';

	return str;
}

/// @brief Creates a string from a StringRef by compying the contents. 
/// @param str_ref 
/// @return 
inline KilnString StringRef_to_kiln_string(StringRef str_ref) {
	return KilnString_from_string_ref(str_ref);
}

inline StringRef KilnString_as_stringref(const KilnString* string) {
	StringRef ref;
	ref.__length = string->__length;
	ref.ptr = string->ptr;
	return ref;
}

inline StringRef StringRef_from_kiln_str(const KilnString* string) {
	return KilnString_as_stringref(string);
}

inline StringRef StringRef_from_cstr(const char* string) {
	StringRef ref;
	ref.__length = strlen(string);
	ref.ptr = string;
	return ref;
}

/// @brief Frees the memory allocated by the kiln string. Sets the pointer to NULL
/// @param str 
/// @return 
inline void KilnString_free(KilnString* str) {
	free(str->ptr);
	str->ptr = NULL;
}

/// @brief Appends the content of a char* to a KilnString
/// @param string 
/// @param cstr 
inline void KilnString_push_cstr(KilnString* string, const char* cstr) {
	uint64_t length = strlen(cstr);
	StringRef str_ref = {
		.__length = length,
		.ptr = cstr
	};

	KilnString_push_stringref(string, str_ref);
}


/// @brief Appends the content of a StringRef to a KilnString
/// @param string The KilnString to append to
/// @param str_ref The StringRef to append
void KilnString_push_stringref(KilnString* string, StringRef str_ref) {
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


/// @brief Checks if a KilnString ends with the specified suffix
/// @param string The string to check
/// @param suffix The suffix to check for
/// @return true if the string ends with the suffix, false otherwise
bool KilnString_ends_with(const KilnString* string, const char* suffix) {
    uint64_t suffix_len = strlen(suffix);
    
    if (suffix_len > string->__length) {
        return false;
    }
    
    return memcmp(string->ptr + (string->__length - suffix_len), suffix, suffix_len) == 0;
}

/// @brief Checks if a KilnString starts with the specified prefix
/// @param string The string to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool KilnString_starts_with(const KilnString* string, const char* prefix) {    
    uint64_t prefix_len = strlen(prefix);
    
    if (prefix_len > string->__length) {
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
    
    if (suffix_len > string.__length) {
        return false;
    }
    
    return memcmp(string.ptr + (string.__length - suffix_len), suffix, suffix_len) == 0;
}

/// @brief Checks if a StringRef starts with the specified prefix
/// @param string The string reference to check
/// @param prefix The prefix to check for
/// @return true if the string starts with the prefix, false otherwise
bool StringRef_starts_with(StringRef string, const char* prefix) {    
    uint64_t prefix_len = strlen(prefix);
    
    if (prefix_len > string.__length) {
        return false;
    }
    
    return memcmp(string.ptr, prefix, prefix_len) == 0;
}

/// @brief Gets a substring from the string passed
/// @param string The source StringRef to extract substring from
/// @param start_idx -1 to default to the start (or 0)
/// @param end_idx  -1 to default to the end
/// @return A StringRef pointing to the requested substring
StringRef StringRef_substring(StringRef string, int64_t start_idx, int64_t end_idx) {
    StringRef result = {NULL, 0};
    
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
/// @param string The KilnString to extract substring from
/// @param start_idx -1 to default to the start (or 0)
/// @param end_idx -1 to default to the end
/// @return A StringRef pointing to the requested substring
inline StringRef KilnString_substring(const KilnString* string, int64_t start_idx, int64_t end_idx) {
    StringRef ref = {string->ptr, string->__length};
    return StringRef_substring(ref, start_idx, end_idx);
}

/// @brief Checks if a StringRef equals a C-style string
/// @param string The StringRef to compare
/// @param other The C-style string to compare against
/// @return true if the strings are equal, false otherwise
inline bool StringRef_equals_cstr(StringRef string, const char* other) {
    uint64_t other_len = strlen(other);
    
    if (string.__length != other_len) {
        return false;
    }
    
    return memcmp(string.ptr, other, string.__length) == 0;
}

/// @brief Checks if two StringRefs are equal
/// @param s1 The first StringRef to compare
/// @param s2 The second StringRef to compare
/// @return true if the strings are equal, false otherwise
inline bool StringRef_equals(StringRef s1, StringRef s2) {    
    if (s1.__length != s2.__length) {
        return false;
    }
    return memcmp(s1.ptr, s2.ptr, s1.__length) == 0;
}

/// @brief Checks if a KilnString equals a C-style string
/// @param string The KilnString to compare
/// @param other The C-style string to compare against
/// @return true if the strings are equal, false otherwise
inline bool KilnString_equals_cstr(const KilnString* string, const char* other) {
    StringRef ref = {string->ptr, string->__length};
    return StringRef_equals_cstr(ref, other);
}

/// @brief Checks if two KilnStrings are equalg
/// @param s1 The first KilnString to compare
/// @param s2 The first KilnString to compare
/// @return true if the strings are equal, false otherwise
inline bool KilnString_equals(const KilnString* s1, const KilnString* s2) {
	StringRef ref_1 = {s1->ptr, s1->__length};
	StringRef ref_2 = {s2->ptr, s2->__length};
	return StringRef_equals(ref_1, ref_2);
}

/// @brief Compares two StringRefs lexicographically
/// @param s1 First StringRef to compare
/// @param s2 Second StringRef to compare
/// @return 0 if equal, negative if s1 < s2, positive if s1 > s2
int32_t StringRef_compare(StringRef s1, StringRef s2) {
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
/// @param s1 First KilnString to compare
/// @param s2 Second KilnString to compare
/// @return 0 if equal, negative if s1 < s2, positive if s1 > s2
inline int32_t KilnString_compare(const KilnString* s1, const KilnString* s2) {
    StringRef r1 = {s1->ptr, s1->__length};
    StringRef r2 = {s2->ptr, s2->__length};
    return StringRef_compare(r1, r2);
}

/// @brief Converts ASCII characters in a KilnString to lowercase, ignoring non-ASCII characters
/// @param string The KilnString to convert
void KilnString_to_ascii_lower(KilnString* string) {
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

/// @brief Converts ASCII characters in a KilnString to uppercase, ignoring non-ASCII characters
/// @param string The KilnString to convert
void KilnString_to_ascii_upper(KilnString* string) {
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

/// @brief Converts a KilnString to uppercase, handling both ASCII and basic Unicode
/// @param string The KilnString to convert to uppercase
void KilnString_to_unicode_upper(KilnString* string) {
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

/// @brief Converts a KilnString to lowercase, handling both ASCII and basic Unicode
/// @param string The KilnString to convert to lowercase
void KilnString_to_unicode_lower(KilnString* string) {
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

/// @brief Removes whitespace from the beginning and end of a KilnString in place
/// @param string The KilnString to trim
void KilnString_trim_inplace(KilnString* string) {
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

/// @brief Returns a new StringRef with whitespace removed from beginning and end
/// @param string The StringRef to trim
/// @return A new StringRef pointing to the trimmed portion of the original string
StringRef StringRef_trim(StringRef string) {
    StringRef result = {NULL, 0};
    
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
StringRef KilnString_trim(const KilnString* string) {
	StringRef ref = {string->ptr, string->__length};
	return StringRef_trim(ref);
}


/// @brief Replaces all instances of old_s with new_s
/// @param string 
/// @param old_s
/// @param new_s
void KilnString_replace(KilnString* string, const char* old_s, const char* new_s) {   
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
/// @param string The StringRef to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
int64_t StringRef_find(StringRef string, const char* target) {
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
/// @param string The StringRef to search in
/// @param target The string to search for
/// @return The position of the last occurrence, or -1 if not found
int64_t StringRef_rfind(StringRef string, const char* target) {
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
/// @param string The KilnString to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
inline int64_t KilnString_find(const KilnString* string, const char* target) {
    StringRef ref = {string->ptr, string->__length};
    return StringRef_find(ref, target);
}

/// @brief Returns the index of the first character of the last occurance of `target` in a KilnString. 
/// @param string The KilnString to search in
/// @param target The substring to find
/// @return Returns `-1` if target is not in `string`
inline int64_t KilnString_rfind(const KilnString* string, const char* target) {
    StringRef ref = {string->ptr, string->__length};
    return StringRef_rfind(ref, target);
}


/// @brief Partitions a StringRef into two parts based on the first occurrence of a delimiter
/// @param string The StringRef to be partitioned
/// @param delimiter The delimiter string to search for
/// @param output_buffer Array of 2 StringRefs to store the results - first part before delimiter, second part after delimiter
void StringRef_partition(StringRef string, const char* delimiter, StringRef output_buffer[2]) {
    // Find the first occurrence of the delimiter
    int64_t delimiter_pos = StringRef_find(string, delimiter);
    
    if (delimiter_pos == -1) {
        // Delimiter not found, first part is the entire string, second part is empty
        output_buffer[0] = string;
        output_buffer[1] = (StringRef){ .ptr = string.ptr + string.__length, .__length = 0 };
    } else {
        // Delimiter found, split the string into two parts
        // First part: from start to delimiter
        output_buffer[0] = (StringRef) {
            .ptr = string.ptr,
            .__length = delimiter_pos
        };
        
        // Second part: after delimiter to end
        size_t delimiter_len = strlen(delimiter);
        output_buffer[1] = (StringRef){
            .ptr = string.ptr + delimiter_pos + delimiter_len,
            .__length = string.__length - delimiter_pos - delimiter_len
        };
    }
}

/// @brief Partitions a StringRef into two parts based on the last occurrence of a delimiter
/// @param string The StringRef to be partitioned
/// @param delimiter The delimiter string to search for from the end
/// @param output_buffer Array of 2 StringRefs to store the results - first part before last delimiter, second part after last delimiter
void StringRef_rpartition(StringRef string, const char* delimiter, StringRef output_buffer[2]) {
    // Find the last occurrence of the delimiter
    int64_t delimiter_pos = StringRef_rfind(string, delimiter);
    
    if (delimiter_pos == -1) {
        // Delimiter not found, first part is the entire string, second part is empty
        output_buffer[0] = string;
        output_buffer[1] = (StringRef){ .ptr = string.ptr + string.__length, .__length = 0 };
    } else {
        // Delimiter found, split the string into two parts
        // First part: from start to last delimiter
        output_buffer[0] = (StringRef){
            .ptr = string.ptr,
            .__length = delimiter_pos
        };
        
        // Second part: after last delimiter to end
        size_t delimiter_len = strlen(delimiter);
        output_buffer[1] = (StringRef){
            .ptr = string.ptr + delimiter_pos + delimiter_len,
            .__length = string.__length - delimiter_pos - delimiter_len
        };
    }
}

/// @brief Partitions a KilnString into two parts based on the first occurrence of a delimiter
/// @param string The StringRef to be partitioned
/// @param delimiter The delimiter string to search for
/// @param output_buffer Array of 2 StringRefs to store the results - first part before delimiter, second part after delimiter
inline void KilnString_partition(const KilnString* string, const char* delimiter, StringRef output_buffer[2]) {
    StringRef ref = {string->ptr, string->__length};
    StringRef_partition(ref, delimiter, output_buffer);
}

/// @brief Partitions a KilnString into two parts based on the last occurrence of a delimiter
/// @param string The StringRef to be partitioned
/// @param delimiter The delimiter string to search for from the end
/// @param output_buffer Array of 2 StringRefs to store the results - first part before last delimiter, second part after last delimiter
inline void KilnString_rpartition(const KilnString* string, const char* delimiter, StringRef output_buffer[2]) {
    StringRef ref = {string->ptr, string->__length};
    StringRef_rpartition(ref, delimiter, output_buffer);
}
