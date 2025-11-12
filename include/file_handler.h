#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stddef.h>

FILE* abrir_arquivo(const char *nome_arquivo);
FILE* criar_arquivo(const char *nome_arquivo);
int escrever_int_array(FILE *arquivo, int **array, size_t *count);
int ler_int_array(FILE *arquivo, int **array, size_t *count);
int anexar_int_array(FILE *arquivo, int **array, size_t *size, size_t *count);
int escrever_double_array(FILE *arquivo, double **array, size_t *count);
int ler_double_array(FILE *arquivo, double **array, size_t *count);
int anexar_double_array(FILE *arquivo, double **array, size_t *size, size_t *count);

#endif // FILE_HANDLER_H
