#include "tests.h"
#include "generator.h"
#include "pontos.h"
#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdbool.h>

bool test_generator(void) {
#ifdef DEBUG
    printf("[DEBUG] test_generator: Starting test suite\n");
#endif
    printf("\n--- Testing Generator Functions ---\n");
    int tests_passed = 0;
    int total_tests = 3;
    
    // Test 1: Check if file is created
#ifdef DEBUG
    printf("[DEBUG] test_generator: Test 1 - File creation\n");
#endif
    printf("Test 1: File creation... ");
    const char *test_file = "test_pontos_temp.txt";
    
    // Remove file if it exists
    unlink(test_file);
    
    // Since gerar_pontos requires user input, we'll test the file operations directly
    // Create a simple coordinate array and write it
    PontoArray arr;
    criar_ponto_array(&arr, 3);
    
    Ponto c1 = {1.0, 2.0};
    Ponto c2 = {2.0, 4.0};
    Ponto c3 = {3.0, 6.0};
    
    inserir_ponto_array(&arr, c1);
    inserir_ponto_array(&arr, c2);
    inserir_ponto_array(&arr, c3);
    
#ifdef DEBUG
    printf("[DEBUG] test_generator: Created array with %zu points\n", arr.count);
#endif
    FILE *file = criar_arquivo(test_file);
    if (file && escrever_ponto_array(file, &arr)) {
        fclose(file);
        
        // Check if file exists
        struct stat buffer;
        if (stat(test_file, &buffer) == 0) {
            printf("PASSED\n");
            tests_passed++;
        } else {
            printf("FAILED (file not created)\n");
        }
    } else {
        if (file) fclose(file);
        printf("FAILED (write error)\n");
    }
    
    free(arr.array);
    
    // Test 2: Verify file content can be read back
#ifdef DEBUG
    printf("[DEBUG] test_generator: Test 2 - File read/write integrity\n");
#endif
    printf("Test 2: File read/write integrity... ");
    PontoArray arr2;
    criar_ponto_array(&arr2, 10);
    
    file = abrir_arquivo(test_file);
    if (file && ler_ponto_array(file, &arr2)) {
        fclose(file);
        
        if (arr2.count == 3 &&
            arr2.array[0].x == 1.0 && arr2.array[0].y == 2.0 &&
            arr2.array[1].x == 2.0 && arr2.array[1].y == 4.0 &&
            arr2.array[2].x == 3.0 && arr2.array[2].y == 6.0) {
            printf("PASSED\n");
            tests_passed++;
        } else {
            printf("FAILED (data mismatch)\n");
        }
    } else {
        if (file) fclose(file);
        printf("FAILED (read error)\n");
    }
    
    free(arr2.array);
    
    // Test 3: File cleanup
#ifdef DEBUG
    printf("[DEBUG] test_generator: Test 3 - File cleanup\n");
#endif
    printf("Test 3: File cleanup... ");
    if (unlink(test_file) == 0) {
        printf("PASSED\n");
        tests_passed++;
    } else {
        printf("FAILED (cleanup error)\n");
    }
    
#ifdef DEBUG
    printf("[DEBUG] test_generator: Test suite completed with %d/%d passed\n", tests_passed, total_tests);
#endif
    printf("\nGenerator tests: %d/%d passed\n", tests_passed, total_tests);
    return tests_passed == total_tests;
}
