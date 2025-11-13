#include "tests.h"
#include <stdio.h>

int main(void) {
#ifdef DEBUG
    printf("[DEBUG] Test suite running in DEBUG mode\n");
#endif
    printf("Starting tests...\n");
    
    if (run_all_tests()) {
        printf("All tests passed!\n");
        return 0;
    } else {
        printf("Some tests failed!\n");
        return 1;
    }
}
