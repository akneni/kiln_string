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

// Test kiln_string_trim_inplace
void test_kiln_string_trim_inplace() {
    // Test with leading whitespace
    kiln_string_t leading = kiln_string_from_cstr("   Hello World");
    kiln_string_trim_inplace(&leading);
    assert(strcmp(leading.ptr, "Hello World") == 0);
    assert(leading.__length == 11);
    kiln_string_free(&leading);
    
    // Test with trailing whitespace
    kiln_string_t trailing = kiln_string_from_cstr("Hello World   ");
    kiln_string_trim_inplace(&trailing);
    assert(strcmp(trailing.ptr, "Hello World") == 0);
    assert(trailing.__length == 11);
    kiln_string_free(&trailing);
    
    // Test with both leading and trailing whitespace
    kiln_string_t both = kiln_string_from_cstr("  Hello World  ");
    kiln_string_trim_inplace(&both);
    assert(strcmp(both.ptr, "Hello World") == 0);
    assert(both.__length == 11);
    kiln_string_free(&both);
    
    // Test with only whitespace
    kiln_string_t only_space = kiln_string_from_cstr("     ");
    kiln_string_trim_inplace(&only_space);
    assert(strcmp(only_space.ptr, "") == 0);
    assert(only_space.__length == 0);
    kiln_string_free(&only_space);
    
    // Test with empty string
    kiln_string_t empty = kiln_string_from_cstr("");
    kiln_string_trim_inplace(&empty);
    assert(strcmp(empty.ptr, "") == 0);
    assert(empty.__length == 0);
    kiln_string_free(&empty);
    
    // Test with no whitespace (should remain unchanged)
    kiln_string_t no_space = kiln_string_from_cstr("Hello");
    kiln_string_trim_inplace(&no_space);
    assert(strcmp(no_space.ptr, "Hello") == 0);
    assert(no_space.__length == 5);
    kiln_string_free(&no_space);
    
    // Test with various whitespace characters
    kiln_string_t various = kiln_string_from_cstr("\t\n\r Hello World \t\n\r");
    kiln_string_trim_inplace(&various);
    assert(strcmp(various.ptr, "Hello World") == 0);
    assert(various.__length == 11);
    kiln_string_free(&various);
}

// Test kstring_ref_trim
void test_stringref_trim() {
    // Test with leading whitespace
    kstring_ref_t leading = kstring_ref_from_cstr("   Hello World");
    kstring_ref_t trimmed_leading = kstring_ref_trim(leading);
    assert(trimmed_leading.__length == 11);
    // Can't use strcmp directly with StringRef, so create a kiln_string_t for comparison
    kiln_string_t kstr_leading = kstring_ref_to_kiln_string(trimmed_leading);
    assert(strcmp(kstr_leading.ptr, "Hello World") == 0);
    kiln_string_free(&kstr_leading);
    
    // Test with trailing whitespace
    kstring_ref_t trailing = kstring_ref_from_cstr("Hello World   ");
    kstring_ref_t trimmed_trailing = kstring_ref_trim(trailing);
    assert(trimmed_trailing.__length == 11);
    kiln_string_t kstr_trailing = kstring_ref_to_kiln_string(trimmed_trailing);
    assert(strcmp(kstr_trailing.ptr, "Hello World") == 0);
    kiln_string_free(&kstr_trailing);
    
    // Test with both leading and trailing whitespace
    kstring_ref_t both = kstring_ref_from_cstr("  Hello World  ");
    kstring_ref_t trimmed_both = kstring_ref_trim(both);
    assert(trimmed_both.__length == 11);
    kiln_string_t kstr_both = kstring_ref_to_kiln_string(trimmed_both);
    assert(strcmp(kstr_both.ptr, "Hello World") == 0);
    kiln_string_free(&kstr_both);
    
    // Test with only whitespace
    kstring_ref_t only_space = kstring_ref_from_cstr("     ");
    kstring_ref_t trimmed_only_space = kstring_ref_trim(only_space);
    assert(trimmed_only_space.__length == 0);
    kiln_string_t kstr_only_space = kstring_ref_to_kiln_string(trimmed_only_space);
    assert(strcmp(kstr_only_space.ptr, "") == 0);
    kiln_string_free(&kstr_only_space);
    
    // Test with empty string
    kstring_ref_t empty = kstring_ref_from_cstr("");
    kstring_ref_t trimmed_empty = kstring_ref_trim(empty);
    assert(trimmed_empty.__length == 0);
    
    // Test with no whitespace (should remain unchanged)
    kstring_ref_t no_space = kstring_ref_from_cstr("Hello");
    kstring_ref_t trimmed_no_space = kstring_ref_trim(no_space);
    assert(trimmed_no_space.__length == 5);
    kiln_string_t kstr_no_space = kstring_ref_to_kiln_string(trimmed_no_space);
    assert(strcmp(kstr_no_space.ptr, "Hello") == 0);
    kiln_string_free(&kstr_no_space);
    
    // Test with various whitespace characters
    kstring_ref_t various = kstring_ref_from_cstr("\t\n\r Hello World \t\n\r");
    kstring_ref_t trimmed_various = kstring_ref_trim(various);
    assert(trimmed_various.__length == 11);
    kiln_string_t kstr_various = kstring_ref_to_kiln_string(trimmed_various);
    assert(strcmp(kstr_various.ptr, "Hello World") == 0);
    kiln_string_free(&kstr_various);
}

// Test kiln_string_trim
void test_kilnstring_trim() {
    // Test with leading whitespace
    kiln_string_t leading = kiln_string_from_cstr("   Hello World");
    kstring_ref_t trimmed_leading = kiln_string_trim(&leading);
    assert(trimmed_leading.__length == 11);
    kiln_string_t kstr_leading = kstring_ref_to_kiln_string(trimmed_leading);
    assert(strcmp(kstr_leading.ptr, "Hello World") == 0);
    kiln_string_free(&leading);
    kiln_string_free(&kstr_leading);
    
    // Test with trailing whitespace
    kiln_string_t trailing = kiln_string_from_cstr("Hello World   ");
    kstring_ref_t trimmed_trailing = kiln_string_trim(&trailing);
    assert(trimmed_trailing.__length == 11);
    kiln_string_t kstr_trailing = kstring_ref_to_kiln_string(trimmed_trailing);
    assert(strcmp(kstr_trailing.ptr, "Hello World") == 0);
    kiln_string_free(&trailing);
    kiln_string_free(&kstr_trailing);
    
    // Continuing with other trim tests similar to the previous ones...
    // Test with both leading and trailing whitespace
    kiln_string_t both = kiln_string_from_cstr("  Hello World  ");
    kstring_ref_t trimmed_both = kiln_string_trim(&both);
    assert(trimmed_both.__length == 11);
    kiln_string_t kstr_both = kstring_ref_to_kiln_string(trimmed_both);
    assert(strcmp(kstr_both.ptr, "Hello World") == 0);
    kiln_string_free(&both);
    kiln_string_free(&kstr_both);
    
    // Test with only whitespace
    kiln_string_t only_space = kiln_string_from_cstr("     ");
    kstring_ref_t trimmed_only_space = kiln_string_trim(&only_space);
    assert(trimmed_only_space.__length == 0);
    kiln_string_free(&only_space);
}

// Test kiln_string_replace
void test_kilnstring_replace() {
    // Test basic replacement
    kiln_string_t basic = kiln_string_from_cstr("Hello, world!");
    kiln_string_replace(&basic, "world", "universe");
    assert(strcmp(basic.ptr, "Hello, universe!") == 0);
    kiln_string_free(&basic);
    
    // Test replacement with shorter string
    kiln_string_t shorter = kiln_string_from_cstr("Replace longer with short");
    kiln_string_replace(&shorter, "longer", "tiny");
    assert(strcmp(shorter.ptr, "Replace tiny with short") == 0);
    kiln_string_free(&shorter);
    
    // Test replacement with longer string
    kiln_string_t longer = kiln_string_from_cstr("Make this bigger");
    kiln_string_replace(&longer, "bigger", "substantially larger");
    assert(strcmp(longer.ptr, "Make this substantially larger") == 0);
    kiln_string_free(&longer);
    
    // Test with target string not found
    kiln_string_t not_found = kiln_string_from_cstr("Nothing to replace here");
    kiln_string_replace(&not_found, "missing", "replacement");
    assert(strcmp(not_found.ptr, "Nothing to replace here") == 0);
    kiln_string_free(&not_found);
    
    // Test with empty replacement string (effectively deleting the target)
    kiln_string_t delete_target = kiln_string_from_cstr("Remove this word");
    kiln_string_replace(&delete_target, "this ", "");
    assert(strcmp(delete_target.ptr, "Remove word") == 0);
    kiln_string_free(&delete_target);
    
    // Test with empty target string (should not replace anything)
    kiln_string_t empty_target = kiln_string_from_cstr("Don't change me");
    kiln_string_replace(&empty_target, "", "something");
    assert(strcmp(empty_target.ptr, "Don't change me") == 0);
    kiln_string_free(&empty_target);
    
    // Test with multiple occurrences
    kiln_string_t multiple = kiln_string_from_cstr("one two one two one");
    kiln_string_replace(&multiple, "one", "1");
    assert(strcmp(multiple.ptr, "1 two 1 two 1") == 0);
    kiln_string_free(&multiple);
    
    // Test with occurrence at the beginning
    kiln_string_t at_beginning = kiln_string_from_cstr("Start with this");
    kiln_string_replace(&at_beginning, "Start", "Begin");
    assert(strcmp(at_beginning.ptr, "Begin with this") == 0);
    kiln_string_free(&at_beginning);
    
    // Test with occurrence at the end
    kiln_string_t at_end = kiln_string_from_cstr("This is the end");
    kiln_string_replace(&at_end, "end", "finale");
    assert(strcmp(at_end.ptr, "This is the finale") == 0);
    kiln_string_free(&at_end);
    
    // Test replacing with the same string (should remain unchanged)
    kiln_string_t same = kiln_string_from_cstr("No real change");
    kiln_string_replace(&same, "real", "real");
    assert(strcmp(same.ptr, "No real change") == 0);
    kiln_string_free(&same);
    
    // Test case-sensitive replacement
    kiln_string_t case_sensitive = kiln_string_from_cstr("Case CASE case");
    kiln_string_replace(&case_sensitive, "case", "test");
    // Only the lowercase "case" instances should be replaced
    assert(strcmp(case_sensitive.ptr, "Case CASE test") == 0);
    kiln_string_free(&case_sensitive);
}

// Test complex patterns with both trim and replace
void test_combined_operations() {
    // Test trim followed by replace
    kiln_string_t trim_then_replace = kiln_string_from_cstr("  Hello, world!  ");
    kiln_string_trim_inplace(&trim_then_replace);
    assert(strcmp(trim_then_replace.ptr, "Hello, world!") == 0);
    
    kiln_string_replace(&trim_then_replace, "world", "universe");
    assert(strcmp(trim_then_replace.ptr, "Hello, universe!") == 0);
    kiln_string_free(&trim_then_replace);
    
    // Test replace followed by trim
    kiln_string_t replace_then_trim = kiln_string_from_cstr("  Old text here  ");
    kiln_string_replace(&replace_then_trim, "Old", "New");
    assert(strcmp(replace_then_trim.ptr, "  New text here  ") == 0);
    
    kiln_string_trim_inplace(&replace_then_trim);
    assert(strcmp(replace_then_trim.ptr, "New text here") == 0);
    kiln_string_free(&replace_then_trim);
    
    // Test multiple operations in sequence
    kiln_string_t multiple_ops = kiln_string_from_cstr("\t Complex example with SPACES \n");
    kiln_string_trim_inplace(&multiple_ops);
    assert(strcmp(multiple_ops.ptr, "Complex example with SPACES") == 0);
    
    kiln_string_replace(&multiple_ops, "example", "test");
    assert(strcmp(multiple_ops.ptr, "Complex test with SPACES") == 0);
    
    kiln_string_to_ascii_lower(&multiple_ops);
    assert(strcmp(multiple_ops.ptr, "complex test with spaces") == 0);
    
    kiln_string_replace(&multiple_ops, "complex", "simple");
    assert(strcmp(multiple_ops.ptr, "simple test with spaces") == 0);
    kiln_string_free(&multiple_ops);
}

int main() {
    printf("=== kiln_string_t Trim and Replace Tests ===\n");
    
    // Run all tests
    run_test("kiln_string_trim_inplace", test_kiln_string_trim_inplace);
    run_test("kstring_ref_trim", test_stringref_trim);
    run_test("kiln_string_trim", test_kilnstring_trim);
    run_test("kiln_string_replace", test_kilnstring_replace);
    run_test("Combined operations", test_combined_operations);
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}