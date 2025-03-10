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

// Test KilnString_trim_inplace
void test_kiln_string_trim_inplace() {
    // Test with leading whitespace
    KilnString leading = KilnString_from_cstr("   Hello World");
    KilnString_trim_inplace(&leading);
    assert(strcmp(leading.ptr, "Hello World") == 0);
    assert(leading.__length == 11);
    KilnString_free(&leading);
    
    // Test with trailing whitespace
    KilnString trailing = KilnString_from_cstr("Hello World   ");
    KilnString_trim_inplace(&trailing);
    assert(strcmp(trailing.ptr, "Hello World") == 0);
    assert(trailing.__length == 11);
    KilnString_free(&trailing);
    
    // Test with both leading and trailing whitespace
    KilnString both = KilnString_from_cstr("  Hello World  ");
    KilnString_trim_inplace(&both);
    assert(strcmp(both.ptr, "Hello World") == 0);
    assert(both.__length == 11);
    KilnString_free(&both);
    
    // Test with only whitespace
    KilnString only_space = KilnString_from_cstr("     ");
    KilnString_trim_inplace(&only_space);
    assert(strcmp(only_space.ptr, "") == 0);
    assert(only_space.__length == 0);
    KilnString_free(&only_space);
    
    // Test with empty string
    KilnString empty = KilnString_from_cstr("");
    KilnString_trim_inplace(&empty);
    assert(strcmp(empty.ptr, "") == 0);
    assert(empty.__length == 0);
    KilnString_free(&empty);
    
    // Test with no whitespace (should remain unchanged)
    KilnString no_space = KilnString_from_cstr("Hello");
    KilnString_trim_inplace(&no_space);
    assert(strcmp(no_space.ptr, "Hello") == 0);
    assert(no_space.__length == 5);
    KilnString_free(&no_space);
    
    // Test with various whitespace characters
    KilnString various = KilnString_from_cstr("\t\n\r Hello World \t\n\r");
    KilnString_trim_inplace(&various);
    assert(strcmp(various.ptr, "Hello World") == 0);
    assert(various.__length == 11);
    KilnString_free(&various);
}

// Test StringRef_trim
void test_stringref_trim() {
    // Test with leading whitespace
    StringRef leading = StringRef_from_cstr("   Hello World");
    StringRef trimmed_leading = StringRef_trim(leading);
    assert(trimmed_leading.__length == 11);
    // Can't use strcmp directly with StringRef, so create a KilnString for comparison
    KilnString kstr_leading = StringRef_to_kiln_string(trimmed_leading);
    assert(strcmp(kstr_leading.ptr, "Hello World") == 0);
    KilnString_free(&kstr_leading);
    
    // Test with trailing whitespace
    StringRef trailing = StringRef_from_cstr("Hello World   ");
    StringRef trimmed_trailing = StringRef_trim(trailing);
    assert(trimmed_trailing.__length == 11);
    KilnString kstr_trailing = StringRef_to_kiln_string(trimmed_trailing);
    assert(strcmp(kstr_trailing.ptr, "Hello World") == 0);
    KilnString_free(&kstr_trailing);
    
    // Test with both leading and trailing whitespace
    StringRef both = StringRef_from_cstr("  Hello World  ");
    StringRef trimmed_both = StringRef_trim(both);
    assert(trimmed_both.__length == 11);
    KilnString kstr_both = StringRef_to_kiln_string(trimmed_both);
    assert(strcmp(kstr_both.ptr, "Hello World") == 0);
    KilnString_free(&kstr_both);
    
    // Test with only whitespace
    StringRef only_space = StringRef_from_cstr("     ");
    StringRef trimmed_only_space = StringRef_trim(only_space);
    assert(trimmed_only_space.__length == 0);
    KilnString kstr_only_space = StringRef_to_kiln_string(trimmed_only_space);
    assert(strcmp(kstr_only_space.ptr, "") == 0);
    KilnString_free(&kstr_only_space);
    
    // Test with empty string
    StringRef empty = StringRef_from_cstr("");
    StringRef trimmed_empty = StringRef_trim(empty);
    assert(trimmed_empty.__length == 0);
    
    // Test with no whitespace (should remain unchanged)
    StringRef no_space = StringRef_from_cstr("Hello");
    StringRef trimmed_no_space = StringRef_trim(no_space);
    assert(trimmed_no_space.__length == 5);
    KilnString kstr_no_space = StringRef_to_kiln_string(trimmed_no_space);
    assert(strcmp(kstr_no_space.ptr, "Hello") == 0);
    KilnString_free(&kstr_no_space);
    
    // Test with various whitespace characters
    StringRef various = StringRef_from_cstr("\t\n\r Hello World \t\n\r");
    StringRef trimmed_various = StringRef_trim(various);
    assert(trimmed_various.__length == 11);
    KilnString kstr_various = StringRef_to_kiln_string(trimmed_various);
    assert(strcmp(kstr_various.ptr, "Hello World") == 0);
    KilnString_free(&kstr_various);
}

// Test KilnString_trim
void test_kilnstring_trim() {
    // Test with leading whitespace
    KilnString leading = KilnString_from_cstr("   Hello World");
    StringRef trimmed_leading = KilnString_trim(&leading);
    assert(trimmed_leading.__length == 11);
    KilnString kstr_leading = StringRef_to_kiln_string(trimmed_leading);
    assert(strcmp(kstr_leading.ptr, "Hello World") == 0);
    KilnString_free(&leading);
    KilnString_free(&kstr_leading);
    
    // Test with trailing whitespace
    KilnString trailing = KilnString_from_cstr("Hello World   ");
    StringRef trimmed_trailing = KilnString_trim(&trailing);
    assert(trimmed_trailing.__length == 11);
    KilnString kstr_trailing = StringRef_to_kiln_string(trimmed_trailing);
    assert(strcmp(kstr_trailing.ptr, "Hello World") == 0);
    KilnString_free(&trailing);
    KilnString_free(&kstr_trailing);
    
    // Continuing with other trim tests similar to the previous ones...
    // Test with both leading and trailing whitespace
    KilnString both = KilnString_from_cstr("  Hello World  ");
    StringRef trimmed_both = KilnString_trim(&both);
    assert(trimmed_both.__length == 11);
    KilnString kstr_both = StringRef_to_kiln_string(trimmed_both);
    assert(strcmp(kstr_both.ptr, "Hello World") == 0);
    KilnString_free(&both);
    KilnString_free(&kstr_both);
    
    // Test with only whitespace
    KilnString only_space = KilnString_from_cstr("     ");
    StringRef trimmed_only_space = KilnString_trim(&only_space);
    assert(trimmed_only_space.__length == 0);
    KilnString_free(&only_space);
}

// Test KilnString_replace
void test_kilnstring_replace() {
    // Test basic replacement
    KilnString basic = KilnString_from_cstr("Hello, world!");
    KilnString_replace(&basic, "world", "universe");
    assert(strcmp(basic.ptr, "Hello, universe!") == 0);
    KilnString_free(&basic);
    
    // Test replacement with shorter string
    KilnString shorter = KilnString_from_cstr("Replace longer with short");
    KilnString_replace(&shorter, "longer", "tiny");
    assert(strcmp(shorter.ptr, "Replace tiny with short") == 0);
    KilnString_free(&shorter);
    
    // Test replacement with longer string
    KilnString longer = KilnString_from_cstr("Make this bigger");
    KilnString_replace(&longer, "bigger", "substantially larger");
    assert(strcmp(longer.ptr, "Make this substantially larger") == 0);
    KilnString_free(&longer);
    
    // Test with target string not found
    KilnString not_found = KilnString_from_cstr("Nothing to replace here");
    KilnString_replace(&not_found, "missing", "replacement");
    assert(strcmp(not_found.ptr, "Nothing to replace here") == 0);
    KilnString_free(&not_found);
    
    // Test with empty replacement string (effectively deleting the target)
    KilnString delete_target = KilnString_from_cstr("Remove this word");
    KilnString_replace(&delete_target, "this ", "");
    assert(strcmp(delete_target.ptr, "Remove word") == 0);
    KilnString_free(&delete_target);
    
    // Test with empty target string (should not replace anything)
    KilnString empty_target = KilnString_from_cstr("Don't change me");
    KilnString_replace(&empty_target, "", "something");
    assert(strcmp(empty_target.ptr, "Don't change me") == 0);
    KilnString_free(&empty_target);
    
    // Test with multiple occurrences
    KilnString multiple = KilnString_from_cstr("one two one two one");
    KilnString_replace(&multiple, "one", "1");
    assert(strcmp(multiple.ptr, "1 two 1 two 1") == 0);
    KilnString_free(&multiple);
    
    // Test with occurrence at the beginning
    KilnString at_beginning = KilnString_from_cstr("Start with this");
    KilnString_replace(&at_beginning, "Start", "Begin");
    assert(strcmp(at_beginning.ptr, "Begin with this") == 0);
    KilnString_free(&at_beginning);
    
    // Test with occurrence at the end
    KilnString at_end = KilnString_from_cstr("This is the end");
    KilnString_replace(&at_end, "end", "finale");
    assert(strcmp(at_end.ptr, "This is the finale") == 0);
    KilnString_free(&at_end);
    
    // Test replacing with the same string (should remain unchanged)
    KilnString same = KilnString_from_cstr("No real change");
    KilnString_replace(&same, "real", "real");
    assert(strcmp(same.ptr, "No real change") == 0);
    KilnString_free(&same);
    
    // Test case-sensitive replacement
    KilnString case_sensitive = KilnString_from_cstr("Case CASE case");
    KilnString_replace(&case_sensitive, "case", "test");
    // Only the lowercase "case" instances should be replaced
    assert(strcmp(case_sensitive.ptr, "test CASE test") == 0);
    KilnString_free(&case_sensitive);
}

// Test complex patterns with both trim and replace
void test_combined_operations() {
    // Test trim followed by replace
    KilnString trim_then_replace = KilnString_from_cstr("  Hello, world!  ");
    KilnString_trim_inplace(&trim_then_replace);
    assert(strcmp(trim_then_replace.ptr, "Hello, world!") == 0);
    
    KilnString_replace(&trim_then_replace, "world", "universe");
    assert(strcmp(trim_then_replace.ptr, "Hello, universe!") == 0);
    KilnString_free(&trim_then_replace);
    
    // Test replace followed by trim
    KilnString replace_then_trim = KilnString_from_cstr("  Old text here  ");
    KilnString_replace(&replace_then_trim, "Old", "New");
    assert(strcmp(replace_then_trim.ptr, "  New text here  ") == 0);
    
    KilnString_trim_inplace(&replace_then_trim);
    assert(strcmp(replace_then_trim.ptr, "New text here") == 0);
    KilnString_free(&replace_then_trim);
    
    // Test multiple operations in sequence
    KilnString multiple_ops = KilnString_from_cstr("\t Complex example with SPACES \n");
    KilnString_trim_inplace(&multiple_ops);
    assert(strcmp(multiple_ops.ptr, "Complex example with SPACES") == 0);
    
    KilnString_replace(&multiple_ops, "example", "test");
    assert(strcmp(multiple_ops.ptr, "Complex test with SPACES") == 0);
    
    KilnString_to_ascii_lower(&multiple_ops);
    assert(strcmp(multiple_ops.ptr, "complex test with spaces") == 0);
    
    KilnString_replace(&multiple_ops, "complex", "simple");
    assert(strcmp(multiple_ops.ptr, "simple test with spaces") == 0);
    KilnString_free(&multiple_ops);
}

int main() {
    printf("=== KilnString Trim and Replace Tests ===\n");
    
    // Run all tests
    run_test("KilnString_trim_inplace", test_kiln_string_trim_inplace);
    run_test("StringRef_trim", test_stringref_trim);
    run_test("KilnString_trim", test_kilnstring_trim);
    run_test("KilnString_replace", test_kilnstring_replace);
    run_test("Combined operations", test_combined_operations);
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}