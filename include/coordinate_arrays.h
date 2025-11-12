#ifndef COORDINATE_ARRAYS_H
#define COORDINATE_ARRAYS_H

#include "structs.h"

int criar_coordinate_array(CoordinateArray *arr, size_t size);
int realocar_coordinate_array(CoordinateArray *arr, size_t new_size);
int inserir_coordinate_array(CoordinateArray *arr, Coordinate value);
int inserir_coordinate_array_indice(CoordinateArray *arr, size_t index, Coordinate value);

#endif // COORDINATE_ARRAYS_H
