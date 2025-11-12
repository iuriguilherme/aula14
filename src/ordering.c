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
