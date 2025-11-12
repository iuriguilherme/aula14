#ifndef DOUBLE_ARRAYS_H
#define DOUBLE_ARRAYS_H

#include <stddef.h>

int criar_double_array(double **array, size_t *size);
int realocar_double_array(double **array, size_t *size, size_t new_size);
int inserir_double_array(double **array, size_t *size, size_t *count, double value);
int inserir_double_array_indice(double **array, size_t *size, size_t *count, size_t index, double value);

#endif // DOUBLE_ARRAYS_H
