#include "../include/kiln_string.h"

#include <stdio.h>
#include <assert.h>

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test KilnString_from_cstr
void test_kiln_string_from_cstr() {
    const char* test_str = "Hello, Kiln!";
    KilnString kstr = KilnString_from_cstr(test_str);
    
    assert(kstr.ptr != NULL);
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(kstr.__length == strlen(test_str));
    assert(kstr.__capacity >= kstr.__length);
    
    KilnString_free(&kstr);
}

// Test KilnString_from_string_ref
void test_kiln_string_from_string_ref() {
    const char* test_str = "Hello, from StringRef!";
    StringRef sr = StringRef_from_cstr(test_str);
    
    KilnString kstr = KilnString_from_string_ref(sr);
    
    assert(kstr.ptr != NULL);
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(kstr.__length == sr.__length);
    assert(kstr.__capacity >= kstr.__length);
    
    KilnString_free(&kstr);
}

// Test StringRef_to_kiln_string (alias of KilnString_from_string_ref)
void test_string_ref_to_kiln_string() {
    const char* test_str = "Convert me to KilnString!";
    StringRef sr = StringRef_from_cstr(test_str);
    
    KilnString kstr = StringRef_to_kiln_string(sr);
    
    assert(kstr.ptr != NULL);
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(kstr.__length == sr.__length);
    assert(kstr.__capacity >= kstr.__length);
    
    KilnString_free(&kstr);
}

// Test KilnString_as_stringref
void test_kiln_string_as_stringref() {
    const char* test_str = "Extract StringRef from me!";
    KilnString kstr = KilnString_from_cstr(test_str);
    
    StringRef sr = KilnString_as_stringref(&kstr);
    
    assert(sr.ptr == kstr.ptr);
    assert(sr.__length == kstr.__length);
    
    KilnString_free(&kstr);
}

// Test StringRef_from_kiln_str (alias of KilnString_as_stringref)
void test_string_ref_from_kiln_str() {
    const char* test_str = "Get StringRef from KilnString!";
    KilnString kstr = KilnString_from_cstr(test_str);
    
    StringRef sr = StringRef_from_kiln_str(&kstr);
    
    assert(sr.ptr == kstr.ptr);
    assert(sr.__length == kstr.__length);
    
    KilnString_free(&kstr);
}

// Test StringRef_from_cstr
void test_string_ref_from_cstr() {
    const char* test_str = "Plain C string here!";
    
    StringRef sr = StringRef_from_cstr(test_str);
    
    assert(sr.ptr != NULL);
    assert(sr.ptr == test_str); // Should reference the same memory
    assert(sr.__length == strlen(test_str));
}

// Test KilnString_free
void test_kiln_string_free() {
    const char* test_str = "Free this string!";
    KilnString kstr = KilnString_from_cstr(test_str);
    
    KilnString_free(&kstr);    
    assert(kstr.ptr == NULL);
}

// Test edge cases

// Test with empty string
void test_empty_string() {
    // Empty C string
    KilnString kstr1 = KilnString_from_cstr("");
    assert(kstr1.ptr != NULL);
    assert(kstr1.ptr[0] == '\0');
    assert(kstr1.__length == 0);
    assert(kstr1.__capacity >= 0);
    
    // Empty StringRef
    StringRef sr = StringRef_from_cstr("");
    KilnString kstr2 = KilnString_from_string_ref(sr);
    assert(kstr2.ptr != NULL);
    assert(kstr2.ptr[0] == '\0');
    assert(kstr2.__length == 0);
    assert(kstr2.__capacity >= 0);
    
    KilnString_free(&kstr1);
    KilnString_free(&kstr2);
}

// Integration test that combines multiple operations
void test_combined_operations() {
    const char* test_str = "Test string for combined operations";
    
    // Create a KilnString from a C string
    KilnString kstr = KilnString_from_cstr(test_str);
    
    // Convert it to a StringRef
    StringRef sr1 = KilnString_as_stringref(&kstr);
    
    // Convert StringRef back to KilnString
    KilnString kstr2 = StringRef_to_kiln_string(sr1);
    
    // Create another StringRef from the second KilnString
    StringRef sr2 = StringRef_from_kiln_str(&kstr2);
    
    // Verify all the conversions maintained the string content
    assert(strcmp(kstr.ptr, test_str) == 0);
    assert(sr1.ptr == kstr.ptr);
    assert(strcmp(kstr2.ptr, test_str) == 0);
    assert(sr2.ptr == kstr2.ptr);
    
    // Clean up
    KilnString_free(&kstr);
    KilnString_free(&kstr2);
}

int main() {
    printf("=== KilnString Instantiation/Conversion Tests ===\n");
    
    // Run all tests
    run_test("KilnString_from_cstr", test_kiln_string_from_cstr);
    run_test("KilnString_from_string_ref", test_kiln_string_from_string_ref);
    run_test("StringRef_to_kiln_string", test_string_ref_to_kiln_string);
    run_test("KilnString_as_stringref", test_kiln_string_as_stringref);
    run_test("StringRef_from_kiln_str", test_string_ref_from_kiln_str);
    run_test("StringRef_from_cstr", test_string_ref_from_cstr);
    run_test("KilnString_free", test_kiln_string_free);
    run_test("Empty string handling", test_empty_string);
    run_test("Combined operations", test_combined_operations);
    
    return 0;
}