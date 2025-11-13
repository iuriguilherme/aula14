#include "tests.h"
#include "file_handler.h"
#include "pontos.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

bool test_file_operations(void) {
#ifdef DEBUG
    printf("[DEBUG] test_file_operations: Starting test\n");
#endif
    printf("\n=== Testing file_handler ===\n");
    
    // Test ponto array file operations
    PontoArray arr1;
    criar_ponto_array(&arr1, 3);
    inserir_ponto_array(&arr1, (Ponto){1.0, 2.0});
    inserir_ponto_array(&arr1, (Ponto){3.0, 6.0});
    inserir_ponto_array(&arr1, (Ponto){5.0, 10.0});
    
#ifdef DEBUG
    printf("[DEBUG] test_file_operations: Created test array with %zu points\n", arr1.count);
#endif
    FILE *f = criar_arquivo("test_pontos.txt");
    if (!f || !escrever_ponto_array(f, &arr1)) {
        printf("FAIL: file_handler - failed to write ponto array\n");
        if (f) fclose(f);
        free(arr1.array);
        return false;
    }
    fclose(f);
    
#ifdef DEBUG
    printf("[DEBUG] test_file_operations: Successfully wrote points to file\n");
#endif
    PontoArray arr2;
    f = abrir_arquivo("test_pontos.txt");
    if (!f || !ler_ponto_array(f, &arr2)) {
        printf("FAIL: file_handler - failed to read ponto array\n");
        if (f) fclose(f);
        free(arr1.array);
        return false;
    }
    fclose(f);
    
#ifdef DEBUG
    printf("[DEBUG] test_file_operations: Successfully read %zu points from file\n", arr2.count);
#endif
    if (arr2.count != arr1.count) {
        printf("FAIL: file_handler - count mismatch\n");
        free(arr1.array);
        free(arr2.array);
        return false;
    }
    
    for (size_t i = 0; i < arr1.count; i++) {
        if (fabs(arr1.array[i].x - arr2.array[i].x) > 1e-9 || 
            fabs(arr1.array[i].y - arr2.array[i].y) > 1e-9) {
            printf("FAIL: file_handler - value mismatch at index %zu\n", i);
            free(arr1.array);
            free(arr2.array);
            return false;
        }
    }
    
    free(arr1.array);
    free(arr2.array);
    
    // Cleanup test file
    unlink("test_pontos.txt");
    
#ifdef DEBUG
    printf("[DEBUG] test_file_operations: Test passed\n");
#endif
    printf("PASS: file_handler ponto array operations\n");
    printf("file_handler: 1/1 tests passed\n");
    return true;
}
