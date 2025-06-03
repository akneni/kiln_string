#include <stdio.h>
#include <assert.h>
#include "../include/kiln_string.h"

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test StringRef_equals_cstr
void test_stringref_equals_cstr() {
    // Create test strings
    const char* cstr1 = "Hello, world!";
    kstring_ref_t sr1 = StringRef_from_cstr(cstr1);
    
    // Test exact equality
    assert(StringRef_equals_cstr(sr1, "Hello, world!") == true);
    
    // Test inequality
    assert(StringRef_equals_cstr(sr1, "hello, world!") == false); // Different case
    assert(StringRef_equals_cstr(sr1, "Hello, World!") == false); // Different case
    assert(StringRef_equals_cstr(sr1, "Hello, world") == false);  // Missing char
    assert(StringRef_equals_cstr(sr1, "Hello, world!.") == false); // Extra char
    assert(StringRef_equals_cstr(sr1, "") == false);              // Empty string
    
    // Test with empty StringRef
    kstring_ref_t empty_ref = StringRef_from_cstr("");
    assert(StringRef_equals_cstr(empty_ref, "") == true);
    assert(StringRef_equals_cstr(empty_ref, "x") == false);
}

// Test StringRef_equals
void test_stringref_equals() {
    // Create test strings
    const char* cstr1 = "Hello, world!";
    const char* cstr2 = "Hello, world!";
    const char* cstr3 = "Different text";
    
    kstring_ref_t sr1 = StringRef_from_cstr(cstr1);
    kstring_ref_t sr2 = StringRef_from_cstr(cstr2);
    kstring_ref_t sr3 = StringRef_from_cstr(cstr3);
    
    // Test equality
    assert(StringRef_equals(sr1, sr2) == true);
    assert(StringRef_equals(sr1, sr1) == true); // Same reference
    
    // Test inequality
    assert(StringRef_equals(sr1, sr3) == false);
    
    // Test with empty StringRefs
    kstring_ref_t empty_ref1 = StringRef_from_cstr("");
    kstring_ref_t empty_ref2 = StringRef_from_cstr("");
    assert(StringRef_equals(empty_ref1, empty_ref2) == true);
    assert(StringRef_equals(empty_ref1, sr1) == false);
    
    // Test with substring
    kiln_string_t kstr = KilnString_from_cstr("Hello, world! Extra text.");
    kstring_ref_t sub_ref = KilnString_substring(&kstr, 0, 13); // "Hello, world!"
    assert(StringRef_equals(sr1, sub_ref) == true);
    
    KilnString_free(&kstr);
}

// Test KilnString_equals_cstr
void test_kilnstring_equals_cstr() {
    // Create test strings
    kiln_string_t kstr1 = KilnString_from_cstr("Hello, world!");
    
    // Test exact equality
    assert(KilnString_equals_cstr(&kstr1, "Hello, world!") == true);
    
    // Test inequality
    assert(KilnString_equals_cstr(&kstr1, "hello, world!") == false); // Different case
    assert(KilnString_equals_cstr(&kstr1, "Hello, World!") == false); // Different case
    assert(KilnString_equals_cstr(&kstr1, "Hello, world") == false);  // Missing char
    assert(KilnString_equals_cstr(&kstr1, "Hello, world!.") == false); // Extra char
    assert(KilnString_equals_cstr(&kstr1, "") == false);              // Empty string
    
    // Test with empty KilnString
    kiln_string_t empty_kstr = KilnString_from_cstr("");
    assert(KilnString_equals_cstr(&empty_kstr, "") == true);
    assert(KilnString_equals_cstr(&empty_kstr, "x") == false);
    
    KilnString_free(&kstr1);
    KilnString_free(&empty_kstr);
}

// Test KilnString_equals
void test_kilnstring_equals() {
    // Create test strings
    kiln_string_t kstr1 = KilnString_from_cstr("Hello, world!");
    kiln_string_t kstr2 = KilnString_from_cstr("Hello, world!");
    kiln_string_t kstr3 = KilnString_from_cstr("Different text");
    
    // Test equality
    assert(KilnString_equals(&kstr1, &kstr2) == true);
    assert(KilnString_equals(&kstr1, &kstr1) == true); // Same reference
    
    // Test inequality
    assert(KilnString_equals(&kstr1, &kstr3) == false);
    
    // Test with empty KilnStrings
    kiln_string_t empty_kstr1 = KilnString_from_cstr("");
    kiln_string_t empty_kstr2 = KilnString_from_cstr("");
    assert(KilnString_equals(&empty_kstr1, &empty_kstr2) == true);
    assert(KilnString_equals(&empty_kstr1, &kstr1) == false);
    
    // Test after modification
    KilnString_push_cstr(&kstr2, " Extra text.");
    assert(KilnString_equals(&kstr1, &kstr2) == false);
    
    KilnString_free(&kstr1);
    KilnString_free(&kstr2);
    KilnString_free(&kstr3);
    KilnString_free(&empty_kstr1);
    KilnString_free(&empty_kstr2);
}

// Test StringRef_compare
void test_stringref_compare() {
    // Create test strings for comparison
    kstring_ref_t sr_a = StringRef_from_cstr("aaa");
    kstring_ref_t sr_b = StringRef_from_cstr("bbb");
    kstring_ref_t sr_a2 = StringRef_from_cstr("aaa");
    kstring_ref_t sr_empty = StringRef_from_cstr("");
    
    // Test equality (should return 0)
    assert(StringRef_compare(sr_a, sr_a2) == 0);
    
    // Test less than (should return negative)
    assert(StringRef_compare(sr_a, sr_b) < 0);
    
    // Test greater than (should return positive)
    assert(StringRef_compare(sr_b, sr_a) > 0);
    
    // Test with empty string
    assert(StringRef_compare(sr_empty, sr_empty) == 0);
    assert(StringRef_compare(sr_empty, sr_a) < 0);
    assert(StringRef_compare(sr_a, sr_empty) > 0);
    
    // Test different length but common prefix
    kstring_ref_t sr_abc = StringRef_from_cstr("abc");
    kstring_ref_t sr_ab = StringRef_from_cstr("ab");
    assert(StringRef_compare(sr_ab, sr_abc) < 0);
    assert(StringRef_compare(sr_abc, sr_ab) > 0);
    
    // Test case sensitivity
    kstring_ref_t sr_A = StringRef_from_cstr("AAA");
    assert(StringRef_compare(sr_a, sr_A) > 0); // 'a' > 'A' in ASCII
}

// Test KilnString_compare
void test_kilnstring_compare() {
    // Create test strings for comparison
    kiln_string_t kstr_a = KilnString_from_cstr("aaa");
    kiln_string_t kstr_b = KilnString_from_cstr("bbb");
    kiln_string_t kstr_a2 = KilnString_from_cstr("aaa");
    kiln_string_t kstr_empty = KilnString_from_cstr("");
    
    // Test equality (should return 0)
    assert(KilnString_compare(&kstr_a, &kstr_a2) == 0);
    
    // Test less than (should return negative)
    assert(KilnString_compare(&kstr_a, &kstr_b) < 0);
    
    // Test greater than (should return positive)
    assert(KilnString_compare(&kstr_b, &kstr_a) > 0);
    
    // Test with empty string
    assert(KilnString_compare(&kstr_empty, &kstr_empty) == 0);
    assert(KilnString_compare(&kstr_empty, &kstr_a) < 0);
    assert(KilnString_compare(&kstr_a, &kstr_empty) > 0);
    
    // Test different length but common prefix
    kiln_string_t kstr_abc = KilnString_from_cstr("abc");
    kiln_string_t kstr_ab = KilnString_from_cstr("ab");
    assert(KilnString_compare(&kstr_ab, &kstr_abc) < 0);
    assert(KilnString_compare(&kstr_abc, &kstr_ab) > 0);
    
    // Test case sensitivity
    kiln_string_t kstr_A = KilnString_from_cstr("AAA");
    assert(KilnString_compare(&kstr_a, &kstr_A) > 0); // 'a' > 'A' in ASCII
    
    KilnString_free(&kstr_a);
    KilnString_free(&kstr_b);
    KilnString_free(&kstr_a2);
    KilnString_free(&kstr_empty);
    KilnString_free(&kstr_abc);
    KilnString_free(&kstr_ab);
    KilnString_free(&kstr_A);
}

// Test mixing kiln_string_t and kstring_ref_t comparison via conversion
void test_mixed_comparisons() {
    // Create test strings
    kiln_string_t kstr = KilnString_from_cstr("Test string");
    kstring_ref_t sr = StringRef_from_cstr("Test string");
    
    // Convert kiln_string_t to kstring_ref_t for comparison
    kstring_ref_t kstr_as_ref = KilnString_as_stringref(&kstr);
    
    // Test equality between converted types
    assert(StringRef_equals(kstr_as_ref, sr) == true);
    assert(StringRef_compare(kstr_as_ref, sr) == 0);
    
    // Test kiln_string_t equals with kstring_ref_t conversion
    kiln_string_t sr_as_kstr = StringRef_to_kiln_string(sr);
    assert(KilnString_equals(&kstr, &sr_as_kstr) == true);
    
    KilnString_free(&kstr);
    KilnString_free(&sr_as_kstr);
}

// Test edge cases for string comparison
void test_comparison_edge_cases() {
    // Test strings with special characters
    kiln_string_t kstr_special1 = KilnString_from_cstr("!@#$%^&*()");
    kiln_string_t kstr_special2 = KilnString_from_cstr("!@#$%^&*()");
    assert(KilnString_equals(&kstr_special1, &kstr_special2) == true);
    assert(KilnString_compare(&kstr_special1, &kstr_special2) == 0);
    
    // Test strings with whitespace
    kstring_ref_t sr_space1 = StringRef_from_cstr("  Hello  ");
    kstring_ref_t sr_space2 = StringRef_from_cstr("  Hello  ");
    kstring_ref_t sr_space3 = StringRef_from_cstr("  Hello"); // Different
    assert(StringRef_equals(sr_space1, sr_space2) == true);
    assert(StringRef_equals(sr_space1, sr_space3) == false);
    
    // Test strings of different lengths
    kiln_string_t kstr_long = KilnString_from_cstr("This is a longer string");
    kiln_string_t kstr_short = KilnString_from_cstr("Short");
    assert(KilnString_equals(&kstr_long, &kstr_short) == false);
    assert(KilnString_compare(&kstr_long, &kstr_short) != 0);
    
    // Test with numeric content
    kstring_ref_t sr_num1 = StringRef_from_cstr("12345");
    kstring_ref_t sr_num2 = StringRef_from_cstr("12345");
    kstring_ref_t sr_num3 = StringRef_from_cstr("123456");
    assert(StringRef_equals(sr_num1, sr_num2) == true);
    assert(StringRef_equals(sr_num1, sr_num3) == false);
    assert(StringRef_compare(sr_num1, sr_num3) < 0);
    
    KilnString_free(&kstr_special1);
    KilnString_free(&kstr_special2);
    KilnString_free(&kstr_long);
    KilnString_free(&kstr_short);
}

int main() {
    printf("=== kiln_string_t Equality and Comparison Tests ===\n");
    
    // Run all tests
    run_test("StringRef_equals_cstr", test_stringref_equals_cstr);
    run_test("StringRef_equals", test_stringref_equals);
    run_test("KilnString_equals_cstr", test_kilnstring_equals_cstr);
    run_test("KilnString_equals", test_kilnstring_equals);
    run_test("StringRef_compare", test_stringref_compare);
    run_test("KilnString_compare", test_kilnstring_compare);
    run_test("Mixed type comparisons", test_mixed_comparisons);
    run_test("Comparison edge cases", test_comparison_edge_cases);
    
    return 0;
}