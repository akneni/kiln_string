#include <stdio.h>
#include <assert.h>
#include "../include/kiln_string.h"

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test KilnString_starts_with
void test_kiln_string_starts_with() {
    // Create test strings
    kiln_string_t kstr = KilnString_from_cstr("Hello, world!");
    
    // Test various prefixes
    assert(KilnString_starts_with(&kstr, "Hello") == true);
    assert(KilnString_starts_with(&kstr, "H") == true);
    assert(KilnString_starts_with(&kstr, "Hello, world!") == true);
    assert(KilnString_starts_with(&kstr, "") == true); // Empty prefix always matches
    
    // Test non-matching prefixes
    assert(KilnString_starts_with(&kstr, "hello") == false); // Case sensitivity
    assert(KilnString_starts_with(&kstr, "world") == false);
    assert(KilnString_starts_with(&kstr, "Hello, world!!") == false); // Longer than string
    
    KilnString_free(&kstr);
}

// Test KilnString_ends_with
void test_kiln_string_ends_with() {
    // Create test strings
    kiln_string_t kstr = KilnString_from_cstr("Hello, world!");
    
    // Test various suffixes
    assert(KilnString_ends_with(&kstr, "world!") == true);
    assert(KilnString_ends_with(&kstr, "!") == true);
    assert(KilnString_ends_with(&kstr, "Hello, world!") == true);
    assert(KilnString_ends_with(&kstr, "") == true); // Empty suffix always matches
    
    // Test non-matching suffixes
    assert(KilnString_ends_with(&kstr, "World!") == false); // Case sensitivity
    assert(KilnString_ends_with(&kstr, "Hello") == false);
    assert(KilnString_ends_with(&kstr, "?Hello, world!") == false); // Longer than string
    
    KilnString_free(&kstr);
}

// Test StringRef_starts_with
void test_stringref_starts_with() {
    // Create test strings
    const char* test_str = "Programming in C";
    kstring_ref_t sr = StringRef_from_cstr(test_str);
    
    // Test various prefixes
    assert(StringRef_starts_with(sr, "Program") == true);
    assert(StringRef_starts_with(sr, "P") == true);
    assert(StringRef_starts_with(sr, "Programming in C") == true);
    assert(StringRef_starts_with(sr, "") == true); // Empty prefix always matches
    
    // Test non-matching prefixes
    assert(StringRef_starts_with(sr, "program") == false); // Case sensitivity
    assert(StringRef_starts_with(sr, "C") == false);
    assert(StringRef_starts_with(sr, "Programming in C++") == false); // Longer than string
}

// Test StringRef_ends_with
void test_stringref_ends_with() {
    // Create test strings
    const char* test_str = "Programming in C";
    kstring_ref_t sr = StringRef_from_cstr(test_str);
    
    // Test various suffixes
    assert(StringRef_ends_with(sr, "in C") == true);
    assert(StringRef_ends_with(sr, "C") == true);
    assert(StringRef_ends_with(sr, "Programming in C") == true);
    assert(StringRef_ends_with(sr, "") == true); // Empty suffix always matches
    
    // Test non-matching suffixes
    assert(StringRef_ends_with(sr, "IN C") == false); // Case sensitivity
    assert(StringRef_ends_with(sr, "Programming") == false);
    assert(StringRef_ends_with(sr, "Advanced Programming in C") == false); // Longer than string
}

// Test with substrings
void test_with_substrings() {
    // Create a KilnString
    kiln_string_t kstr = KilnString_from_cstr("The quick brown fox jumps over the lazy dog");
    
    // Get a substring as StringRef
    kstring_ref_t sr = KilnString_substring(&kstr, 4, 19); // "quick brown fox"
    
    // Test prefix/suffix on substring
    assert(StringRef_starts_with(sr, "quick") == true);
    assert(StringRef_starts_with(sr, "The quick") == false); // Not in substring
    assert(StringRef_ends_with(sr, "fox") == true);
    assert(StringRef_ends_with(sr, "brown fox jumps") == false); // Beyond substring
    
    KilnString_free(&kstr);
}

// Test edge cases
void test_edge_cases() {
    // Test with single character
    kiln_string_t single_char = KilnString_from_cstr("X");
    assert(KilnString_starts_with(&single_char, "X") == true);
    assert(KilnString_starts_with(&single_char, "x") == false);
    assert(KilnString_ends_with(&single_char, "X") == true);
    assert(KilnString_ends_with(&single_char, "Y") == false);
    KilnString_free(&single_char);
    
    // Test with empty string
    kiln_string_t empty_str = KilnString_from_cstr("");
    assert(KilnString_starts_with(&empty_str, "") == true);
    assert(KilnString_starts_with(&empty_str, "a") == false);
    assert(KilnString_ends_with(&empty_str, "") == true);
    assert(KilnString_ends_with(&empty_str, "a") == false);
    KilnString_free(&empty_str);
    
    // Test kstring_ref_t with empty string
    kstring_ref_t empty_ref = StringRef_from_cstr("");
    assert(StringRef_starts_with(empty_ref, "") == true);
    assert(StringRef_starts_with(empty_ref, "a") == false);
    assert(StringRef_ends_with(empty_ref, "") == true);
    assert(StringRef_ends_with(empty_ref, "a") == false);
}

// Test with special characters
void test_special_chars() {
    // Create test string with special characters
    kiln_string_t special = KilnString_from_cstr("/*-+!@#$%^&*()\\");
    
    // Test prefixes and suffixes with special characters
    assert(KilnString_starts_with(&special, "/*-") == true);
    assert(KilnString_ends_with(&special, "()\\") == true);
    
    // Create test string with null characters (note: this requires special handling)
    char null_str[] = {'A', '\0', 'B', 'C', '\0'};
    kiln_string_t null_char = KilnString_from_cstr(null_str);
    
    // Since we're using C strings with null termination, only 'A' will be visible
    assert(KilnString_starts_with(&null_char, "A") == true);
    assert(KilnString_ends_with(&null_char, "A") == true);
    
    KilnString_free(&special);
    KilnString_free(&null_char);
}

// Test case sensitivity
void test_case_sensitivity() {
    // Create test string
    kiln_string_t kstr = KilnString_from_cstr("CamelCaseString");
    kstring_ref_t sr = KilnString_as_stringref(&kstr);
    
    // Test case sensitivity
    assert(KilnString_starts_with(&kstr, "Camel") == true);
    assert(KilnString_starts_with(&kstr, "camel") == false);
    assert(KilnString_ends_with(&kstr, "String") == true);
    assert(KilnString_ends_with(&kstr, "string") == false);
    
    assert(StringRef_starts_with(sr, "Camel") == true);
    assert(StringRef_starts_with(sr, "camel") == false);
    assert(StringRef_ends_with(sr, "String") == true);
    assert(StringRef_ends_with(sr, "string") == false);
    
    KilnString_free(&kstr);
}

int main() {
    printf("=== kiln_string_t Prefix/Suffix Tests ===\n");
    
    // Run all tests
    run_test("KilnString_starts_with", test_kiln_string_starts_with);
    run_test("KilnString_ends_with", test_kiln_string_ends_with);
    run_test("StringRef_starts_with", test_stringref_starts_with);
    run_test("StringRef_ends_with", test_stringref_ends_with);
    run_test("With substrings", test_with_substrings);
    run_test("Edge cases", test_edge_cases);
    run_test("Special characters", test_special_chars);
    run_test("Case sensitivity", test_case_sensitivity);
    
    return 0;
}