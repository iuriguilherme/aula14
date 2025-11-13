#include "pontos.h"
#include <stdlib.h>
#include <stdio.h>

bool criar_ponto_array(PontoArray *arr, size_t size) {
    if (arr == NULL || size == 0) {
#ifdef VERBOSE
        printf("[DEBUG] criar_ponto_array: Invalid parameters (arr=%p, size=%zu)\n", 
               (void*)arr, size);
#endif
        return false;
    }
    
    arr->array = (Ponto *)malloc(size * sizeof(Ponto));
    
    if (arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] criar_ponto_array: malloc failed for size %zu\n", size);
#endif
        return false;
    }
    
    arr->size = size;
    arr->count = 0;
    
#ifdef VERBOSE
    printf("[DEBUG] criar_ponto_array: Successfully created array with size %zu\n", size);
#endif
    return true;
}

bool realocar_ponto_array(PontoArray *arr, size_t new_size) {
    if (arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] realocar_ponto_array: Invalid parameters (arr=%p, arr->array=%p)\n", 
               (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return false;
    }
    
    Ponto *temp = (Ponto *)realloc(arr->array, new_size * sizeof(Ponto));
    
    if (temp == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] realocar_ponto_array: realloc failed from size %zu to %zu\n", 
               arr->size, new_size);
#endif
        return false;
    }
    
    arr->array = temp;
    
    if (new_size > arr->size) {
        arr->size = new_size;
    }
    
#ifdef VERBOSE
    printf("[DEBUG] realocar_ponto_array: Successfully reallocated to size %zu\n", new_size);
#endif
    return true;
}

bool inserir_ponto_array(PontoArray *arr, Ponto value) {
    if (arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] inserir_ponto_array: Invalid parameters (arr=%p, arr->array=%p)\n", 
               (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return false;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
#ifdef VERBOSE
        printf("[DEBUG] inserir_ponto_array: Reallocating from %zu to %zu\n", 
               arr->size, new_size);
#endif
        if (!realocar_ponto_array(arr, new_size)) {
#ifdef VERBOSE
            printf("[DEBUG] inserir_ponto_array: Reallocation failed\n");
#endif
            return false;
        }
    }
    
    arr->array[arr->count] = value;
    arr->count++;
    
#ifdef VERBOSE
    printf("[DEBUG] inserir_ponto_array: Inserted ponto (%.2f, %.2f) at index %zu\n", 
           value.x, value.y, arr->count - 1);
#endif
    return true;
}

bool inserir_ponto_array_indice(PontoArray *arr, size_t index, Ponto value) {
    if (arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] inserir_ponto_array_indice: Invalid parameters (arr=%p, arr->array=%p)\n", 
               (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return false;
    }
    
    if (index > arr->count) {
#ifdef VERBOSE
        printf("[DEBUG] inserir_ponto_array_indice: Invalid index %zu (count=%zu)\n", 
               index, arr->count);
#endif
        return false;
    }
    
    if (arr->count >= arr->size) {
        size_t new_size = arr->size * 2;
#ifdef VERBOSE
        printf("[DEBUG] inserir_ponto_array_indice: Reallocating from %zu to %zu\n", 
               arr->size, new_size);
#endif
        if (!realocar_ponto_array(arr, new_size)) {
#ifdef VERBOSE
            printf("[DEBUG] inserir_ponto_array_indice: Reallocation failed\n");
#endif
            return false;
        }
    }
    
    for (size_t i = arr->count; i > index; i--) {
        arr->array[i] = arr->array[i - 1];
    }
    
    arr->array[index] = value;
    arr->count++;
    
#ifdef VERBOSE
    printf("[DEBUG] inserir_ponto_array_indice: Inserted ponto (%.2f, %.2f) at index %zu\n", 
           value.x, value.y, index);
#endif
    return true;
}
