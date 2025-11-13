#include "main.h"
#include "generator.h"
#include "file_handler.h"
#include "coordinate_arrays.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
#ifdef VERBOSE
    printf("=== Gerador de Pontos ===\n\n");
#endif
    
    // Check if pontos.txt exists and has valid coordinates
    FILE *arquivo = fopen("pontos.txt", "r");
    
    if (arquivo == NULL) {
        // File doesn't exist, generate points
#ifdef VERBOSE
        printf("Arquivo pontos.txt não encontrado.\n");
#endif
        gerar_pontos("pontos.txt");
    } else {
        // File exists, try to read coordinates
        CoordinateArray arr;
        criar_coordinate_array(&arr, 10);
        
        int result = ler_coordinate_array(arquivo, &arr);
        fclose(arquivo);
        
        if (result == 0 && arr.count > 0) {
            // File has valid coordinates
#ifdef VERBOSE
            printf("Arquivo pontos.txt encontrado com %zu coordenadas válidas.\n", arr.count);
#endif
            printf("Hello, World!\n");
        } else {
            // File exists but is empty or invalid
#ifdef VERBOSE
            printf("Arquivo pontos.txt existe mas não contém coordenadas válidas.\n");
#endif
            gerar_pontos("pontos.txt");
        }
        
        free(arr.array);
    }
    
    return 0;
}
