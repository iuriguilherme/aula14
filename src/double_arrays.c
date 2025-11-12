#include "double_arrays.h"
#include <stdlib.h>

int criar_double_array(double **array, size_t *size) {
    if (array == NULL || size == NULL || *size == 0) {
        return 0;
    }
    
    *array = (double *)malloc(*size * sizeof(double));
    
    if (*array == NULL) {
        return 0;
    }
    
    return 1;
}

int realocar_double_array(double **array, size_t *size, size_t new_size) {
    if (array == NULL || *array == NULL || size == NULL) {
        return 0;
    }
    
    double *temp = (double *)realloc(*array, new_size * sizeof(double));
    
    if (temp == NULL) {
        return 0;
    }
    
    *array = temp;
    
    if (new_size > *size) {
        *size = new_size;
    }
    
    return 1;
}

int inserir_double_array(double **array, size_t *size, size_t *count, double value) {
    if (array == NULL || *array == NULL || size == NULL || count == NULL) {
        return 0;
    }
    
    if (*count >= *size) {
        size_t new_size = *size * 2;
        if (!realocar_double_array(array, size, new_size)) {
            return 0;
        }
    }
    
    (*array)[*count] = value;
    (*count)++;
    
    return 1;
}

int inserir_double_array_indice(double **array, size_t *size, size_t *count, size_t index, double value) {
    if (array == NULL || *array == NULL || size == NULL || count == NULL) {
        return 0;
    }
    
    if (index > *count) {
        return 0;
    }
    
    if (*count >= *size) {
        size_t new_size = *size * 2;
        if (!realocar_double_array(array, size, new_size)) {
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
