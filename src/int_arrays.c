#include "int_arrays.h"
#include <stdlib.h>

int criar_int_array(int **array, size_t *size) {
    if (array == NULL || size == NULL || *size == 0) {
        return 0;
    }
    
    *array = (int *)malloc(*size * sizeof(int));
    
    if (*array == NULL) {
        return 0;
    }
    
    return 1;
}

int realocar_int_array(int **array, size_t *size, size_t new_size) {
    if (array == NULL || *array == NULL || size == NULL) {
        return 0;
    }
    
    int *temp = (int *)realloc(*array, new_size * sizeof(int));
    
    if (temp == NULL) {
        return 0;
    }
    
    *array = temp;
    
    if (new_size > *size) {
        *size = new_size;
    }
    
    return 1;
}

int inserir_int_array(int **array, size_t *size, size_t *count, int value) {
    if (array == NULL || *array == NULL || size == NULL || count == NULL) {
        return 0;
    }
    
    if (*count >= *size) {
        size_t new_size = *size * 2;
        if (!realocar_int_array(array, size, new_size)) {
            return 0;
        }
    }
    
    (*array)[*count] = value;
    (*count)++;
    
    return 1;
}

int inserir_int_array_indice(int **array, size_t *size, size_t *count, size_t index, int value) {
    if (array == NULL || *array == NULL || size == NULL || count == NULL) {
        return 0;
    }
    
    if (index > *count) {
        index = *count;
    }
    
    if (*count >= *size) {
        size_t new_size = *size * 2;
        if (!realocar_int_array(array, size, new_size)) {
            return 0;
        }
    }
    
    for (size_t i = *count; i > index; i--) {
        (*array)[i] = (*array)[i - 1];
    }
    
    (*array)[index] = value;
    (*count)++;
    
    return 1;
}
