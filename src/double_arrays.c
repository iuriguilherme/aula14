#include "double_arrays.h"
#include <stdlib.h>

int criar_double_array(DoubleArray *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    arr->array = (double *)malloc(size * sizeof(double));
    
    if (arr->array == NULL) {
        return 0;
    }
    
    arr->size = size;
    arr->count = 0;
    
    return 1;
}

int realocar_double_array(DoubleArray *arr, size_t new_size) {
    if (arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    double *temp = (double *)realloc(arr->array, new_size * sizeof(double));
    
    if (temp == NULL) {
        return 0;
    }
    
    arr->array = temp;
    
    if (new_size > arr->size) {
        arr->size = new_size;
    }
    
    return 1;
}

int inserir_double_array(DoubleArray *arr, double value) {
    if (arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
        if (!realocar_double_array(arr, new_size)) {
            return 0;
        }
    }
    
    arr->array[arr->count] = value;
    arr->count++;
    
    return 1;
}

int inserir_double_array_indice(DoubleArray *arr, size_t index, double value) {
    if (arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    if (index > arr->count) {
        return 0;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
        if (!realocar_double_array(arr, new_size)) {
            return 0;
        }
    }
    
    for (size_t i = arr->count; i > index; i--) {
        arr->array[i] = arr->array[i - 1];
    }
    
    arr->array[index] = value;
    arr->count++;
    
    return 1;
}
