#include <stdio.h>
#include <assert.h>
#include "../include/kiln_string.h"

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test kstring_ref_equals_cstr
void test_stringref_equals_cstr() {
    // Create test strings
    const char* cstr1 = "Hello, world!";
    kstring_ref_t sr1 = kstring_ref_from_cstr(cstr1);
    
    // Test exact equality
    assert(kstring_ref_equals_cstr(sr1, "Hello, world!") == true);
    
    // Test inequality
    assert(kstring_ref_equals_cstr(sr1, "hello, world!") == false); // Different case
    assert(kstring_ref_equals_cstr(sr1, "Hello, World!") == false); // Different case
    assert(kstring_ref_equals_cstr(sr1, "Hello, world") == false);  // Missing char
    assert(kstring_ref_equals_cstr(sr1, "Hello, world!.") == false); // Extra char
    assert(kstring_ref_equals_cstr(sr1, "") == false);              // Empty string
    
    // Test with empty StringRef
    kstring_ref_t empty_ref = kstring_ref_from_cstr("");
    assert(kstring_ref_equals_cstr(empty_ref, "") == true);
    assert(kstring_ref_equals_cstr(empty_ref, "x") == false);
}

// Test kstring_ref_equals
void test_stringref_equals() {
    // Create test strings
    const char* cstr1 = "Hello, world!";
    const char* cstr2 = "Hello, world!";
    const char* cstr3 = "Different text";
    
    kstring_ref_t sr1 = kstring_ref_from_cstr(cstr1);
    kstring_ref_t sr2 = kstring_ref_from_cstr(cstr2);
    kstring_ref_t sr3 = kstring_ref_from_cstr(cstr3);
    
    // Test equality
    assert(kstring_ref_equals(sr1, sr2) == true);
    assert(kstring_ref_equals(sr1, sr1) == true); // Same reference
    
    // Test inequality
    assert(kstring_ref_equals(sr1, sr3) == false);
    
    // Test with empty StringRefs
    kstring_ref_t empty_ref1 = kstring_ref_from_cstr("");
    kstring_ref_t empty_ref2 = kstring_ref_from_cstr("");
    assert(kstring_ref_equals(empty_ref1, empty_ref2) == true);
    assert(kstring_ref_equals(empty_ref1, sr1) == false);
    
    // Test with substring
    kiln_string_t kstr = kiln_string_from_cstr("Hello, world! Extra text.");
    kstring_ref_t sub_ref = kiln_string_substring(&kstr, 0, 13); // "Hello, world!"
    assert(kstring_ref_equals(sr1, sub_ref) == true);
    
    kiln_string_free(&kstr);
}

// Test kiln_string_equals_cstr
void test_kilnstring_equals_cstr() {
    // Create test strings
    kiln_string_t kstr1 = kiln_string_from_cstr("Hello, world!");
    
    // Test exact equality
    assert(kiln_string_equals_cstr(&kstr1, "Hello, world!") == true);
    
    // Test inequality
    assert(kiln_string_equals_cstr(&kstr1, "hello, world!") == false); // Different case
    assert(kiln_string_equals_cstr(&kstr1, "Hello, World!") == false); // Different case
    assert(kiln_string_equals_cstr(&kstr1, "Hello, world") == false);  // Missing char
    assert(kiln_string_equals_cstr(&kstr1, "Hello, world!.") == false); // Extra char
    assert(kiln_string_equals_cstr(&kstr1, "") == false);              // Empty string
    
    // Test with empty KilnString
    kiln_string_t empty_kstr = kiln_string_from_cstr("");
    assert(kiln_string_equals_cstr(&empty_kstr, "") == true);
    assert(kiln_string_equals_cstr(&empty_kstr, "x") == false);
    
    kiln_string_free(&kstr1);
    kiln_string_free(&empty_kstr);
}

// Test kiln_string_equals
void test_kilnstring_equals() {
    // Create test strings
    kiln_string_t kstr1 = kiln_string_from_cstr("Hello, world!");
    kiln_string_t kstr2 = kiln_string_from_cstr("Hello, world!");
    kiln_string_t kstr3 = kiln_string_from_cstr("Different text");
    
    // Test equality
    assert(kiln_string_equals(&kstr1, &kstr2) == true);
    assert(kiln_string_equals(&kstr1, &kstr1) == true); // Same reference
    
    // Test inequality
    assert(kiln_string_equals(&kstr1, &kstr3) == false);
    
    // Test with empty KilnStrings
    kiln_string_t empty_kstr1 = kiln_string_from_cstr("");
    kiln_string_t empty_kstr2 = kiln_string_from_cstr("");
    assert(kiln_string_equals(&empty_kstr1, &empty_kstr2) == true);
    assert(kiln_string_equals(&empty_kstr1, &kstr1) == false);
    
    // Test after modification
    kiln_string_push_cstr(&kstr2, " Extra text.");
    assert(kiln_string_equals(&kstr1, &kstr2) == false);
    
    kiln_string_free(&kstr1);
    kiln_string_free(&kstr2);
    kiln_string_free(&kstr3);
    kiln_string_free(&empty_kstr1);
    kiln_string_free(&empty_kstr2);
}

// Test kstring_ref_compare
void test_stringref_compare() {
    // Create test strings for comparison
    kstring_ref_t sr_a = kstring_ref_from_cstr("aaa");
    kstring_ref_t sr_b = kstring_ref_from_cstr("bbb");
    kstring_ref_t sr_a2 = kstring_ref_from_cstr("aaa");
    kstring_ref_t sr_empty = kstring_ref_from_cstr("");
    
    // Test equality (should return 0)
    assert(kstring_ref_compare(sr_a, sr_a2) == 0);
    
    // Test less than (should return negative)
    assert(kstring_ref_compare(sr_a, sr_b) < 0);
    
    // Test greater than (should return positive)
    assert(kstring_ref_compare(sr_b, sr_a) > 0);
    
    // Test with empty string
    assert(kstring_ref_compare(sr_empty, sr_empty) == 0);
    assert(kstring_ref_compare(sr_empty, sr_a) < 0);
    assert(kstring_ref_compare(sr_a, sr_empty) > 0);
    
    // Test different length but common prefix
    kstring_ref_t sr_abc = kstring_ref_from_cstr("abc");
    kstring_ref_t sr_ab = kstring_ref_from_cstr("ab");
    assert(kstring_ref_compare(sr_ab, sr_abc) < 0);
    assert(kstring_ref_compare(sr_abc, sr_ab) > 0);
    
    // Test case sensitivity
    kstring_ref_t sr_A = kstring_ref_from_cstr("AAA");
    assert(kstring_ref_compare(sr_a, sr_A) > 0); // 'a' > 'A' in ASCII
}

// Test kiln_string_compare
void test_kilnstring_compare() {
    // Create test strings for comparison
    kiln_string_t kstr_a = kiln_string_from_cstr("aaa");
    kiln_string_t kstr_b = kiln_string_from_cstr("bbb");
    kiln_string_t kstr_a2 = kiln_string_from_cstr("aaa");
    kiln_string_t kstr_empty = kiln_string_from_cstr("");
    
    // Test equality (should return 0)
    assert(kiln_string_compare(&kstr_a, &kstr_a2) == 0);
    
    // Test less than (should return negative)
    assert(kiln_string_compare(&kstr_a, &kstr_b) < 0);
    
    // Test greater than (should return positive)
    assert(kiln_string_compare(&kstr_b, &kstr_a) > 0);
    
    // Test with empty string
    assert(kiln_string_compare(&kstr_empty, &kstr_empty) == 0);
    assert(kiln_string_compare(&kstr_empty, &kstr_a) < 0);
    assert(kiln_string_compare(&kstr_a, &kstr_empty) > 0);
    
    // Test different length but common prefix
    kiln_string_t kstr_abc = kiln_string_from_cstr("abc");
    kiln_string_t kstr_ab = kiln_string_from_cstr("ab");
    assert(kiln_string_compare(&kstr_ab, &kstr_abc) < 0);
    assert(kiln_string_compare(&kstr_abc, &kstr_ab) > 0);
    
    // Test case sensitivity
    kiln_string_t kstr_A = kiln_string_from_cstr("AAA");
    assert(kiln_string_compare(&kstr_a, &kstr_A) > 0); // 'a' > 'A' in ASCII
    
    kiln_string_free(&kstr_a);
    kiln_string_free(&kstr_b);
    kiln_string_free(&kstr_a2);
    kiln_string_free(&kstr_empty);
    kiln_string_free(&kstr_abc);
    kiln_string_free(&kstr_ab);
    kiln_string_free(&kstr_A);
}

// Test mixing kiln_string_t and kstring_ref_t comparison via conversion
void test_mixed_comparisons() {
    // Create test strings
    kiln_string_t kstr = kiln_string_from_cstr("Test string");
    kstring_ref_t sr = kstring_ref_from_cstr("Test string");
    
    // Convert kiln_string_t to kstring_ref_t for comparison
    kstring_ref_t kstr_as_ref = kiln_string_as_stringref(&kstr);
    
    // Test equality between converted types
    assert(kstring_ref_equals(kstr_as_ref, sr) == true);
    assert(kstring_ref_compare(kstr_as_ref, sr) == 0);
    
    // Test kiln_string_t equals with kstring_ref_t conversion
    kiln_string_t sr_as_kstr = kstring_ref_to_kiln_string(sr);
    assert(kiln_string_equals(&kstr, &sr_as_kstr) == true);
    
    kiln_string_free(&kstr);
    kiln_string_free(&sr_as_kstr);
}

// Test edge cases for string comparison
void test_comparison_edge_cases() {
    // Test strings with special characters
    kiln_string_t kstr_special1 = kiln_string_from_cstr("!@#$%^&*()");
    kiln_string_t kstr_special2 = kiln_string_from_cstr("!@#$%^&*()");
    assert(kiln_string_equals(&kstr_special1, &kstr_special2) == true);
    assert(kiln_string_compare(&kstr_special1, &kstr_special2) == 0);
    
    // Test strings with whitespace
    kstring_ref_t sr_space1 = kstring_ref_from_cstr("  Hello  ");
    kstring_ref_t sr_space2 = kstring_ref_from_cstr("  Hello  ");
    kstring_ref_t sr_space3 = kstring_ref_from_cstr("  Hello"); // Different
    assert(kstring_ref_equals(sr_space1, sr_space2) == true);
    assert(kstring_ref_equals(sr_space1, sr_space3) == false);
    
    // Test strings of different lengths
    kiln_string_t kstr_long = kiln_string_from_cstr("This is a longer string");
    kiln_string_t kstr_short = kiln_string_from_cstr("Short");
    assert(kiln_string_equals(&kstr_long, &kstr_short) == false);
    assert(kiln_string_compare(&kstr_long, &kstr_short) != 0);
    
    // Test with numeric content
    kstring_ref_t sr_num1 = kstring_ref_from_cstr("12345");
    kstring_ref_t sr_num2 = kstring_ref_from_cstr("12345");
    kstring_ref_t sr_num3 = kstring_ref_from_cstr("123456");
    assert(kstring_ref_equals(sr_num1, sr_num2) == true);
    assert(kstring_ref_equals(sr_num1, sr_num3) == false);
    assert(kstring_ref_compare(sr_num1, sr_num3) < 0);
    
    kiln_string_free(&kstr_special1);
    kiln_string_free(&kstr_special2);
    kiln_string_free(&kstr_long);
    kiln_string_free(&kstr_short);
}

int main() {
    printf("=== kiln_string_t Equality and Comparison Tests ===\n");
    
    // Run all tests
    run_test("kstring_ref_equals_cstr", test_stringref_equals_cstr);
    run_test("kstring_ref_equals", test_stringref_equals);
    run_test("kiln_string_equals_cstr", test_kilnstring_equals_cstr);
    run_test("kiln_string_equals", test_kilnstring_equals);
    run_test("kstring_ref_compare", test_stringref_compare);
    run_test("kiln_string_compare", test_kilnstring_compare);
    run_test("Mixed type comparisons", test_mixed_comparisons);
    run_test("Comparison edge cases", test_comparison_edge_cases);
    
    return 0;
}