#include "tests.h"
#include "pontos.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

static bool test_criar_ponto_array(void) {
#ifdef DEBUG
    printf("[DEBUG] test_criar_ponto_array: Starting test\n");
#endif
    PontoArray arr;
    
    if (!criar_ponto_array(&arr, 10)) {
        printf("FAIL: criar_ponto_array - failed to create array\n");
        return false;
    }
    
    if (arr.size != 10 || arr.count != 0 || arr.array == NULL) {
        printf("FAIL: criar_ponto_array - incorrect initialization\n");
        free(arr.array);
        return false;
    }
    
    free(arr.array);
#ifdef DEBUG
    printf("[DEBUG] test_criar_ponto_array: Test passed\n");
#endif
    printf("PASS: criar_ponto_array\n");
    return true;
}

static bool test_inserir_ponto_array(void) {
#ifdef DEBUG
    printf("[DEBUG] test_inserir_ponto_array: Starting test\n");
#endif
    PontoArray arr;
    criar_ponto_array(&arr, 2);
    
    Ponto c1 = {1.0, 2.0};
    if (!inserir_ponto_array(&arr, c1)) {
        printf("FAIL: inserir_ponto_array - failed to insert first element\n");
        free(arr.array);
        return false;
    }
    
    if (arr.count != 1 || fabs(arr.array[0].x - 1.0) > 0.001 || fabs(arr.array[0].y - 2.0) > 0.001) {
        printf("FAIL: inserir_ponto_array - incorrect value or count\n");
        free(arr.array);
        return false;
    }
    
    Ponto c2 = {3.0, 4.0};
    Ponto c3 = {5.0, 6.0};
    inserir_ponto_array(&arr, c2);
    inserir_ponto_array(&arr, c3); // Should trigger reallocation
    
    if (arr.count != 3 || arr.size < 3) {
        printf("FAIL: inserir_ponto_array - reallocation failed\n");
        free(arr.array);
        return false;
    }
    
    free(arr.array);
#ifdef DEBUG
    printf("[DEBUG] test_inserir_ponto_array: Test passed\n");
#endif
    printf("PASS: inserir_ponto_array\n");
    return true;
}

bool test_ponto_arrays(void) {
#ifdef DEBUG
    printf("[DEBUG] test_ponto_arrays: Starting test suite\n");
#endif
    printf("\n=== Testing ponto_arrays ===\n");
    int passed = 0;
    
    if (test_criar_ponto_array()) passed++;
    if (test_inserir_ponto_array()) passed++;
    
#ifdef DEBUG
    printf("[DEBUG] test_ponto_arrays: Test suite completed with %d/2 passed\n", passed);
#endif
    printf("ponto_arrays: %d/2 tests passed\n", passed);
    return passed == 2;
}
