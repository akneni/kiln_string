#include <stdio.h>
#include <assert.h>
#include "../include/kiln_string.h"

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test kiln_string_starts_with
void test_kiln_string_starts_with() {
    // Create test strings
    kiln_string_t kstr = kiln_string_from_cstr("Hello, world!");
    
    // Test various prefixes
    assert(kiln_string_starts_with(&kstr, "Hello") == true);
    assert(kiln_string_starts_with(&kstr, "H") == true);
    assert(kiln_string_starts_with(&kstr, "Hello, world!") == true);
    assert(kiln_string_starts_with(&kstr, "") == true); // Empty prefix always matches
    
    // Test non-matching prefixes
    assert(kiln_string_starts_with(&kstr, "hello") == false); // Case sensitivity
    assert(kiln_string_starts_with(&kstr, "world") == false);
    assert(kiln_string_starts_with(&kstr, "Hello, world!!") == false); // Longer than string
    
    kiln_string_free(&kstr);
}

// Test kiln_string_ends_with
void test_kiln_string_ends_with() {
    // Create test strings
    kiln_string_t kstr = kiln_string_from_cstr("Hello, world!");
    
    // Test various suffixes
    assert(kiln_string_ends_with(&kstr, "world!") == true);
    assert(kiln_string_ends_with(&kstr, "!") == true);
    assert(kiln_string_ends_with(&kstr, "Hello, world!") == true);
    assert(kiln_string_ends_with(&kstr, "") == true); // Empty suffix always matches
    
    // Test non-matching suffixes
    assert(kiln_string_ends_with(&kstr, "World!") == false); // Case sensitivity
    assert(kiln_string_ends_with(&kstr, "Hello") == false);
    assert(kiln_string_ends_with(&kstr, "?Hello, world!") == false); // Longer than string
    
    kiln_string_free(&kstr);
}

// Test kstring_ref_starts_with
void test_stringref_starts_with() {
    // Create test strings
    const char* test_str = "Programming in C";
    kstring_ref_t sr = kstring_ref_from_cstr(test_str);
    
    // Test various prefixes
    assert(kstring_ref_starts_with(sr, "Program") == true);
    assert(kstring_ref_starts_with(sr, "P") == true);
    assert(kstring_ref_starts_with(sr, "Programming in C") == true);
    assert(kstring_ref_starts_with(sr, "") == true); // Empty prefix always matches
    
    // Test non-matching prefixes
    assert(kstring_ref_starts_with(sr, "program") == false); // Case sensitivity
    assert(kstring_ref_starts_with(sr, "C") == false);
    assert(kstring_ref_starts_with(sr, "Programming in C++") == false); // Longer than string
}

// Test kstring_ref_ends_with
void test_stringref_ends_with() {
    // Create test strings
    const char* test_str = "Programming in C";
    kstring_ref_t sr = kstring_ref_from_cstr(test_str);
    
    // Test various suffixes
    assert(kstring_ref_ends_with(sr, "in C") == true);
    assert(kstring_ref_ends_with(sr, "C") == true);
    assert(kstring_ref_ends_with(sr, "Programming in C") == true);
    assert(kstring_ref_ends_with(sr, "") == true); // Empty suffix always matches
    
    // Test non-matching suffixes
    assert(kstring_ref_ends_with(sr, "IN C") == false); // Case sensitivity
    assert(kstring_ref_ends_with(sr, "Programming") == false);
    assert(kstring_ref_ends_with(sr, "Advanced Programming in C") == false); // Longer than string
}

// Test with substrings
void test_with_substrings() {
    // Create a KilnString
    kiln_string_t kstr = kiln_string_from_cstr("The quick brown fox jumps over the lazy dog");
    
    // Get a substring as StringRef
    kstring_ref_t sr = kiln_string_substring(&kstr, 4, 19); // "quick brown fox"
    
    // Test prefix/suffix on substring
    assert(kstring_ref_starts_with(sr, "quick") == true);
    assert(kstring_ref_starts_with(sr, "The quick") == false); // Not in substring
    assert(kstring_ref_ends_with(sr, "fox") == true);
    assert(kstring_ref_ends_with(sr, "brown fox jumps") == false); // Beyond substring
    
    kiln_string_free(&kstr);
}

// Test edge cases
void test_edge_cases() {
    // Test with single character
    kiln_string_t single_char = kiln_string_from_cstr("X");
    assert(kiln_string_starts_with(&single_char, "X") == true);
    assert(kiln_string_starts_with(&single_char, "x") == false);
    assert(kiln_string_ends_with(&single_char, "X") == true);
    assert(kiln_string_ends_with(&single_char, "Y") == false);
    kiln_string_free(&single_char);
    
    // Test with empty string
    kiln_string_t empty_str = kiln_string_from_cstr("");
    assert(kiln_string_starts_with(&empty_str, "") == true);
    assert(kiln_string_starts_with(&empty_str, "a") == false);
    assert(kiln_string_ends_with(&empty_str, "") == true);
    assert(kiln_string_ends_with(&empty_str, "a") == false);
    kiln_string_free(&empty_str);
    
    // Test kstring_ref_t with empty string
    kstring_ref_t empty_ref = kstring_ref_from_cstr("");
    assert(kstring_ref_starts_with(empty_ref, "") == true);
    assert(kstring_ref_starts_with(empty_ref, "a") == false);
    assert(kstring_ref_ends_with(empty_ref, "") == true);
    assert(kstring_ref_ends_with(empty_ref, "a") == false);
}

// Test with special characters
void test_special_chars() {
    // Create test string with special characters
    kiln_string_t special = kiln_string_from_cstr("/*-+!@#$%^&*()\\");
    
    // Test prefixes and suffixes with special characters
    assert(kiln_string_starts_with(&special, "/*-") == true);
    assert(kiln_string_ends_with(&special, "()\\") == true);
    
    // Create test string with null characters (note: this requires special handling)
    char null_str[] = {'A', '\0', 'B', 'C', '\0'};
    kiln_string_t null_char = kiln_string_from_cstr(null_str);
    
    // Since we're using C strings with null termination, only 'A' will be visible
    assert(kiln_string_starts_with(&null_char, "A") == true);
    assert(kiln_string_ends_with(&null_char, "A") == true);
    
    kiln_string_free(&special);
    kiln_string_free(&null_char);
}

// Test case sensitivity
void test_case_sensitivity() {
    // Create test string
    kiln_string_t kstr = kiln_string_from_cstr("CamelCaseString");
    kstring_ref_t sr = kiln_string_to_kstring_ref(&kstr);
    
    // Test case sensitivity
    assert(kiln_string_starts_with(&kstr, "Camel") == true);
    assert(kiln_string_starts_with(&kstr, "camel") == false);
    assert(kiln_string_ends_with(&kstr, "String") == true);
    assert(kiln_string_ends_with(&kstr, "string") == false);
    
    assert(kstring_ref_starts_with(sr, "Camel") == true);
    assert(kstring_ref_starts_with(sr, "camel") == false);
    assert(kstring_ref_ends_with(sr, "String") == true);
    assert(kstring_ref_ends_with(sr, "string") == false);
    
    kiln_string_free(&kstr);
}

int main() {
    printf("=== kiln_string_t Prefix/Suffix Tests ===\n");
    
    // Run all tests
    run_test("kiln_string_starts_with", test_kiln_string_starts_with);
    run_test("kiln_string_ends_with", test_kiln_string_ends_with);
    run_test("kstring_ref_starts_with", test_stringref_starts_with);
    run_test("kstring_ref_ends_with", test_stringref_ends_with);
    run_test("With substrings", test_with_substrings);
    run_test("Edge cases", test_edge_cases);
    run_test("Special characters", test_special_chars);
    run_test("Case sensitivity", test_case_sensitivity);
    
    return 0;
}