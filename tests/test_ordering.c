#include "tests.h"
#include "ordering.h"
#include "pontos.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int test_bubble_sort_ponto(void) {
#ifdef DEBUG
    printf("[DEBUG] test_bubble_sort_ponto: Starting test\n");
#endif
    PontoArray arr;
    criar_ponto_array(&arr, 5);
    
    inserir_ponto_array(&arr, (Ponto){5.0, 10.0});
    inserir_ponto_array(&arr, (Ponto){2.0, 4.0});
    inserir_ponto_array(&arr, (Ponto){8.0, 16.0});
    inserir_ponto_array(&arr, (Ponto){1.0, 2.0});
    inserir_ponto_array(&arr, (Ponto){9.0, 18.0});
    
    bubble_sort_ponto(&arr);
    
    double expected_x[] = {1.0, 2.0, 5.0, 8.0, 9.0};
    for (size_t i = 0; i < arr.count; i++) {
        if (fabs(arr.array[i].x - expected_x[i]) > 1e-9) {
            printf("FAIL: bubble_sort_ponto - incorrect order at index %zu\n", i);
            free(arr.array);
            return 0;
        }
    }
    
    free(arr.array);
#ifdef DEBUG
    printf("[DEBUG] test_bubble_sort_ponto: Test passed\n");
#endif
    printf("PASS: bubble_sort_ponto\n");
    return 1;
}

static int test_reverse_ponto(void) {
#ifdef DEBUG
    printf("[DEBUG] test_reverse_ponto: Starting test\n");
#endif
    PontoArray arr;
    criar_ponto_array(&arr, 5);
    
    inserir_ponto_array(&arr, (Ponto){1.0, 2.0});
    inserir_ponto_array(&arr, (Ponto){2.0, 4.0});
    inserir_ponto_array(&arr, (Ponto){3.0, 6.0});
    inserir_ponto_array(&arr, (Ponto){4.0, 8.0});
    inserir_ponto_array(&arr, (Ponto){5.0, 10.0});
    
    reverse_ponto_array(&arr);
    
    double expected_x[] = {5.0, 4.0, 3.0, 2.0, 1.0};
    for (size_t i = 0; i < arr.count; i++) {
        if (fabs(arr.array[i].x - expected_x[i]) > 1e-9) {
            printf("FAIL: reverse_ponto - incorrect order at index %zu\n", i);
            free(arr.array);
            return 0;
        }
    }
    
    free(arr.array);
#ifdef DEBUG
    printf("[DEBUG] test_reverse_ponto: Test passed\n");
#endif
    printf("PASS: reverse_ponto\n");
    return 1;
}

static int test_reverse_ponto_even(void) {
#ifdef DEBUG
    printf("[DEBUG] test_reverse_ponto_even: Starting test\n");
#endif
    PontoArray arr;
    criar_ponto_array(&arr, 4);
    
    inserir_ponto_array(&arr, (Ponto){1.0, 2.0});
    inserir_ponto_array(&arr, (Ponto){2.0, 4.0});
    inserir_ponto_array(&arr, (Ponto){3.0, 6.0});
    inserir_ponto_array(&arr, (Ponto){4.0, 8.0});
    
    reverse_ponto_array(&arr);
    
    double expected_x[] = {4.0, 3.0, 2.0, 1.0};
    for (size_t i = 0; i < arr.count; i++) {
        if (fabs(arr.array[i].x - expected_x[i]) > 1e-9) {
            printf("FAIL: reverse_ponto (even) - incorrect order at index %zu\n", i);
            free(arr.array);
            return 0;
        }
    }
    
    free(arr.array);
#ifdef DEBUG
    printf("[DEBUG] test_reverse_ponto_even: Test passed\n");
#endif
    printf("PASS: reverse_ponto (even)\n");
    return 1;
}

int test_ordering(void) {
#ifdef DEBUG
    printf("[DEBUG] test_ordering: Starting test suite\n");
#endif
    printf("\n=== Testing ordering ===\n");
    int passed = 0;
    
    passed += test_bubble_sort_ponto();
    passed += test_reverse_ponto();
    passed += test_reverse_ponto_even();
    
#ifdef DEBUG
    printf("[DEBUG] test_ordering: Test suite completed with %d/3 passed\n", passed);
#endif
    printf("ordering: %d/3 tests passed\n", passed);
    return passed == 3;
}
