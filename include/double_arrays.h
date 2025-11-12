#ifndef DOUBLE_ARRAYS_H
#define DOUBLE_ARRAYS_H

#include "structs.h"

int criar_double_array(DoubleArray *arr, size_t size);
int realocar_double_array(DoubleArray *arr, size_t new_size);
int inserir_double_array(DoubleArray *arr, double value);
int inserir_double_array_indice(DoubleArray *arr, size_t index, double value);

#endif // DOUBLE_ARRAYS_H
