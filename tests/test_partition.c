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

// Helper function to check StringRef content against expected C string
bool stringref_equals_cstr(StringRef ref, const char* expected) {
    if (expected == NULL) {
        return ref.ptr == NULL || ref.__length == 0;
    }
    
    if (ref.__length != strlen(expected)) {
        return false;
    }
    
    return strncmp(ref.ptr, expected, ref.__length) == 0;
}

// Test StringRef_partition
void test_stringref_partition() {
    // Test with delimiter in the middle
    StringRef test1 = StringRef_from_cstr("Hello,World");
    StringRef result1[2];
    StringRef_partition(test1, ",", result1);
    
    assert(stringref_equals_cstr(result1[0], "Hello"));
    assert(stringref_equals_cstr(result1[1], "World"));
    
    // Test with delimiter at the beginning
    StringRef test2 = StringRef_from_cstr(",Hello World");
    StringRef result2[2];
    StringRef_partition(test2, ",", result2);
    
    assert(stringref_equals_cstr(result2[0], ""));
    assert(stringref_equals_cstr(result2[1], "Hello World"));
    
    // Test with delimiter at the end
    StringRef test3 = StringRef_from_cstr("Hello World,");
    StringRef result3[2];
    StringRef_partition(test3, ",", result3);
    
    assert(stringref_equals_cstr(result3[0], "Hello World"));
    assert(stringref_equals_cstr(result3[1], ""));
    
    // Test with delimiter not found
    StringRef test4 = StringRef_from_cstr("Hello World");
    StringRef result4[2];
    StringRef_partition(test4, ",", result4);
    
    assert(stringref_equals_cstr(result4[0], "Hello World"));
    assert(stringref_equals_cstr(result4[1], ""));
    
    // Test with multiple delimiters (should only split on first occurrence)
    StringRef test5 = StringRef_from_cstr("one,two,three");
    StringRef result5[2];
    StringRef_partition(test5, ",", result5);
    
    assert(stringref_equals_cstr(result5[0], "one"));
    assert(stringref_equals_cstr(result5[1], "two,three"));
    
    // Test with multi-character delimiter
    StringRef test6 = StringRef_from_cstr("part1::part2");
    StringRef result6[2];
    StringRef_partition(test6, "::", result6);
    
    assert(stringref_equals_cstr(result6[0], "part1"));
    assert(stringref_equals_cstr(result6[1], "part2"));
    
    // Test with empty string
    StringRef test7 = StringRef_from_cstr("");
    StringRef result7[2];
    StringRef_partition(test7, ",", result7);
    
    assert(stringref_equals_cstr(result7[0], ""));
    assert(stringref_equals_cstr(result7[1], ""));
    
    // Test with empty delimiter (implementation-dependent, may not be valid)
    StringRef test8 = StringRef_from_cstr("Hello World");
    StringRef result8[2];
    StringRef_partition(test8, "", result8);
    
    // Since an empty delimiter might have special behavior, the assertion depends on implementation
    // Typical behavior would be to split at beginning, but this is implementation-dependent
    // We'll assume it splits at beginning or returns the whole string in first part
    if (result8[0].__length == 0) {
        assert(stringref_equals_cstr(result8[1], "Hello World"));
    } else {
        assert(stringref_equals_cstr(result8[0], "Hello World"));
    }
}

// Test StringRef_rpartition
void test_stringref_rpartition() {
    // Test with delimiter in the middle
    StringRef test1 = StringRef_from_cstr("Hello,World");
    StringRef result1[2];
    StringRef_rpartition(test1, ",", result1);
    
    assert(stringref_equals_cstr(result1[0], "Hello"));
    assert(stringref_equals_cstr(result1[1], "World"));
    
    // Test with delimiter at the beginning
    StringRef test2 = StringRef_from_cstr(",Hello World");
    StringRef result2[2];
    StringRef_rpartition(test2, ",", result2);
    
    assert(stringref_equals_cstr(result2[0], ""));
    assert(stringref_equals_cstr(result2[1], "Hello World"));
    
    // Test with delimiter at the end
    StringRef test3 = StringRef_from_cstr("Hello World,");
    StringRef result3[2];
    StringRef_rpartition(test3, ",", result3);
    
    assert(stringref_equals_cstr(result3[0], "Hello World"));
    assert(stringref_equals_cstr(result3[1], ""));
    
    // Test with delimiter not found
    StringRef test4 = StringRef_from_cstr("Hello World");
    StringRef result4[2];
    StringRef_rpartition(test4, ",", result4);
    
    assert(stringref_equals_cstr(result4[0], "Hello World"));
    assert(stringref_equals_cstr(result4[1], ""));
    
    // Test with multiple delimiters (should only split on last occurrence)
    StringRef test5 = StringRef_from_cstr("one,two,three");
    StringRef result5[2];
    StringRef_rpartition(test5, ",", result5);
    
    assert(stringref_equals_cstr(result5[0], "one,two"));
    assert(stringref_equals_cstr(result5[1], "three"));
    
    // Test with multi-character delimiter
    StringRef test6 = StringRef_from_cstr("part1::part2::part3");
    StringRef result6[2];
    StringRef_rpartition(test6, "::", result6);
    
    assert(stringref_equals_cstr(result6[0], "part1::part2"));
    assert(stringref_equals_cstr(result6[1], "part3"));
    
    // Test with empty string
    StringRef test7 = StringRef_from_cstr("");
    StringRef result7[2];
    StringRef_rpartition(test7, ",", result7);
    
    assert(stringref_equals_cstr(result7[0], ""));
    assert(stringref_equals_cstr(result7[1], ""));
    
    // Test with empty delimiter (implementation-dependent, may not be valid)
    StringRef test8 = StringRef_from_cstr("Hello World");
    StringRef result8[2];
    StringRef_rpartition(test8, "", result8);
    
    // Since an empty delimiter might have special behavior, the assertion depends on implementation
    // Typical behavior would be to split at end, but this is implementation-dependent
    if (result8[0].__length == 0) {
        assert(stringref_equals_cstr(result8[1], "Hello World"));
    } else {
        assert(stringref_equals_cstr(result8[0], "Hello World"));
    }
}

// Test case comparing partition and rpartition with multiple delimiters
void test_compare_partition_methods() {
    // String with multiple delimiters for comparison
    StringRef test = StringRef_from_cstr("first,second,third,fourth");
    
    // Forward partition (splits on first delimiter)
    StringRef forward_result[2];
    StringRef_partition(test, ",", forward_result);
    
    assert(stringref_equals_cstr(forward_result[0], "first"));
    assert(stringref_equals_cstr(forward_result[1], "second,third,fourth"));
    
    // Reverse partition (splits on last delimiter)
    StringRef reverse_result[2];
    StringRef_rpartition(test, ",", reverse_result);
    
    assert(stringref_equals_cstr(reverse_result[0], "first,second,third"));
    assert(stringref_equals_cstr(reverse_result[1], "fourth"));
}

// Test error cases or edge cases
void test_partition_edge_cases() {
    // Test with NULL or invalid input (if your implementation allows it)
    // Note: These are optional based on your library's philosophy about NULL checks
    
    // Test with very long string
    char long_str[1024];
    memset(long_str, 'a', 1023);
    long_str[1023] = '\0';
    
    StringRef long_ref = StringRef_from_cstr(long_str);
    StringRef result[2];
    
    // Place delimiter at beginning
    long_str[0] = ',';
    StringRef_partition(long_ref, ",", result);
    assert(result[0].__length == 0);
    assert(result[1].__length == 1022);
    
    // Place delimiter at end
    long_str[0] = 'a';
    long_str[1022] = ',';
    long_ref = StringRef_from_cstr(long_str);
    StringRef_partition(long_ref, ",", result);
    assert(result[0].__length == 1022);
    assert(result[1].__length == 0);
    
    // Test with repeated delimiters
    StringRef repeats = StringRef_from_cstr(",,,,test,,,,");
    
    // Forward partition should find first delimiter
    StringRef_partition(repeats, ",", result);
    assert(result[0].__length == 0);
    assert(stringref_equals_cstr(result[1], ",,,test,,,,"));
    
    // Reverse partition should find last delimiter
    StringRef_rpartition(repeats, ",", result);
    assert(stringref_equals_cstr(result[0], ",,,,test,,,"));
    assert(result[1].__length == 0);
}

int main() {
    printf("=== KilnString Partition Tests ===\n");
    
    // Run all tests
    run_test("StringRef_partition", test_stringref_partition);
    run_test("StringRef_rpartition", test_stringref_rpartition);
    run_test("Compare partition methods", test_compare_partition_methods);
    run_test("Partition edge cases", test_partition_edge_cases);
    
    return 0;
}