#include "lagrange.h"
#include "config.h"
#include "structs.h"
#include "coordinate_arrays.h"
#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Calcula o valor interpolado usando o método de Lagrange
 * L(x) = Σ y_i * l_i(x)
 * onde l_i(x) = Π (x - x_j) / (x_i - x_j) para j ≠ i
 */
double lagrange_interpolation(CoordinateArray *arr, double x) {
    double result = 0.0;
    
    for (size_t i = 0; i < arr->count; i++) {
        double term = arr->array[i].y;
        
        for (size_t j = 0; j < arr->count; j++) {
            if (i != j) {
                term *= (x - arr->array[j].x) / (arr->array[i].x - arr->array[j].x);
            }
        }
        
        result += term;
    }
    
    return result;
}

/*
 * Exibe o polinômio de Lagrange em forma simbólica
 */
void display_polynomial(CoordinateArray *arr) {
    printf("\nPolinômio Interpolador de Lagrange:\n");
    printf("L(x) = ");
    
    for (size_t i = 0; i < arr->count; i++) {
        if (i > 0 && arr->array[i].y >= 0) {
            printf("+ ");
        }
        
        printf("%.4f", arr->array[i].y);
        
        // Exibir os termos l_i(x)
        printf(" * [");
        int first = 1;
        for (size_t j = 0; j < arr->count; j++) {
            if (i != j) {
                if (!first) {
                    printf(" * ");
                }
                printf("(x - %.2f)/(%.2f - %.2f)", 
                       arr->array[j].x, arr->array[i].x, arr->array[j].x);
                first = 0;
            }
        }
        printf("]");
        
        if (i < arr->count - 1) {
            printf("\n       ");
        }
    }
    printf("\n");
}

/*
 * Exibe os pontos dados
 */
void display_points(CoordinateArray *arr) {
    printf("\nPontos fornecidos:\n");
    printf("  i  |    x    |    y\n");
    printf("-----|---------|----------\n");
    for (size_t i = 0; i < arr->count; i++) {
        printf(" %3zu | %7.2f | %8.4f\n", i, arr->array[i].x, arr->array[i].y);
    }
}

/*
 * Gera um valor padrão de x baseado no intervalo dos pontos dados
 * Retorna o ponto médio entre o menor e maior valor de x
 */
double gerar_x_padrao(CoordinateArray *arr) {
    if (arr->count == 0) {
        return 0.0;
    }
    
    double x_min = arr->array[0].x;
    double x_max = arr->array[0].x;
    
    for (size_t i = 1; i < arr->count; i++) {
        if (arr->array[i].x < x_min) {
            x_min = arr->array[i].x;
        }
        if (arr->array[i].x > x_max) {
            x_max = arr->array[i].x;
        }
    }
    
    return (x_min + x_max) / 2.0;
}

/*
 * Exporta os dados para um arquivo JSON para visualização
 */
void exportar_json(CoordinateArray *arr, const char *filename) {
    FILE *json_file = fopen(filename, "w");
    if (!json_file) {
#ifdef VERBOSE
        printf("[DEBUG] exportar_json: Failed to create file '%s'\n", filename);
#endif
        return;
    }
    
    // Find x range
    double x_min = arr->array[0].x;
    double x_max = arr->array[0].x;
    
    for (size_t i = 1; i < arr->count; i++) {
        if (arr->array[i].x < x_min) x_min = arr->array[i].x;
        if (arr->array[i].x > x_max) x_max = arr->array[i].x;
    }
    
    // Generate interpolated points
    double range = x_max - x_min;
    double step = range / 100.0; // 100 points for smooth curve
    
    fprintf(json_file, "{\n");
    fprintf(json_file, "  \"originalPoints\": [\n");
    
    // Write original points
    for (size_t i = 0; i < arr->count; i++) {
        fprintf(json_file, "    {\"x\": %.6f, \"y\": %.6f}%s\n",
                arr->array[i].x, arr->array[i].y,
                (i < arr->count - 1) ? "," : "");
    }
    
    fprintf(json_file, "  ],\n");
    fprintf(json_file, "  \"interpolatedPoints\": [\n");
    
    // Write interpolated points
    for (int i = 0; i <= 100; i++) {
        double x = x_min + (step * i);
        double y = lagrange_interpolation(arr, x);
        fprintf(json_file, "    {\"x\": %.6f, \"y\": %.6f}%s\n",
                x, y, (i < 100) ? "," : "");
    }
    
    fprintf(json_file, "  ]\n");
    fprintf(json_file, "}\n");
    
    fclose(json_file);
    
#ifdef VERBOSE
    printf("[DEBUG] exportar_json: Successfully exported to '%s'\n", filename);
#endif
    printf("\nDados exportados para '%s' para visualização.\n", filename);
}

void executar_lagrange(const char *nome_arquivo) {
    CoordinateArray arr;
    
    printf("=== Interpolador Polinomial de Lagrange ===\n\n");
    
    // Criar array de coordenadas
    if (!criar_coordinate_array(&arr, MAX_POINTS)) {
        printf("Erro ao criar array de coordenadas.\n");
        return;
    }
    
    // Ler os pontos do arquivo usando file_handler
    FILE *file = abrir_arquivo(nome_arquivo);
    if (!file) {
        printf("Erro ao abrir o arquivo: %s\n", nome_arquivo);
        free(arr.array);
        return;
    }
    
    if (ler_coordinate_array(file, &arr) != 1) {
        printf("Erro ao ler coordenadas do arquivo.\n");
        fclose(file);
        free(arr.array);
        return;
    }
    
    fclose(file);
    
    if (arr.count < 2) {
        printf("Erro: São necessários pelo menos 2 pontos para interpolação.\n");
        free(arr.array);
        return;
    }
    
    printf("Arquivo lido com sucesso! Total de pontos: %zu\n", arr.count);
    
    // Exibir os pontos
    display_points(&arr);
    
    // Exibir o polinômio
    display_polynomial(&arr);
    
    // Menu para calcular valores interpolados
    char choice;
    do {
        double x_padrao = gerar_x_padrao(&arr);
        
        printf("\n--- Calcular valor interpolado ---\n");
        printf("Digite o valor de x [padrão: %.4f] (ou 'q' para sair): ", x_padrao);
        
        char buffer[100];
        double x;
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        
        // Check if user wants to quit
        if (buffer[0] == 'q' || buffer[0] == 'Q') {
            break;
        }
        
        // Use default if user just pressed Enter
        if (buffer[0] == '\n') {
            x = x_padrao;
            printf("Usando padrão: %.4f\n", x);
        } else if (sscanf(buffer, "%lf", &x) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }
        
        double y = lagrange_interpolation(&arr, x);
        printf("L(%.4f) = %.6f\n", x, y);
        
        printf("\nDeseja calcular outro valor? (s/n): ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || 
            (buffer[0] != 's' && buffer[0] != 'S')) {
            break;
        }
        
    } while (1);
    
    printf("\nPrograma finalizado.\n");
    
    // Exportar dados para JSON
    exportar_json(&arr, "interpolacao.json");
    
    // Liberar memória
    free(arr.array);
}
