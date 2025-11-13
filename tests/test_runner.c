#include "tests.h"
#include <stdio.h>
#include <stdbool.h>

extern bool test_ponto_arrays(void);
extern bool test_ordering(void);
extern bool test_file_operations(void);
extern bool test_generator(void);

bool run_all_tests(void) {
#ifdef DEBUG
    printf("[DEBUG] run_all_tests: Starting all test suites\n");
#endif
    printf("\n========================================\n");
    printf("       Running All Tests\n");
    printf("========================================\n");
    
    int total_passed = 0;
    int total_suites = 0;
    
    if (test_ponto_arrays()) total_passed++;
    total_suites++;
    
    if (test_ordering()) total_passed++;
    total_suites++;
    
    if (test_file_operations()) total_passed++;
    total_suites++;
    
    if (test_generator()) total_passed++;
    total_suites++;
    
#ifdef DEBUG
    printf("[DEBUG] run_all_tests: All test suites completed - %d/%d passed\n", total_passed, total_suites);
#endif
    printf("\n========================================\n");
    printf("Test Results: %d/%d test suites passed\n", total_passed, total_suites);
    printf("========================================\n\n");
    
    return total_passed == total_suites;
}
