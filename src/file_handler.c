#include "file_handler.h"
#include "int_arrays.h"
#include "double_arrays.h"
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

int escrever_int_array(FILE *arquivo, int **array, size_t *count) {
    if (arquivo == NULL || array == NULL || *array == NULL || count == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < *count; i++) {
        fprintf(arquivo, "%d\n", (*array)[i]);
    }
    
    return 1;
}

int ler_int_array(FILE *arquivo, int **array, size_t *count) {
    if (arquivo == NULL || array == NULL || count == NULL) {
        return 0;
    }
    
    *count = 0;
    size_t size = 10;
    
    if (!criar_int_array(array, &size)) {
        return 0;
    }
    
    int value;
    while (fscanf(arquivo, "%d", &value) == 1) {
        if (!inserir_int_array(array, &size, count, value)) {
            free(*array);
            *array = NULL;
            return 0;
        }
    }
    
    return 1;
}

int anexar_int_array(FILE *arquivo, int **array, size_t *size, size_t *count) {
    if (arquivo == NULL || array == NULL || *array == NULL || size == NULL || count == NULL) {
        return 0;
    }
    
    int value;
    while (fscanf(arquivo, "%d", &value) == 1) {
        if (!inserir_int_array(array, size, count, value)) {
            return 0;
        }
    }
    
    return 1;
}

int escrever_double_array(FILE *arquivo, double **array, size_t *count) {
    if (arquivo == NULL || array == NULL || *array == NULL || count == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < *count; i++) {
        fprintf(arquivo, "%lf\n", (*array)[i]);
    }
    
    return 1;
}

int ler_double_array(FILE *arquivo, double **array, size_t *count) {
    if (arquivo == NULL || array == NULL || count == NULL) {
        return 0;
    }
    
    *count = 0;
    size_t size = 10;
    
    if (!criar_double_array(array, &size)) {
        return 0;
    }
    
    double value;
    while (fscanf(arquivo, "%lf", &value) == 1) {
        if (!inserir_double_array(array, &size, count, value)) {
            free(*array);
            *array = NULL;
            return 0;
        }
    }
    
    return 1;
}

int anexar_double_array(FILE *arquivo, double **array, size_t *size, size_t *count) {
    if (arquivo == NULL || array == NULL || *array == NULL || size == NULL || count == NULL) {
        return 0;
    }
    
    double value;
    while (fscanf(arquivo, "%lf", &value) == 1) {
        if (!inserir_double_array(array, size, count, value)) {
            return 0;
        }
    }
    
    return 1;
}
