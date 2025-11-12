/*
 * Interpolador Polinomial de Lagrange
 * 
 * Este programa lê pares de valores (x, y) de um arquivo e calcula
 * o polinômio interpolador usando o método de Lagrange.
 * Permite calcular valores interpolados para novos pontos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POINTS 100
#define MAX_LINE 256

typedef struct {
    double x;
    double y;
} Point;

/*
 * Lê os pontos do arquivo de entrada
 * Formato esperado: cada linha contém "x y" separados por espaço
 */
int read_points(const char *filename, Point points[], int *n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return 0;
    }
    
    *n = 0;
    char line[MAX_LINE];
    
    while (fgets(line, sizeof(line), file) && *n < MAX_POINTS) {
        // Ignorar linhas vazias e comentários
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }
        
        if (sscanf(line, "%lf %lf", &points[*n].x, &points[*n].y) == 2) {
            (*n)++;
        }
    }
    
    fclose(file);
    return 1;
}

/*
 * Calcula o valor interpolado usando o método de Lagrange
 * L(x) = Σ y_i * l_i(x)
 * onde l_i(x) = Π (x - x_j) / (x_i - x_j) para j ≠ i
 */
double lagrange_interpolation(Point points[], int n, double x) {
    double result = 0.0;
    
    for (int i = 0; i < n; i++) {
        double term = points[i].y;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (x - points[j].x) / (points[i].x - points[j].x);
            }
        }
        
        result += term;
    }
    
    return result;
}

/*
 * Exibe o polinômio de Lagrange em forma simbólica
 */
void display_polynomial(Point points[], int n) {
    printf("\nPolinômio Interpolador de Lagrange:\n");
    printf("L(x) = ");
    
    for (int i = 0; i < n; i++) {
        if (i > 0 && points[i].y >= 0) {
            printf("+ ");
        }
        
        printf("%.4f", points[i].y);
        
        // Exibir os termos l_i(x)
        printf(" * [");
        int first = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (!first) {
                    printf(" * ");
                }
                printf("(x - %.2f)/(%.2f - %.2f)", 
                       points[j].x, points[i].x, points[j].x);
                first = 0;
            }
        }
        printf("]");
        
        if (i < n - 1) {
            printf("\n       ");
        }
    }
    printf("\n");
}

/*
 * Exibe os pontos dados
 */
void display_points(Point points[], int n) {
    printf("\nPontos fornecidos:\n");
    printf("  i  |    x    |    y\n");
    printf("-----|---------|----------\n");
    for (int i = 0; i < n; i++) {
        printf(" %3d | %7.2f | %8.4f\n", i, points[i].x, points[i].y);
    }
}

int main(int argc, char *argv[]) {
    Point points[MAX_POINTS];
    int n;
    char filename[MAX_LINE];
    
    printf("=== Interpolador Polinomial de Lagrange ===\n\n");
    
    // Verificar argumentos da linha de comando
    if (argc > 1) {
        strncpy(filename, argv[1], MAX_LINE - 1);
        filename[MAX_LINE - 1] = '\0';
    } else {
        printf("Digite o nome do arquivo de entrada: ");
        if (scanf("%s", filename) != 1) {
            printf("Erro ao ler o nome do arquivo.\n");
            return 1;
        }
    }
    
    // Ler os pontos do arquivo
    if (!read_points(filename, points, &n)) {
        return 1;
    }
    
    if (n < 2) {
        printf("Erro: São necessários pelo menos 2 pontos para interpolação.\n");
        return 1;
    }
    
    printf("Arquivo lido com sucesso! Total de pontos: %d\n", n);
    
    // Exibir os pontos
    display_points(points, n);
    
    // Exibir o polinômio
    display_polynomial(points, n);
    
    // Menu para calcular valores interpolados
    char choice;
    do {
        printf("\n--- Calcular valor interpolado ---\n");
        printf("Digite o valor de x (ou 'q' para sair): ");
        
        double x;
        if (scanf("%lf", &x) != 1) {
            // Limpar o buffer se não conseguiu ler um número
            if (scanf("%s", &choice) != 1) {
                break;
            }
            if (choice == 'q' || choice == 'Q') {
                break;
            }
            printf("Entrada inválida. Tente novamente.\n");
            continue;
        }
        
        double y = lagrange_interpolation(points, n, x);
        printf("L(%.4f) = %.6f\n", x, y);
        
        printf("\nDeseja calcular outro valor? (s/n): ");
        if (scanf(" %c", &choice) != 1) {
            break;
        }
        
    } while (choice == 's' || choice == 'S');
    
    printf("\nPrograma finalizado.\n");
    
    return 0;
}
