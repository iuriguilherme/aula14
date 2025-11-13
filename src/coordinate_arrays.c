#include "coordinate_arrays.h"
#include <stdlib.h>
#include <stdio.h>

int criar_coordinate_array(CoordinateArray *arr, size_t size) {
    if (arr == NULL || size == 0) {
#ifdef VERBOSE
        printf("[DEBUG] criar_coordinate_array: Invalid parameters (arr=%p, size=%zu)\n", 
               (void*)arr, size);
#endif
        return 0;
    }
    
    arr->array = (Coordinate *)malloc(size * sizeof(Coordinate));
    
    if (arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] criar_coordinate_array: malloc failed for size %zu\n", size);
#endif
        return 0;
    }
    
    arr->size = size;
    arr->count = 0;
    
#ifdef VERBOSE
    printf("[DEBUG] criar_coordinate_array: Successfully created array with size %zu\n", size);
#endif
    return 1;
}

int realocar_coordinate_array(CoordinateArray *arr, size_t new_size) {
    if (arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] realocar_coordinate_array: Invalid parameters (arr=%p, arr->array=%p)\n", 
               (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    Coordinate *temp = (Coordinate *)realloc(arr->array, new_size * sizeof(Coordinate));
    
    if (temp == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] realocar_coordinate_array: realloc failed from size %zu to %zu\n", 
               arr->size, new_size);
#endif
        return 0;
    }
    
    arr->array = temp;
    
    if (new_size > arr->size) {
        arr->size = new_size;
    }
    
#ifdef VERBOSE
    printf("[DEBUG] realocar_coordinate_array: Successfully reallocated to size %zu\n", new_size);
#endif
    return 1;
}

int inserir_coordinate_array(CoordinateArray *arr, Coordinate value) {
    if (arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] inserir_coordinate_array: Invalid parameters (arr=%p, arr->array=%p)\n", 
               (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
#ifdef VERBOSE
        printf("[DEBUG] inserir_coordinate_array: Reallocating from %zu to %zu\n", 
               arr->size, new_size);
#endif
        if (!realocar_coordinate_array(arr, new_size)) {
#ifdef VERBOSE
            printf("[DEBUG] inserir_coordinate_array: Reallocation failed\n");
#endif
            return 0;
        }
    }
    
    arr->array[arr->count] = value;
    arr->count++;
    
#ifdef VERBOSE
    printf("[DEBUG] inserir_coordinate_array: Inserted coordinate (%.2f, %.2f) at index %zu\n", 
           value.x, value.y, arr->count - 1);
#endif
    return 1;
}

int inserir_coordinate_array_indice(CoordinateArray *arr, size_t index, Coordinate value) {
    if (arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] inserir_coordinate_array_indice: Invalid parameters (arr=%p, arr->array=%p)\n", 
               (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    if (index > arr->count) {
#ifdef VERBOSE
        printf("[DEBUG] inserir_coordinate_array_indice: Invalid index %zu (count=%zu)\n", 
               index, arr->count);
#endif
        return 0;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
#ifdef VERBOSE
        printf("[DEBUG] inserir_coordinate_array_indice: Reallocating from %zu to %zu\n", 
               arr->size, new_size);
#endif
        if (!realocar_coordinate_array(arr, new_size)) {
#ifdef VERBOSE
            printf("[DEBUG] inserir_coordinate_array_indice: Reallocation failed\n");
#endif
            return 0;
        }
    }
    
    for (size_t i = arr->count; i > index; i--) {
        arr->array[i] = arr->array[i - 1];
    }
    
    arr->array[index] = value;
    arr->count++;
    
#ifdef VERBOSE
    printf("[DEBUG] inserir_coordinate_array_indice: Inserted coordinate (%.2f, %.2f) at index %zu\n", 
           value.x, value.y, index);
#endif
    return 1;
}
