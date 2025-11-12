#include "coordinate_arrays.h"
#include <stdlib.h>

int criar_coordinate_array(CoordinateArray *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0;
    }
    
    arr->array = (Coordinate *)malloc(size * sizeof(Coordinate));
    
    if (arr->array == NULL) {
        return 0;
    }
    
    arr->size = size;
    arr->count = 0;
    
    return 1;
}

int realocar_coordinate_array(CoordinateArray *arr, size_t new_size) {
    if (arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    Coordinate *temp = (Coordinate *)realloc(arr->array, new_size * sizeof(Coordinate));
    
    if (temp == NULL) {
        return 0;
    }
    
    arr->array = temp;
    
    if (new_size > arr->size) {
        arr->size = new_size;
    }
    
    return 1;
}

int inserir_coordinate_array(CoordinateArray *arr, Coordinate value) {
    if (arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
        if (!realocar_coordinate_array(arr, new_size)) {
            return 0;
        }
    }
    
    arr->array[arr->count] = value;
    arr->count++;
    
    return 1;
}

int inserir_coordinate_array_indice(CoordinateArray *arr, size_t index, Coordinate value) {
    if (arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    if (index > arr->count) {
        return 0;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
        if (!realocar_coordinate_array(arr, new_size)) {
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
