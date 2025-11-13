#include "generator.h"
#include "structs.h"
#include "coordinate_arrays.h"
#include "file_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Gera pontos para uma função linear: f(x) = ax + b
static int gerar_linear(CoordinateArray *arr, int num_pontos) {
    // Coeficientes aleatórios para a função linear
    double a = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
    double b = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
    
    printf("Gerando função linear: f(x) = %.2fx + %.2f\n", a, b);
    
    for (int i = 0; i < num_pontos; i++) {
        Coordinate coord;
        coord.x = ((double)rand() / RAND_MAX) * 20.0 - 10.0; // -10 a 10
        coord.y = a * coord.x + b;
        
        if (!inserir_coordinate_array(arr, coord)) {
            return 0;
        }
    }
    
    return 1;
}

// Gera pontos para uma função quadrática: f(x) = ax² + bx + c
static int gerar_quadratica(CoordinateArray *arr, int num_pontos) {
    // Coeficientes aleatórios para a função quadrática
    double a = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // -2 a 2
    double b = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
    double c = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
    
    printf("Gerando função quadrática: f(x) = %.2fx² + %.2fx + %.2f\n", a, b, c);
    
    for (int i = 0; i < num_pontos; i++) {
        Coordinate coord;
        coord.x = ((double)rand() / RAND_MAX) * 20.0 - 10.0; // -10 a 10
        coord.y = a * coord.x * coord.x + b * coord.x + c;
        
        if (!inserir_coordinate_array(arr, coord)) {
            return 0;
        }
    }
    
    return 1;
}

// Gera pontos para uma função cúbica: f(x) = ax³ + bx² + cx + d
static int gerar_cubica(CoordinateArray *arr, int num_pontos) {
    // Coeficientes aleatórios para a função cúbica
    double a = ((double)rand() / RAND_MAX) * 2.0 - 1.0; // -1 a 1
    double b = ((double)rand() / RAND_MAX) * 4.0 - 2.0; // -2 a 2
    double c = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
    double d = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
    
    printf("Gerando função cúbica: f(x) = %.2fx³ + %.2fx² + %.2fx + %.2f\n", a, b, c, d);
    
    for (int i = 0; i < num_pontos; i++) {
        Coordinate coord;
        coord.x = ((double)rand() / RAND_MAX) * 10.0 - 5.0; // -5 a 5
        coord.y = a * coord.x * coord.x * coord.x + b * coord.x * coord.x + c * coord.x + d;
        
        if (!inserir_coordinate_array(arr, coord)) {
            return 0;
        }
    }
    
    return 1;
}

void gerar_pontos(const char *nome_arquivo) {
    int num_pontos;
    int tipo_funcao;
    int sugestao_pontos;
    
    // Inicializa gerador de números aleatórios
    srand(time(NULL));
    
    // Primeiro: Pergunta o tipo de função
    printf("\nEscolha o tipo de função:\n");
    printf("1 - Linear (f(x) = ax + b) [padrão]\n");
    printf("2 - Quadrática (f(x) = ax² + bx + c)\n");
    printf("3 - Cúbica (f(x) = ax³ + bx² + cx + d)\n");
    printf("Opção: ");
    
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
        tipo_funcao = 1; // Padrão: linear
        printf("Usando padrão: Linear\n");
    } else if (sscanf(buffer, "%d", &tipo_funcao) != 1 || tipo_funcao < 1 || tipo_funcao > 3) {
        printf("Opção inválida! Usando padrão: Linear\n");
        tipo_funcao = 1;
    }
    
    // Define sugestão de pontos baseada no tipo de função
    switch (tipo_funcao) {
        case 1:
            sugestao_pontos = 3;  // Linear: 2 pontos mínimos, 3 para melhor interpolação
            break;
        case 2:
            sugestao_pontos = 5;  // Quadrática: mais pontos para capturar curvatura
            break;
        case 3:
            sugestao_pontos = 7;  // Cúbica: ainda mais pontos para inflexões
            break;
        default:
            sugestao_pontos = 3;
    }
    
    // Segundo: Pergunta quantos pontos gerar (com sugestão dinâmica)
    printf("\nQuantos pontos deseja gerar? [sugerido: %d] ", sugestao_pontos);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || buffer[0] == '\n') {
        num_pontos = sugestao_pontos;
        printf("Usando sugestão: %d pontos\n", num_pontos);
    } else if (sscanf(buffer, "%d", &num_pontos) != 1 || num_pontos <= 0) {
        printf("Número inválido! Usando sugestão: %d pontos\n", sugestao_pontos);
        num_pontos = sugestao_pontos;
    }
    
    // Cria array de coordenadas
    CoordinateArray arr;
    if (!criar_coordinate_array(&arr, num_pontos)) {
        printf("Erro ao criar array de coordenadas!\n");
        return;
    }
    
    // Gera os pontos de acordo com o tipo de função
    int sucesso = 0;
    switch (tipo_funcao) {
        case 1:
            sucesso = gerar_linear(&arr, num_pontos);
            break;
        case 2:
            sucesso = gerar_quadratica(&arr, num_pontos);
            break;
        case 3:
            sucesso = gerar_cubica(&arr, num_pontos);
            break;
    }
    
    if (!sucesso) {
        printf("Erro ao gerar pontos!\n");
        free(arr.array);
        return;
    }
    
    // Escreve os pontos no arquivo
    FILE *arquivo = criar_arquivo(nome_arquivo);
    if (!arquivo) {
        printf("Erro ao criar arquivo %s!\n", nome_arquivo);
        free(arr.array);
        return;
    }
    
    if (!escrever_coordinate_array(arquivo, &arr)) {
        printf("Erro ao escrever no arquivo!\n");
        fclose(arquivo);
        free(arr.array);
        return;
    }
    
    fclose(arquivo);
    free(arr.array);
    
    printf("\n%d pontos gerados com sucesso em %s!\n", num_pontos, nome_arquivo);
}
