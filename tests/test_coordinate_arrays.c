#include "tests.h"
#include "coordinate_arrays.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int test_criar_coordinate_array(void) {
    CoordinateArray arr;
    
    if (!criar_coordinate_array(&arr, 10)) {
        printf("FAIL: criar_coordinate_array - failed to create array\n");
        return 0;
    }
    
    if (arr.size != 10 || arr.count != 0 || arr.array == NULL) {
        printf("FAIL: criar_coordinate_array - incorrect initialization\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: criar_coordinate_array\n");
    return 1;
}

static int test_inserir_coordinate_array(void) {
    CoordinateArray arr;
    criar_coordinate_array(&arr, 2);
    
    Coordinate c1 = {1.0, 2.0};
    if (!inserir_coordinate_array(&arr, c1)) {
        printf("FAIL: inserir_coordinate_array - failed to insert first element\n");
        free(arr.array);
        return 0;
    }
    
    if (arr.count != 1 || fabs(arr.array[0].x - 1.0) > 0.001 || fabs(arr.array[0].y - 2.0) > 0.001) {
        printf("FAIL: inserir_coordinate_array - incorrect value or count\n");
        free(arr.array);
        return 0;
    }
    
    Coordinate c2 = {3.0, 4.0};
    Coordinate c3 = {5.0, 6.0};
    inserir_coordinate_array(&arr, c2);
    inserir_coordinate_array(&arr, c3); // Should trigger reallocation
    
    if (arr.count != 3 || arr.size < 3) {
        printf("FAIL: inserir_coordinate_array - reallocation failed\n");
        free(arr.array);
        return 0;
    }
    
    free(arr.array);
    printf("PASS: inserir_coordinate_array\n");
    return 1;
}

int test_coordinate_arrays(void) {
    printf("\n=== Testing coordinate_arrays ===\n");
    int passed = 0;
    
    passed += test_criar_coordinate_array();
    passed += test_inserir_coordinate_array();
    
    printf("coordinate_arrays: %d/2 tests passed\n", passed);
    return passed == 2;
}
