#include "tests.h"
#include "int_arrays.h"
#include <stdio.h>
#include <stdlib.h>

static int test_criar_int_array(void) {
    IntArray arr;
    
    if (!criar_int_array(&arr, 10)) {
        printf("FAIL: criar_int_array - failed to create array\n");
        return 0;
    }
    
    if (arr.size != 10 || arr.count != 0 || arr.array == NULL) {
        printf("FAIL: criar_int_array - incorrect initialization\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: criar_int_array\n");
    return 1;
}

static int test_inserir_int_array(void) {
    IntArray arr;
    criar_int_array(&arr, 2);
    
    if (!inserir_int_array(&arr, 10)) {
        printf("FAIL: inserir_int_array - failed to insert first element\n");
        free(arr.array);
        return 0;
    }
    
    if (arr.count != 1 || arr.array[0] != 10) {
        printf("FAIL: inserir_int_array - incorrect value or count\n");
        free(arr.array);
        return 0;
    }
    
    inserir_int_array(&arr, 20);
    inserir_int_array(&arr, 30); // Should trigger reallocation
    
    if (arr.count != 3 || arr.size < 3) {
        printf("FAIL: inserir_int_array - reallocation failed\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: inserir_int_array\n");
    return 1;
}

static int test_inserir_int_array_indice(void) {
    IntArray arr;
    criar_int_array(&arr, 5);
    
    inserir_int_array(&arr, 10);
    inserir_int_array(&arr, 30);
    
    if (!inserir_int_array_indice(&arr, 1, 20)) {
        printf("FAIL: inserir_int_array_indice - failed to insert at index\n");
        free(arr.array);
        return 0;
    }
    
    if (arr.array[0] != 10 || arr.array[1] != 20 || arr.array[2] != 30) {
        printf("FAIL: inserir_int_array_indice - incorrect order\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: inserir_int_array_indice\n");
    return 1;
}

int test_int_arrays(void) {
    printf("\n=== Testing int_arrays ===\n");
    int passed = 0;
    
    passed += test_criar_int_array();
    passed += test_inserir_int_array();
    passed += test_inserir_int_array_indice();
    
    printf("int_arrays: %d/3 tests passed\n", passed);
    return passed == 3;
}
