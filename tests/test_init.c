#include "../include/kiln_string.h"

#include <stdio.h>
#include <assert.h>

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test kiln_string_from_cstr
void test_kiln_string_from_cstr() {
    const char* test_str = "Hello, Kiln!";
    kiln_string_t kstr = kiln_string_from_cstr(test_str);
    
    assert(kstr.ptr != NULL);
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(kstr.__length == strlen(test_str));
    assert(kstr.__capacity >= kstr.__length);
    
    kiln_string_free(&kstr);
}

// Test kiln_string_from_kstring_ref
void test_kiln_string_from_kstring_ref() {
    const char* test_str = "Hello, from StringRef!";
    kstring_ref_t sr = kstring_ref_from_cstr(test_str);
    
    kiln_string_t kstr = kiln_string_from_kstring_ref(sr);
    
    assert(kstr.ptr != NULL);
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(kstr.__length == sr.__length);
    assert(kstr.__capacity >= kstr.__length);
    
    kiln_string_free(&kstr);
}

// Test kstring_ref_to_kiln_string (alias of kiln_string_from_kstring_ref)
void test_string_ref_to_kiln_string() {
    const char* test_str = "Convert me to KilnString!";
    kstring_ref_t sr = kstring_ref_from_cstr(test_str);
    
    kiln_string_t kstr = kstring_ref_to_kiln_string(sr);
    
    assert(kstr.ptr != NULL);
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(kstr.__length == sr.__length);
    assert(kstr.__capacity >= kstr.__length);
    
    kiln_string_free(&kstr);
}

// Test kiln_string_to_kstring_ref
void test_kiln_string_to_kstring_ref() {
    const char* test_str = "Extract kstring_ref_t from me!";
    kiln_string_t kstr = kiln_string_from_cstr(test_str);
    
    kstring_ref_t sr = kiln_string_to_kstring_ref(&kstr);
    
    assert(sr.ptr == kstr.ptr);
    assert(sr.__length == kstr.__length);
    
    kiln_string_free(&kstr);
}

// Test kstring_ref_from_kiln_string (alias of kiln_string_to_kstring_ref)
void test_string_ref_from_kiln_str() {
    const char* test_str = "Get kstring_ref_t from KilnString!";
    kiln_string_t kstr = kiln_string_from_cstr(test_str);
    
    kstring_ref_t sr = kstring_ref_from_kiln_string(&kstr);
    
    assert(sr.ptr == kstr.ptr);
    assert(sr.__length == kstr.__length);
    
    kiln_string_free(&kstr);
}

// Test kstring_ref_from_cstr
void test_string_ref_from_cstr() {
    const char* test_str = "Plain C string here!";
    
    kstring_ref_t sr = kstring_ref_from_cstr(test_str);
    
    assert(sr.ptr != NULL);
    assert(sr.ptr == test_str); // Should reference the same memory
    assert(sr.__length == strlen(test_str));
}

// Test kiln_string_free
void test_kiln_string_free() {
    const char* test_str = "Free this string!";
    kiln_string_t kstr = kiln_string_from_cstr(test_str);
    
    kiln_string_free(&kstr);    
    assert(kstr.ptr == NULL);
}

// Test edge cases

// Test with empty string
void test_empty_string() {
    // Empty C string
    kiln_string_t kstr1 = kiln_string_from_cstr("");
    assert(kstr1.ptr != NULL);
    assert(kstr1.ptr[0] == '\0');
    assert(kstr1.__length == 0);
    assert(kstr1.__capacity >= 0);
    
    // Empty StringRef
    kstring_ref_t sr = kstring_ref_from_cstr("");
    kiln_string_t kstr2 = kiln_string_from_kstring_ref(sr);
    assert(kstr2.ptr != NULL);
    assert(kstr2.ptr[0] == '\0');
    assert(kstr2.__length == 0);
    assert(kstr2.__capacity >= 0);
    
    kiln_string_free(&kstr1);
    kiln_string_free(&kstr2);
}

// Integration test that combines multiple operations
void test_combined_operations() {
    const char* test_str = "Test string for combined operations";
    
    // Create a kiln_string_t from a C string
    kiln_string_t kstr = kiln_string_from_cstr(test_str);
    
    // Convert it to a StringRef
    kstring_ref_t sr1 = kiln_string_to_kstring_ref(&kstr);
    
    // Convert kstring_ref_t back to KilnString
    kiln_string_t kstr2 = kstring_ref_to_kiln_string(sr1);
    
    // Create another kstring_ref_t from the second KilnString
    kstring_ref_t sr2 = kstring_ref_from_kiln_string(&kstr2);
    
    // Verify all the conversions maintained the string content
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(sr1.ptr == kstr.ptr);
    assert(strcmp(kstr2.ptr, test_str) == 0);
    assert(sr2.ptr == kstr2.ptr);
    
    // Clean up
    kiln_string_free(&kstr);
    kiln_string_free(&kstr2);
}

int main() {
    printf("=== kiln_string_t Instantiation/Conversion Tests ===\n");
    
    // Run all tests
    run_test("kiln_string_from_cstr", test_kiln_string_from_cstr);
    run_test("kiln_string_from_kstring_ref", test_kiln_string_from_kstring_ref);
    run_test("kstring_ref_to_kiln_string", test_string_ref_to_kiln_string);
    run_test("kiln_string_to_kstring_ref", test_kiln_string_to_kstring_ref);
    run_test("kstring_ref_from_kiln_string", test_string_ref_from_kiln_str);
    run_test("kstring_ref_from_cstr", test_string_ref_from_cstr);
    run_test("kiln_string_free", test_kiln_string_free);
    run_test("Empty string handling", test_empty_string);
    run_test("Combined operations", test_combined_operations);
    
    return 0;
}