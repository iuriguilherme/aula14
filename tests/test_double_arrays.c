#include "tests.h"
#include "double_arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int test_criar_double_array(void) {
    DoubleArray arr;
    
    if (!criar_double_array(&arr, 10)) {
        printf("FAIL: criar_double_array - failed to create array\n");
        return 0;
    }
    
    if (arr.size != 10 || arr.count != 0 || arr.array == NULL) {
        printf("FAIL: criar_double_array - incorrect initialization\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: criar_double_array\n");
    return 1;
}

static int test_inserir_double_array(void) {
    DoubleArray arr;
    criar_double_array(&arr, 2);
    
    if (!inserir_double_array(&arr, 3.14)) {
        printf("FAIL: inserir_double_array - failed to insert first element\n");
        free(arr.array);
        return 0;
    }
    
    if (arr.count != 1 || fabs(arr.array[0] - 3.14) > 0.001) {
        printf("FAIL: inserir_double_array - incorrect value or count\n");
        free(arr.array);
        return 0;
    }
    
    inserir_double_array(&arr, 2.71);
    inserir_double_array(&arr, 1.41); // Should trigger reallocation
    
    if (arr.count != 3 || arr.size < 3) {
        printf("FAIL: inserir_double_array - reallocation failed\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: inserir_double_array\n");
    return 1;
}

int test_double_arrays(void) {
    printf("\n=== Testing double_arrays ===\n");
    int passed = 0;
    
    passed += test_criar_double_array();
    passed += test_inserir_double_array();
    
    printf("double_arrays: %d/2 tests passed\n", passed);
    return passed == 2;
}
