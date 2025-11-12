# aula14
Propostas de Projeto Algoritmos II

## Interpolador Polinomial de Lagrange

Este projeto implementa um interpolador polinomial usando o método de Lagrange em linguagem C.

### Descrição

O programa lê pares de valores (x, y) de um arquivo de entrada e calcula o polinômio interpolador pelo método de Lagrange. O polinômio resultante pode ser usado para calcular valores interpolados em novos pontos.

### Método de Lagrange

O método de Lagrange constrói um polinômio que passa exatamente por todos os pontos dados. Para n pontos (x₀, y₀), (x₁, y₁), ..., (xₙ₋₁, yₙ₋₁), o polinômio interpolador é:

```
L(x) = Σ yᵢ * lᵢ(x)
```

onde lᵢ(x) são os polinômios base de Lagrange:

```
lᵢ(x) = Π (x - xⱼ) / (xᵢ - xⱼ)  para j ≠ i
```

### Como Compilar

```bash
make
```

ou

```bash
gcc -Wall -Wextra -std=c11 -O2 -o lagrange lagrange.c -lm
```

### Como Usar

#### Usando um arquivo de entrada:

```bash
./lagrange pontos.txt
```

ou simplesmente execute e digite o nome do arquivo quando solicitado:

```bash
./lagrange
```

#### Formato do Arquivo de Entrada

O arquivo deve conter um par de valores (x, y) por linha, separados por espaço:

```
# Comentários começam com #
0.0 0.0
1.0 1.0
2.0 4.0
3.0 9.0
```

### Exemplos de Uso

O projeto inclui três arquivos de exemplo:

1. **pontos.txt** - Pontos de uma função quadrática (f(x) = x²)
2. **pontos_linear.txt** - Pontos de uma função linear (f(x) = 2x + 1)
3. **pontos_cubica.txt** - Pontos de uma função cúbica (f(x) = x³)

Execute com:

```bash
make run
```

### Funcionalidades

- Leitura de pontos de arquivo com suporte a comentários
- Cálculo do polinômio interpolador de Lagrange
- Exibição do polinômio em forma simbólica
- Cálculo interativo de valores interpolados em novos pontos
- Interface amigável em português

### Limpeza

Para remover os arquivos compilados:

```bash
make clean
```

### Requisitos

- Compilador GCC (ou compatível)
- Sistema operacional: Linux, macOS ou Windows (com MinGW)
- Biblioteca matemática padrão (libm)

### Limitações

- Máximo de 100 pontos por padrão (pode ser ajustado em MAX_POINTS)
- Pontos com valores x duplicados podem causar divisão por zero

### Autor

Projeto desenvolvido para a disciplina Algoritmos II
