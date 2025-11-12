#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stddef.h>
#include "structs.h"

FILE* abrir_arquivo(const char *nome_arquivo);
FILE* criar_arquivo(const char *nome_arquivo);
int escrever_int_array(FILE *arquivo, IntArray *arr);
int ler_int_array(FILE *arquivo, IntArray *arr);
int anexar_int_array(FILE *arquivo, IntArray *arr);
int escrever_double_array(FILE *arquivo, DoubleArray *arr);
int ler_double_array(FILE *arquivo, DoubleArray *arr);
int anexar_double_array(FILE *arquivo, DoubleArray *arr);
int escrever_coordinate_array(FILE *arquivo, CoordinateArray *arr);
int ler_coordinate_array(FILE *arquivo, CoordinateArray *arr);
int anexar_coordinate_array(FILE *arquivo, CoordinateArray *arr);

#endif // FILE_HANDLER_H
