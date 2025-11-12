#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>

typedef struct {
    size_t size;
    size_t count;
    int *array;
} IntArray;

typedef struct {
    size_t size;
    size_t count;
    double *array;
} DoubleArray;

typedef struct {
    double x;
    double y;
} Coordinate;

typedef struct {
    size_t size;
    size_t count;
    Coordinate *array;
} CoordinateArray;

#endif // STRUCTS_H
