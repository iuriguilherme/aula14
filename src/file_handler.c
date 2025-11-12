#include "file_handler.h"
#include "int_arrays.h"
#include "double_arrays.h"
#include "coordinate_arrays.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* abrir_arquivo_modo(const char *nome_arquivo, const char *modo) {
    if (nome_arquivo == NULL) {
        return NULL;
    }
    
    FILE *arquivo = fopen(nome_arquivo, modo);
    
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
        return 0;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%d\n", arr->array[i]);
    }
    
    return 1;
}

int ler_int_array(FILE *arquivo, IntArray *arr) {
    if (arquivo == NULL || arr == NULL) {
        return 0;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_int_array(arr, size)) {
        return 0;
    }
    
    int value;
    while (fscanf(arquivo, "%d", &value) == 1) {
        if (!inserir_int_array(arr, value)) {
            free(arr->array);
            arr->array = NULL;
            return 0;
        }
    }
    
    return 1;
}

int anexar_int_array(FILE *arquivo, IntArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    int value;
    while (fscanf(arquivo, "%d", &value) == 1) {
        if (!inserir_int_array(arr, value)) {
            return 0;
        }
    }
    
    return 1;
}

int escrever_double_array(FILE *arquivo, DoubleArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%lf\n", arr->array[i]);
    }
    
    return 1;
}

int ler_double_array(FILE *arquivo, DoubleArray *arr) {
    if (arquivo == NULL || arr == NULL) {
        return 0;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_double_array(arr, size)) {
        return 0;
    }
    
    double value;
    while (fscanf(arquivo, "%lf", &value) == 1) {
        if (!inserir_double_array(arr, value)) {
            free(arr->array);
            arr->array = NULL;
            return 0;
        }
    }
    
    return 1;
}

int anexar_double_array(FILE *arquivo, DoubleArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    double value;
    while (fscanf(arquivo, "%lf", &value) == 1) {
        if (!inserir_double_array(arr, value)) {
            return 0;
        }
    }
    
    return 1;
}

int escrever_coordinate_array(FILE *arquivo, CoordinateArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%lf %lf\n", arr->array[i].x, arr->array[i].y);
    }
    
    return 1;
}

int ler_coordinate_array(FILE *arquivo, CoordinateArray *arr) {
    if (arquivo == NULL || arr == NULL) {
        return 0;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_coordinate_array(arr, size)) {
        return 0;
    }
    
    Coordinate coord;
    while (fscanf(arquivo, "%lf %lf", &coord.x, &coord.y) == 2) {
        if (!inserir_coordinate_array(arr, coord)) {
            free(arr->array);
            arr->array = NULL;
            return 0;
        }
    }
    
    return 1;
}

int anexar_coordinate_array(FILE *arquivo, CoordinateArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
        return 0;
    }
    
    Coordinate coord;
    while (fscanf(arquivo, "%lf %lf", &coord.x, &coord.y) == 2) {
        if (!inserir_coordinate_array(arr, coord)) {
            return 0;
        }
    }
    
    return 1;
}
