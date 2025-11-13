#ifndef ORDERING_H
#define ORDERING_H

#include <stddef.h>
#include "structs.h"

void bubble_sort_int(int **array, size_t *count);
void inverter_int_array(int **array, size_t *count);
void reverse_array(int **array, size_t *count);
void bubble_sort_ponto(PontoArray *arr);
void reverse_ponto_array(PontoArray *arr);

#endif // ORDERING_H
