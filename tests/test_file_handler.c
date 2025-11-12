#include "tests.h"
#include "file_handler.h"
#include "int_arrays.h"
#include "double_arrays.h"
#include "coordinate_arrays.h"
#include <stdio.h>
#include <stdlib.h>

int test_file_operations(void) {
    printf("\n=== Testing file_handler ===\n");
    
    // Test int array file operations
    IntArray arr1;
    criar_int_array(&arr1, 5);
    inserir_int_array(&arr1, 10);
    inserir_int_array(&arr1, 20);
    inserir_int_array(&arr1, 30);
    
    FILE *f = criar_arquivo("test_int.txt");
    if (!f || !escrever_int_array(f, &arr1)) {
        printf("FAIL: file_handler - failed to write int array\n");
        if (f) fclose(f);
        free(arr1.array);
        return 0;
    }
    fclose(f);
    
    IntArray arr2;
    f = abrir_arquivo("test_int.txt");
    if (!f || !ler_int_array(f, &arr2)) {
        printf("FAIL: file_handler - failed to read int array\n");
        if (f) fclose(f);
        free(arr1.array);
        return 0;
    }
    fclose(f);
    
    if (arr2.count != arr1.count) {
        printf("FAIL: file_handler - count mismatch\n");
        free(arr1.array);
        free(arr2.array);
        return 0;
    }
    
    for (size_t i = 0; i < arr1.count; i++) {
        if (arr1.array[i] != arr2.array[i]) {
            printf("FAIL: file_handler - value mismatch at index %zu\n", i);
            free(arr1.array);
            free(arr2.array);
            return 0;
        }
    }
    
    free(arr1.array);
    free(arr2.array);
    printf("PASS: file_handler int array operations\n");
    printf("file_handler: 1/1 tests passed\n");
    return 1;
}
