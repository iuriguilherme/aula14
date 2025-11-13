/*
 * Interpolador Polinomial de Lagrange
 * 
 * Este programa lê pares de valores (x, y) de um arquivo e calcula
 * o polinômio interpolador usando o método de Lagrange.
 * Permite calcular valores interpolados para novos pontos.
 * 
 * Data: 12 de Novembro de 2025
 * Aluno: Iuri Guilherme
 * Professor: Cassandro
 * Disciplina: Algoritmos II
 * Escola: IFRS - Campus Veranópolis
 * Turma: 2025/1
 * Tecnologias de IA Gerativa Utilizadas: GitHub Copilot, Claude Sonnet 4.5
 * Ambiente de Desenvolvimento: VSCode
 * Linguagem de Programação: C (Padrão C17)
 * Bibliotecas Utilizadas: stdio.h, stdlib.h, string.h, time.h, stddef.h, stdbool.h
 * 
 */

#include "main.h"
#include "init.h"
#include "lagrange.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Initialize and ensure pontos.txt is valid
    inicializar_arquivo("pontos.txt");
    
    // Run Lagrange interpolation on the valid file
    executar_lagrange("pontos.txt");
    
    return 0;
}
