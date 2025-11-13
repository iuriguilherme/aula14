#ifndef STRUCTS_H
#define STRUCTS_H

#include <stddef.h>

typedef struct {
    double x;
    double y;
} Ponto;

typedef struct {
    size_t size;
    size_t count;
    Ponto *array;
} PontoArray;

#endif // STRUCTS_H
