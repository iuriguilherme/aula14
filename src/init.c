#include "init.h"
#include "generator.h"
#include "file_handler.h"
#include "pontos.h"
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
        PontoArray arr;
        criar_ponto_array(&arr, 10);
        
        int result = ler_ponto_array(arquivo, &arr);
        fclose(arquivo);

        #ifdef VERBOSE
            printf("[DEBUG]: result = %d, arr.count = %d\n", result, arr.count);
        #endif

        if (result == 1 && arr.count > 0) {
            // File has valid coordinates
#ifdef VERBOSE
            printf("Arquivo %s encontrado com %zu coordenadas válidas.\n", nome_arquivo, arr.count);
#endif
            
            // Show existing points (limit display to 20 points for readability)
            printf("\nArquivo %s contém %zu coordenadas válidas.\n", nome_arquivo, arr.count);
            printf("Pontos existentes:\n");
            
            size_t display_count = (arr.count > 20) ? 20 : arr.count;
            for (size_t i = 0; i < display_count; i++) {
                printf("  %zu: (%.4f, %.4f)\n", i + 1, arr.array[i].x, arr.array[i].y);
            }
            
            if (arr.count > 20) {
                printf("  ... (%zu pontos não exibidos)\n", arr.count - 20);
            }
            
            // Ask if user wants to regenerate
            printf("\nDeseja gerar novos pontos? (Os dados existentes serão sobrescritos) [padrão: n] (s/n): ");
            char buffer[100];
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                if (buffer[0] == 's' || buffer[0] == 'S') {
                    printf("Gerando novos pontos...\n");
                    needs_generation = 1;
                } else {
                    printf("Usando pontos existentes.\n");
                }
            } else {
                printf("Usando pontos existentes.\n");
            }
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
