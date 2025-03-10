#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/kiln_string.h"

// Test helper function to print test name
void run_test(const char* test_name, void (*test_func)(void)) {
    printf("Running: %s\n", test_name);
    test_func();
    printf("  ✓ PASSED\n");
}

// Test KilnString_to_ascii_lower
void test_kiln_string_to_ascii_lower() {
    // Test with mixed case string
    KilnString mixed = KilnString_from_cstr("HELLO World! 123");
    KilnString_to_ascii_lower(&mixed);
    assert(strcmp(mixed.ptr, "hello world! 123") == 0);
    KilnString_free(&mixed);
    
    // Test with all uppercase
    KilnString upper = KilnString_from_cstr("ALL UPPERCASE TEXT");
    KilnString_to_ascii_lower(&upper);
    assert(strcmp(upper.ptr, "all uppercase text") == 0);
    KilnString_free(&upper);
    
    // Test with all lowercase (should remain unchanged)
    KilnString lower = KilnString_from_cstr("already lowercase");
    KilnString_to_ascii_lower(&lower);
    assert(strcmp(lower.ptr, "already lowercase") == 0);
    KilnString_free(&lower);
    
    // Test with numbers and special characters
    KilnString special = KilnString_from_cstr("12345!@#$%^&*()_+");
    KilnString_to_ascii_lower(&special);
    assert(strcmp(special.ptr, "12345!@#$%^&*()_+") == 0);
    KilnString_free(&special);
    
    // Test with empty string
    KilnString empty = KilnString_from_cstr("");
    KilnString_to_ascii_lower(&empty);
    assert(strcmp(empty.ptr, "") == 0);
    KilnString_free(&empty);
}

// Test KilnString_to_ascii_upper
void test_kiln_string_to_ascii_upper() {
    // Test with mixed case string
    KilnString mixed = KilnString_from_cstr("Hello World! 123");
    KilnString_to_ascii_upper(&mixed);
    assert(strcmp(mixed.ptr, "HELLO WORLD! 123") == 0);
    KilnString_free(&mixed);
    
    // Test with all lowercase
    KilnString lower = KilnString_from_cstr("all lowercase text");
    KilnString_to_ascii_upper(&lower);
    assert(strcmp(lower.ptr, "ALL LOWERCASE TEXT") == 0);
    KilnString_free(&lower);
    
    // Test with all uppercase (should remain unchanged)
    KilnString upper = KilnString_from_cstr("ALREADY UPPERCASE");
    KilnString_to_ascii_upper(&upper);
    assert(strcmp(upper.ptr, "ALREADY UPPERCASE") == 0);
    KilnString_free(&upper);
    
    // Test with numbers and special characters
    KilnString special = KilnString_from_cstr("12345!@#$%^&*()_+");
    KilnString_to_ascii_upper(&special);
    assert(strcmp(special.ptr, "12345!@#$%^&*()_+") == 0);
    KilnString_free(&special);
    
    // Test with empty string
    KilnString empty = KilnString_from_cstr("");
    KilnString_to_ascii_upper(&empty);
    assert(strcmp(empty.ptr, "") == 0);
    KilnString_free(&empty);
}

// Test KilnString_to_unicode_lower
void test_kiln_string_to_unicode_lower() {
    // Test with standard ASCII mixed case
    KilnString ascii_mixed = KilnString_from_cstr("HELLO World! 123");
    KilnString_to_unicode_lower(&ascii_mixed);
    assert(strcmp(ascii_mixed.ptr, "hello world! 123") == 0);
    KilnString_free(&ascii_mixed);
    
    // Test with characters that have different Unicode lowercase
    // Examples (if your implementation supports them):
    // - "İ" (Latin capital letter I with dot above) -> "i̇" (lowercase with dot)
    // - "Ñ" (Latin capital letter N with tilde) -> "ñ" (lowercase with tilde)
    
    // Basic test with some non-ASCII characters containing diacritics
    // This assumes your implementation handles these correctly
    KilnString unicode = KilnString_from_cstr("CAFÉ RÉSUMÉ NAÏVE");
    KilnString_to_unicode_lower(&unicode);
    assert(strcmp(unicode.ptr, "café résumé naïve") == 0);
    KilnString_free(&unicode);
}

// Test KilnString_to_unicode_upper
void test_kiln_string_to_unicode_upper() {
    // Test with standard ASCII mixed case
    KilnString ascii_mixed = KilnString_from_cstr("Hello World! 123");
    KilnString_to_unicode_upper(&ascii_mixed);
    assert(strcmp(ascii_mixed.ptr, "HELLO WORLD! 123") == 0);
    KilnString_free(&ascii_mixed);
    
    // Test with characters that have different Unicode uppercase
    // Examples (if your implementation supports them):
    // - "ß" (German Eszett) -> "SS" (uppercases to double S in traditional mapping)
    // - "ı" (dotless i) -> "I" (uppercase I)
    
    // Basic test with some non-ASCII characters containing diacritics
    // This assumes your implementation handles these correctly
    KilnString unicode = KilnString_from_cstr("café résumé naïve");
    KilnString_to_unicode_upper(&unicode);
    assert(strcmp(unicode.ptr, "CAFÉ RÉSUMÉ NAÏVE") == 0);
    KilnString_free(&unicode);
}

// Test combination of case conversions
void test_case_conversion_combinations() {
    // Test converting to upper then lower
    KilnString mixed = KilnString_from_cstr("Hello World");
    KilnString_to_ascii_upper(&mixed);
    assert(strcmp(mixed.ptr, "HELLO WORLD") == 0);
    
    KilnString_to_ascii_lower(&mixed);
    assert(strcmp(mixed.ptr, "hello world") == 0);
    KilnString_free(&mixed);
    
    // Test with special case conversions (if applicable to your implementation)
    // For example, characters like 'ß' (German eszett) which uppercase to "SS" then
    // lowercase back to "ss" not the original 'ß'
    
    // Test with mixed ASCII and non-ASCII (if your implementation supports it)
    KilnString mixed_unicode = KilnString_from_cstr("Mixed CASE ñ Ö");
    KilnString_to_unicode_lower(&mixed_unicode);
    assert(strcmp(mixed_unicode.ptr, "mixed case ñ ö") == 0);
    
    KilnString_to_unicode_upper(&mixed_unicode);
    assert(strcmp(mixed_unicode.ptr, "MIXED CASE Ñ Ö") == 0);
    KilnString_free(&mixed_unicode);
}

int main() {
    printf("=== KilnString Case Conversion Tests ===\n");
    
    // Run all tests
    run_test("KilnString_to_ascii_lower", test_kiln_string_to_ascii_lower);
    run_test("KilnString_to_ascii_upper", test_kiln_string_to_ascii_upper);
    run_test("KilnString_to_unicode_lower", test_kiln_string_to_unicode_lower);
    run_test("KilnString_to_unicode_upper", test_kiln_string_to_unicode_upper);
    run_test("Case conversion combinations", test_case_conversion_combinations);
    
    return 0;
}