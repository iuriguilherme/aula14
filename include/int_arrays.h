#ifndef INT_ARRAYS_H
#define INT_ARRAYS_H

#include <stddef.h>

int criar_int_array(int **array, size_t *size);
int realocar_int_array(int **array, size_t *size, size_t new_size);
int inserir_int_array(int **array, size_t *size, size_t *count, int value);
int inserir_int_array_indice(int **array, size_t *size, size_t *count, size_t index, int value);

#endif // INT_ARRAYS_H
