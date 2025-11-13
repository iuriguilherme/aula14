#ifndef PONTOS_H
#define PONTOS_H

#include "structs.h"
#include <stddef.h>

int criar_ponto_array(PontoArray *arr, size_t size);
int realocar_ponto_array(PontoArray *arr, size_t new_size);
int inserir_ponto_array(PontoArray *arr, Ponto value);
int inserir_ponto_array_indice(PontoArray *arr, size_t index, Ponto value);

#endif // PONTOS_H
