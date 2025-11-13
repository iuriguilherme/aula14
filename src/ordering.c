#include "ordering.h"

void bubble_sort_int(int **array, size_t *count) {
    if (array == NULL || *array == NULL || count == NULL || *count <= 1) {
        return;
    }
    
    for (size_t i = 0; i < *count - 1; i++) {
        for (size_t j = 0; j < *count - i - 1; j++) {
            if ((*array)[j] > (*array)[j + 1]) {
                int temp = (*array)[j];
                (*array)[j] = (*array)[j + 1];
                (*array)[j + 1] = temp;
            }
        }
    }
}

void inverter_int_array(int **array, size_t *count) {
    if (array == NULL || *array == NULL || count == NULL || *count <= 1) {
        return;
    }
    
    for (size_t i = 0; i < *count / 2; i++) {
        int temp = (*array)[i];
        (*array)[i] = (*array)[*count - 1 - i];
        (*array)[*count - 1 - i] = temp;
    }
}

void reverse(int *inicio, int *fim) {
    if (inicio >= fim) {
        return;
    }
    
    int temp = *inicio;
    *inicio = *fim;
    *fim = temp;
    
    reverse(inicio + 1, fim - 1);
}

void reverse_array(int **array, size_t *count) {
    if (array == NULL || *array == NULL || count == NULL || *count <= 1) {
        return;
    }
    
    reverse(*array, *array + *count - 1);
}

void bubble_sort_ponto(PontoArray *arr) {
    if (arr == NULL || arr->array == NULL || arr->count <= 1) {
        return;
    }
    
    for (size_t i = 0; i < arr->count - 1; i++) {
        for (size_t j = 0; j < arr->count - i - 1; j++) {
            if (arr->array[j].x > arr->array[j + 1].x) {
                Ponto temp = arr->array[j];
                arr->array[j] = arr->array[j + 1];
                arr->array[j + 1] = temp;
            }
        }
    }
}

static void reverse_ponto(Ponto *inicio, Ponto *fim) {
    if (inicio >= fim) {
        return;
    }
    
    Ponto temp = *inicio;
    *inicio = *fim;
    *fim = temp;
    
    reverse_ponto(inicio + 1, fim - 1);
}

void reverse_ponto_array(PontoArray *arr) {
    if (arr == NULL || arr->array == NULL || arr->count <= 1) {
        return;
    }
    
    reverse_ponto(arr->array, arr->array + arr->count - 1);
}
