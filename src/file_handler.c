#include "file_handler.h"
#include "int_arrays.h"
#include "double_arrays.h"
#include "coordinate_arrays.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* abrir_arquivo_modo(const char *nome_arquivo, const char *modo) {
    if (nome_arquivo == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] abrir_arquivo_modo: nome_arquivo is NULL\n");
#endif
        return NULL;
    }
    
    FILE *arquivo = fopen(nome_arquivo, modo);
    
#ifdef VERBOSE
    if (arquivo == NULL) {
        printf("[DEBUG] abrir_arquivo_modo: Failed to open '%s' with mode '%s'\n", nome_arquivo, modo);
    } else {
        printf("[DEBUG] abrir_arquivo_modo: Successfully opened '%s' with mode '%s'\n", nome_arquivo, modo);
    }
#endif
    
    return arquivo;
}

FILE* abrir_arquivo(const char *nome_arquivo) {
    return abrir_arquivo_modo(nome_arquivo, "r");
}

FILE* criar_arquivo(const char *nome_arquivo) {
    return abrir_arquivo_modo(nome_arquivo, "w");
}

int escrever_int_array(FILE *arquivo, IntArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] escrever_int_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%d\n", arr->array[i]);
    }
    
#ifdef VERBOSE
    printf("[DEBUG] escrever_int_array: Successfully wrote %zu integers\n", arr->count);
#endif
    return 1;
}

int ler_int_array(FILE *arquivo, IntArray *arr) {
    if (arquivo == NULL || arr == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] ler_int_array: Invalid parameters (arquivo=%p, arr=%p)\n", 
               (void*)arquivo, (void*)arr);
#endif
        return 0;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_int_array(arr, size)) {
#ifdef VERBOSE
        printf("[DEBUG] ler_int_array: Failed to create int array\n");
#endif
        return 0;
    }
    
    int value;
    while (fscanf(arquivo, "%d", &value) == 1) {
        if (!inserir_int_array(arr, value)) {
            free(arr->array);
            arr->array = NULL;
#ifdef VERBOSE
            printf("[DEBUG] ler_int_array: Failed to insert value, freed array\n");
#endif
            return 0;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] ler_int_array: Successfully read %zu integers\n", arr->count);
#endif
    return 1;
}

int anexar_int_array(FILE *arquivo, IntArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] anexar_int_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    int value;
    size_t initial_count = arr->count;
    while (fscanf(arquivo, "%d", &value) == 1) {
        if (!inserir_int_array(arr, value)) {
#ifdef VERBOSE
            printf("[DEBUG] anexar_int_array: Failed to insert value\n");
#endif
            return 0;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] anexar_int_array: Successfully appended %zu integers\n", arr->count - initial_count);
#endif
    return 1;
}

int escrever_double_array(FILE *arquivo, DoubleArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] escrever_double_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%lf\n", arr->array[i]);
    }
    
#ifdef VERBOSE
    printf("[DEBUG] escrever_double_array: Successfully wrote %zu doubles\n", arr->count);
#endif
    return 1;
}

int ler_double_array(FILE *arquivo, DoubleArray *arr) {
    if (arquivo == NULL || arr == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] ler_double_array: Invalid parameters (arquivo=%p, arr=%p)\n", 
               (void*)arquivo, (void*)arr);
#endif
        return 0;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_double_array(arr, size)) {
#ifdef VERBOSE
        printf("[DEBUG] ler_double_array: Failed to create double array\n");
#endif
        return 0;
    }
    
    double value;
    while (fscanf(arquivo, "%lf", &value) == 1) {
        if (!inserir_double_array(arr, value)) {
            free(arr->array);
            arr->array = NULL;
#ifdef VERBOSE
            printf("[DEBUG] ler_double_array: Failed to insert value, freed array\n");
#endif
            return 0;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] ler_double_array: Successfully read %zu doubles\n", arr->count);
#endif
    return 1;
}

int anexar_double_array(FILE *arquivo, DoubleArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] anexar_double_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    double value;
    size_t initial_count = arr->count;
    while (fscanf(arquivo, "%lf", &value) == 1) {
        if (!inserir_double_array(arr, value)) {
#ifdef VERBOSE
            printf("[DEBUG] anexar_double_array: Failed to insert value\n");
#endif
            return 0;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] anexar_double_array: Successfully appended %zu doubles\n", arr->count - initial_count);
#endif
    return 1;
}

int escrever_coordinate_array(FILE *arquivo, CoordinateArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] escrever_coordinate_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%lf %lf\n", arr->array[i].x, arr->array[i].y);
    }
    
#ifdef VERBOSE
    printf("[DEBUG] escrever_coordinate_array: Successfully wrote %zu coordinates\n", arr->count);
#endif
    return 1;
}

int ler_coordinate_array(FILE *arquivo, CoordinateArray *arr) {
    if (arquivo == NULL || arr == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] ler_coordinate_array: Invalid parameters (arquivo=%p, arr=%p)\n", 
               (void*)arquivo, (void*)arr);
#endif
        return 0;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_coordinate_array(arr, size)) {
#ifdef VERBOSE
        printf("[DEBUG] ler_coordinate_array: Failed to create coordinate array\n");
#endif
        return 0;
    }
    
    Coordinate coord;
    while (fscanf(arquivo, "%lf %lf", &coord.x, &coord.y) == 2) {
        if (!inserir_coordinate_array(arr, coord)) {
            free(arr->array);
            arr->array = NULL;
#ifdef VERBOSE
            printf("[DEBUG] ler_coordinate_array: Failed to insert coordinate, freed array\n");
#endif
            return 0;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] ler_coordinate_array: Successfully read %zu coordinates\n", arr->count);
#endif
    return 1;
}

int anexar_coordinate_array(FILE *arquivo, CoordinateArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] anexar_coordinate_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return 0;
    }
    
    Coordinate coord;
    size_t initial_count = arr->count;
    while (fscanf(arquivo, "%lf %lf", &coord.x, &coord.y) == 2) {
        if (!inserir_coordinate_array(arr, coord)) {
#ifdef VERBOSE
            printf("[DEBUG] anexar_coordinate_array: Failed to insert coordinate\n");
#endif
            return 0;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] anexar_coordinate_array: Successfully appended %zu coordinates\n", arr->count - initial_count);
#endif
    return 1;
}
