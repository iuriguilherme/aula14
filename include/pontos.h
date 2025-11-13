#ifndef PONTOS_H
#define PONTOS_H

#include "structs.h"
#include <stddef.h>
#include <stdbool.h>

bool criar_ponto_array(PontoArray *arr, size_t size);
bool realocar_ponto_array(PontoArray *arr, size_t new_size);
bool inserir_ponto_array(PontoArray *arr, Ponto value);
bool inserir_ponto_array_indice(PontoArray *arr, size_t index, Ponto value);

#endif // PONTOS_H
