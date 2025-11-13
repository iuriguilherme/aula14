#include "init.h"
#include "generator.h"
#include "file_handler.h"
#include "coordinate_arrays.h"
#include <stdio.h>
#include <stdlib.h>

void inicializar_arquivo(const char *nome_arquivo) {
#ifdef VERBOSE
    printf("=== Gerador de Pontos ===\n\n");
#endif
    
    // Check if file exists and has valid coordinates
    FILE *arquivo = fopen(nome_arquivo, "r");
    int needs_generation = 0;
    
    if (arquivo == NULL) {
        // File doesn't exist, generate points
#ifdef VERBOSE
        printf("Arquivo %s não encontrado.\n", nome_arquivo);
#endif
        needs_generation = 1;
    } else {
        // File exists, try to read coordinates
        CoordinateArray arr;
        criar_coordinate_array(&arr, 10);
        
        int result = ler_coordinate_array(arquivo, &arr);
        fclose(arquivo);

        #ifdef VERBOSE
            printf("[DEBUG]: result = %d, arr.count = %d\n", result, arr.count);
        #endif

        if (result == 1 && arr.count > 0) {
            // File has valid coordinates
#ifdef VERBOSE
            printf("Arquivo %s encontrado com %zu coordenadas válidas.\n", nome_arquivo, arr.count);
#endif
        } else {
            // File exists but is empty or invalid
#ifdef VERBOSE
            printf("Arquivo %s existe mas não contém coordenadas válidas.\n", nome_arquivo);
#endif
            needs_generation = 1;
        }
        
        free(arr.array);
    }
    
    // Generate points if needed
    if (needs_generation) {
        gerar_pontos(nome_arquivo);
    }
}
