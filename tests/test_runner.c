#include "tests.h"
#include <stdio.h>

extern int test_int_arrays(void);
extern int test_double_arrays(void);
extern int test_coordinate_arrays(void);
extern int test_ordering(void);
extern int test_file_operations(void);

int run_all_tests(void) {
    printf("\n========================================\n");
    printf("       Running All Tests\n");
    printf("========================================\n");
    
    int total_passed = 0;
    int total_suites = 0;
    
    if (test_int_arrays()) total_passed++;
    total_suites++;
    
    if (test_double_arrays()) total_passed++;
    total_suites++;
    
    if (test_coordinate_arrays()) total_passed++;
    total_suites++;
    
    if (test_ordering()) total_passed++;
    total_suites++;
    
    if (test_file_operations()) total_passed++;
    total_suites++;
    
    printf("\n========================================\n");
    printf("Test Results: %d/%d test suites passed\n", total_passed, total_suites);
    printf("========================================\n\n");
    
    return total_passed == total_suites;
}
