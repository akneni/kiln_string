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

// Test kiln_string_to_ascii_lower
void test_kiln_string_to_ascii_lower() {
    // Test with mixed case string
    kiln_string_t mixed = kiln_string_from_cstr("HELLO World! 123");
    kiln_string_to_ascii_lower(&mixed);
    assert(strcmp(mixed.ptr, "hello world! 123") == 0);
    kiln_string_free(&mixed);
    
    // Test with all uppercase
    kiln_string_t upper = kiln_string_from_cstr("ALL UPPERCASE TEXT");
    kiln_string_to_ascii_lower(&upper);
    assert(strcmp(upper.ptr, "all uppercase text") == 0);
    kiln_string_free(&upper);
    
    // Test with all lowercase (should remain unchanged)
    kiln_string_t lower = kiln_string_from_cstr("already lowercase");
    kiln_string_to_ascii_lower(&lower);
    assert(strcmp(lower.ptr, "already lowercase") == 0);
    kiln_string_free(&lower);
    
    // Test with numbers and special characters
    kiln_string_t special = kiln_string_from_cstr("12345!@#$%^&*()_+");
    kiln_string_to_ascii_lower(&special);
    assert(strcmp(special.ptr, "12345!@#$%^&*()_+") == 0);
    kiln_string_free(&special);
    
    // Test with empty string
    kiln_string_t empty = kiln_string_from_cstr("");
    kiln_string_to_ascii_lower(&empty);
    assert(strcmp(empty.ptr, "") == 0);
    kiln_string_free(&empty);
}

// Test kiln_string_to_ascii_upper
void test_kiln_string_to_ascii_upper() {
    // Test with mixed case string
    kiln_string_t mixed = kiln_string_from_cstr("Hello World! 123");
    kiln_string_to_ascii_upper(&mixed);
    assert(strcmp(mixed.ptr, "HELLO WORLD! 123") == 0);
    kiln_string_free(&mixed);
    
    // Test with all lowercase
    kiln_string_t lower = kiln_string_from_cstr("all lowercase text");
    kiln_string_to_ascii_upper(&lower);
    assert(strcmp(lower.ptr, "ALL LOWERCASE TEXT") == 0);
    kiln_string_free(&lower);
    
    // Test with all uppercase (should remain unchanged)
    kiln_string_t upper = kiln_string_from_cstr("ALREADY UPPERCASE");
    kiln_string_to_ascii_upper(&upper);
    assert(strcmp(upper.ptr, "ALREADY UPPERCASE") == 0);
    kiln_string_free(&upper);
    
    // Test with numbers and special characters
    kiln_string_t special = kiln_string_from_cstr("12345!@#$%^&*()_+");
    kiln_string_to_ascii_upper(&special);
    assert(strcmp(special.ptr, "12345!@#$%^&*()_+") == 0);
    kiln_string_free(&special);
    
    // Test with empty string
    kiln_string_t empty = kiln_string_from_cstr("");
    kiln_string_to_ascii_upper(&empty);
    assert(strcmp(empty.ptr, "") == 0);
    kiln_string_free(&empty);
}

// Test kiln_string_to_unicode_lower
void test_kiln_string_to_unicode_lower() {
    // Test with standard ASCII mixed case
    kiln_string_t ascii_mixed = kiln_string_from_cstr("HELLO World! 123");
    kiln_string_to_unicode_lower(&ascii_mixed);
    assert(strcmp(ascii_mixed.ptr, "hello world! 123") == 0);
    kiln_string_free(&ascii_mixed);
    
    // Test with characters that have different Unicode lowercase
    // Examples (if your implementation supports them):
    // - "İ" (Latin capital letter I with dot above) -> "i̇" (lowercase with dot)
    // - "Ñ" (Latin capital letter N with tilde) -> "ñ" (lowercase with tilde)
    
    // Basic test with some non-ASCII characters containing diacritics
    // This assumes your implementation handles these correctly
    kiln_string_t unicode = kiln_string_from_cstr("CAFÉ RÉSUMÉ NAÏVE");
    kiln_string_to_unicode_lower(&unicode);
    assert(strcmp(unicode.ptr, "café résumé naïve") == 0);
    kiln_string_free(&unicode);
}

// Test kiln_string_to_unicode_upper
void test_kiln_string_to_unicode_upper() {
    // Test with standard ASCII mixed case
    kiln_string_t ascii_mixed = kiln_string_from_cstr("Hello World! 123");
    kiln_string_to_unicode_upper(&ascii_mixed);
    assert(strcmp(ascii_mixed.ptr, "HELLO WORLD! 123") == 0);
    kiln_string_free(&ascii_mixed);
    
    // Test with characters that have different Unicode uppercase
    // Examples (if your implementation supports them):
    // - "ß" (German Eszett) -> "SS" (uppercases to double S in traditional mapping)
    // - "ı" (dotless i) -> "I" (uppercase I)
    
    // Basic test with some non-ASCII characters containing diacritics
    // This assumes your implementation handles these correctly
    kiln_string_t unicode = kiln_string_from_cstr("café résumé naïve");
    kiln_string_to_unicode_upper(&unicode);
    assert(strcmp(unicode.ptr, "CAFÉ RÉSUMÉ NAÏVE") == 0);
    kiln_string_free(&unicode);
}

// Test combination of case conversions
void test_case_conversion_combinations() {
    // Test converting to upper then lower
    kiln_string_t mixed = kiln_string_from_cstr("Hello World");
    kiln_string_to_ascii_upper(&mixed);
    assert(strcmp(mixed.ptr, "HELLO WORLD") == 0);
    
    kiln_string_to_ascii_lower(&mixed);
    assert(strcmp(mixed.ptr, "hello world") == 0);
    kiln_string_free(&mixed);
    
    // Test with special case conversions (if applicable to your implementation)
    // For example, characters like 'ß' (German eszett) which uppercase to "SS" then
    // lowercase back to "ss" not the original 'ß'
    
    // Test with mixed ASCII and non-ASCII (if your implementation supports it)
    kiln_string_t mixed_unicode = kiln_string_from_cstr("Mixed CASE ñ Ö");
    kiln_string_to_unicode_lower(&mixed_unicode);
    assert(strcmp(mixed_unicode.ptr, "mixed case ñ ö") == 0);
    
    kiln_string_to_unicode_upper(&mixed_unicode);
    assert(strcmp(mixed_unicode.ptr, "MIXED CASE Ñ Ö") == 0);
    kiln_string_free(&mixed_unicode);
}

int main() {
    printf("=== kiln_string_t Case Conversion Tests ===\n");
    
    // Run all tests
    run_test("kiln_string_to_ascii_lower", test_kiln_string_to_ascii_lower);
    run_test("kiln_string_to_ascii_upper", test_kiln_string_to_ascii_upper);
    run_test("kiln_string_to_unicode_lower", test_kiln_string_to_unicode_lower);
    run_test("kiln_string_to_unicode_upper", test_kiln_string_to_unicode_upper);
    run_test("Case conversion combinations", test_case_conversion_combinations);
    
    return 0;
}