#include "file_handler.h"
#include "pontos.h"
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

bool escrever_ponto_array(FILE *arquivo, PontoArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] escrever_ponto_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return false;
    }
    
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(arquivo, "%lf %lf\n", arr->array[i].x, arr->array[i].y);
    }
    
#ifdef VERBOSE
    printf("[DEBUG] escrever_ponto_array: Successfully wrote %zu pontos\n", arr->count);
#endif
    return true;
}

bool ler_ponto_array(FILE *arquivo, PontoArray *arr) {
    if (arquivo == NULL || arr == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] ler_ponto_array: Invalid parameters (arquivo=%p, arr=%p)\n", 
               (void*)arquivo, (void*)arr);
#endif
        return false;
    }
    
    arr->count = 0;
    size_t size = 10;
    
    if (!criar_ponto_array(arr, size)) {
#ifdef VERBOSE
        printf("[DEBUG] ler_ponto_array: Failed to create ponto array\n");
#endif
        return false;
    }
    
    Ponto coord;
    while (fscanf(arquivo, "%lf %lf", &coord.x, &coord.y) == 2) {
        if (!inserir_ponto_array(arr, coord)) {
            free(arr->array);
            arr->array = NULL;
#ifdef VERBOSE
            printf("[DEBUG] ler_ponto_array: Failed to insert ponto, freed array\n");
#endif
            return false;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] ler_ponto_array: Successfully read %zu pontos\n", arr->count);
#endif
    return true;
}

bool anexar_ponto_array(FILE *arquivo, PontoArray *arr) {
    if (arquivo == NULL || arr == NULL || arr->array == NULL) {
#ifdef VERBOSE
        printf("[DEBUG] anexar_ponto_array: Invalid parameters (arquivo=%p, arr=%p, arr->array=%p)\n", 
               (void*)arquivo, (void*)arr, arr ? (void*)arr->array : NULL);
#endif
        return false;
    }
    
    size_t initial_count = arr->count;
    Ponto coord;
    while (fscanf(arquivo, "%lf %lf", &coord.x, &coord.y) == 2) {
        if (!inserir_ponto_array(arr, coord)) {
#ifdef VERBOSE
            printf("[DEBUG] anexar_ponto_array: Failed to insert ponto\n");
#endif
            return false;
        }
    }
    
#ifdef VERBOSE
    printf("[DEBUG] anexar_ponto_array: Successfully appended %zu pontos\n", arr->count - initial_count);
#endif
    return true;
}
