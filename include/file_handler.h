#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>
#include <stddef.h>
#include "structs.h"

FILE* abrir_arquivo(const char *nome_arquivo);
FILE* criar_arquivo(const char *nome_arquivo);
int escrever_ponto_array(FILE *arquivo, PontoArray *arr);
int ler_ponto_array(FILE *arquivo, PontoArray *arr);
int anexar_ponto_array(FILE *arquivo, PontoArray *arr);

#endif // FILE_HANDLER_H
