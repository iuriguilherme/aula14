#ifndef INT_ARRAYS_H
#define INT_ARRAYS_H

#include "structs.h"

int criar_int_array(IntArray *arr, size_t size);
int realocar_int_array(IntArray *arr, size_t new_size);
int inserir_int_array(IntArray *arr, int value);
int inserir_int_array_indice(IntArray *arr, size_t index, int value);

#endif // INT_ARRAYS_H
