#include "tests.h"
#include "ordering.h"
#include "int_arrays.h"
#include <stdio.h>
#include <stdlib.h>

static int test_bubble_sort_int(void) {
    IntArray arr;
    criar_int_array(&arr, 5);
    
    inserir_int_array(&arr, 5);
    inserir_int_array(&arr, 2);
    inserir_int_array(&arr, 8);
    inserir_int_array(&arr, 1);
    inserir_int_array(&arr, 9);
    
    bubble_sort_int(&arr.array, &arr.count);
    
    int expected[] = {1, 2, 5, 8, 9};
    for (size_t i = 0; i < arr.count; i++) {
        if (arr.array[i] != expected[i]) {
            printf("FAIL: bubble_sort_int - incorrect order at index %zu\n", i);
            free(arr.array);
            return 0;
        }
    }
    
    free(arr.array);
    printf("PASS: bubble_sort_int\n");
    return 1;
}

static int test_reverse(void) {
    IntArray arr;
    criar_int_array(&arr, 5);
    
    inserir_int_array(&arr, 1);
    inserir_int_array(&arr, 2);
    inserir_int_array(&arr, 3);
    inserir_int_array(&arr, 4);
    inserir_int_array(&arr, 5);
    
    reverse_array(&arr.array, &arr.count);
    
    int expected[] = {5, 4, 3, 2, 1};
    for (size_t i = 0; i < arr.count; i++) {
        if (arr.array[i] != expected[i]) {
            printf("FAIL: reverse - incorrect order at index %zu\n", i);
            free(arr.array);
            return 0;
        }
    }
    
    free(arr.array);
    printf("PASS: reverse\n");
    return 1;
}

static int test_reverse_even(void) {
    IntArray arr;
    criar_int_array(&arr, 4);
    
    inserir_int_array(&arr, 1);
    inserir_int_array(&arr, 2);
    inserir_int_array(&arr, 3);
    inserir_int_array(&arr, 4);
    
    reverse_array(&arr.array, &arr.count);
    
    int expected[] = {4, 3, 2, 1};
    for (size_t i = 0; i < arr.count; i++) {
        if (arr.array[i] != expected[i]) {
            printf("FAIL: reverse (even) - incorrect order at index %zu\n", i);
            free(arr.array);
            return 0;
        }
    }
    
    free(arr.array);
    printf("PASS: reverse (even)\n");
    return 1;
}

int test_ordering(void) {
    printf("\n=== Testing ordering ===\n");
    int passed = 0;
    
    passed += test_bubble_sort_int();
    passed += test_reverse();
    passed += test_reverse_even();
    
    printf("ordering: %d/3 tests passed\n", passed);
    return passed == 3;
}
