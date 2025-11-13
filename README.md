# aula14
Interpolador Polinomial de Lagrange - Algoritmos II

## Descrição

Este projeto implementa um interpolador polinomial completo usando o método de Lagrange em linguagem C. O programa automaticamente gera pontos de funções matemáticas (linear, quadrática ou cúbica) e realiza interpolação polinomial para calcular valores em novos pontos.

### Funcionalidades

- **Geração automática de pontos**: Cria conjuntos de pontos aleatórios seguindo funções:
  - Linear: f(x) = ax + b
  - Quadrática: f(x) = ax² + bx + c
  - Cúbica: f(x) = ax³ + bx² + cx + d
- **Interpolação de Lagrange**: Calcula o polinômio que passa por todos os pontos
- **Exibição simbólica**: Mostra o polinômio interpolador em notação matemática
- **Cálculo interativo**: Permite calcular valores interpolados com sugestão de valor padrão
- **Exportação JSON**: Gera arquivo JSON com dados originais e interpolados
- **Visualização gráfica**: Interface HTML interativa para visualizar a interpolação
- **Validação automática**: Verifica a existência e validade do arquivo de pontos
- **Arrays dinâmicos**: Gerenciamento inteligente de memória com realocação automática
- **Modo debug**: Mensagens detalhadas de depuração com a flag `-DVERBOSE`
- **Testes automatizados**: Suite completa de testes para todas as funcionalidades

## Estrutura do Projeto

```
aula14/
├── src/               # Código fonte
│   ├── main.c         # Ponto de entrada do programa
│   ├── init.c         # Inicialização e validação de arquivos
│   ├── generator.c    # Geração de pontos aleatórios
│   ├── lagrange.c     # Interpolação polinomial
│   ├── file_handler.c # Operações de leitura/escrita
│   ├── coordinate_arrays.c    # Manipulação de arrays de coordenadas
│   ├── int_arrays.c           # Manipulação de arrays de inteiros
│   ├── double_arrays.c        # Manipulação de arrays de doubles
│   └── ordering.c     # Algoritmos de ordenação e reversão
├── include/           # Arquivos de cabeçalho
│   ├── structs.h      # Definições de estruturas de dados
│   ├── config.h       # Configurações do projeto
│   └── *.h            # Headers de cada módulo
├── tests/             # Suite de testes
│   ├── test_*.c       # Testes unitários para cada módulo
│   └── test_runner.c  # Coordenador de testes
├── obj/               # Arquivos objeto (gerado)
├── build/             # Executáveis (gerado)
└── Makefile           # Sistema de compilação

```

## Método de Lagrange

O método de Lagrange constrói um polinômio que passa exatamente por todos os pontos dados. Para n pontos (x₀, y₀), (x₁, y₁), ..., (xₙ₋₁, yₙ₋₁), o polinômio interpolador é:

```
L(x) = Σ yᵢ * lᵢ(x)
```

onde lᵢ(x) são os polinômios base de Lagrange:

```
lᵢ(x) = Π (x - xⱼ) / (xᵢ - xⱼ)  para j ≠ i
```

## Como Compilar

### Compilação padrão:
```bash
make
```

### Compilação com modo debug (mensagens detalhadas):
```bash
make debug
```

### Compilação dos testes:
```bash
make test
```

## Como Usar

### Uso básico:
```bash
make run
```

O programa irá:
1. Verificar se existe um arquivo `pontos.txt` válido
2. Se não existir ou estiver inválido, solicitar a geração de novos pontos
3. Executar a interpolação de Lagrange nos pontos

### Geração de Pontos

Quando executado sem arquivo válido, o programa pergunta:

```
Quantos pontos deseja gerar? [padrão: 3]
```

E depois:

```
Escolha o tipo de função:
1 - Linear (f(x) = ax + b) [padrão]
2 - Quadrática (f(x) = ax² + bx + c)
3 - Cúbica (f(x) = ax³ + bx² + cx + d)
Opção:
```

Pressione Enter para usar os valores padrão (3 pontos, função linear).

### Calculando Valores Interpolados

Após carregar os pontos, o programa exibe:

```
--- Calcular valor interpolado ---
Digite o valor de x [padrão: X.XXXX] (ou 'q' para sair):
```

- Pressione Enter para usar o valor padrão (ponto médio do intervalo)
- Digite um valor numérico para calcular nesse ponto
- Digite 'q' para sair

### Formato do Arquivo de Entrada

O arquivo `pontos.txt` deve conter pares de valores (x, y) por linha:

```
0.0 0.0
1.0 2.0
2.0 4.0
3.0 6.0
```

## Exemplos de Uso

### Exemplo 1: Gerando pontos quadráticos

```bash
$ make run
Quantos pontos deseja gerar? [padrão: 3] 5
Escolha o tipo de função:
1 - Linear (f(x) = ax + b) [padrão]
2 - Quadrática (f(x) = ax² + bx + c)
3 - Cúbica (f(x) = ax³ + bx² + cx + d)
Opção: 2
Gerando função quadrática: f(x) = 1.23x² + -2.45x + 3.67

5 pontos gerados com sucesso em pontos.txt!

=== Interpolador Polinomial de Lagrange ===

Arquivo lido com sucesso! Total de pontos: 5
...
```

### Exemplo 2: Usando arquivo existente

Se `pontos.txt` já existe e é válido:

```bash
$ make run
=== Interpolador Polinomial de Lagrange ===

Arquivo lido com sucesso! Total de pontos: 5

Pontos fornecidos:
  i  |    x    |    y
-----|---------|----------
   0 |   -8.23 |  95.4321
   1 |   -2.14 |  12.3456
...

--- Calcular valor interpolado ---
Digite o valor de x [padrão: 0.0000] (ou 'q' para sair): 
Usando padrão: 0.0000
L(0.0000) = 3.670000

Deseja calcular outro valor? (s/n): n

Programa finalizado.

Dados exportados para 'interpolacao.json' para visualização.
```

### Exemplo 3: Visualizando os resultados graficamente

Após executar o programa, um arquivo `interpolacao.json` é criado. Para visualizar:

```bash
# Abra visualizar.html no navegador
firefox visualizar.html
# ou
google-chrome visualizar.html
# ou simplesmente abra o arquivo com seu navegador padrão
```

O gráfico mostrará:
- **Pontos originais** (em vermelho)
- **Curva interpolada** (em azul) com 100 pontos calculados
- **Estatísticas** sobre os dados (número de pontos, intervalo, grau do polinômio)

### Exemplo 4: Modo Debug

```bash
$ make debug
[DEBUG] inicializar_arquivo: Checking file 'pontos.txt'
[DEBUG] abrir_arquivo_modo: Successfully opened 'pontos.txt' with mode 'r'
[DEBUG] ler_coordinate_array: Successfully read 5 coordinates
...
```

## Comandos do Makefile

```bash
make         # Compila o programa
make run     # Compila e executa o programa
make debug   # Compila em modo debug e executa (com mensagens verbose)
make test    # Compila e executa os testes
make clean   # Remove arquivos compilados
make help    # Exibe ajuda do Makefile
```

## Configuração

O arquivo `include/config.h` contém configurações importantes:

```c
#define MAX_POINTS 300  // Número máximo de pontos para interpolação
```

## Estruturas de Dados

### Coordinate
```c
typedef struct {
    double x;
    double y;
} Coordinate;
```

### CoordinateArray
```c
typedef struct {
    size_t size;         // Capacidade alocada
    size_t count;        // Número de elementos
    Coordinate *array;   // Array dinâmico
} CoordinateArray;
```

## Testes

O projeto inclui testes para:
- Manipulação de arrays (int, double, coordinate)
- Operações de arquivo (leitura/escrita)
- Algoritmos de ordenação e reversão
- Geração de pontos

Execute:
```bash
make test
```

## Requisitos

- Compilador GCC (ou compatível com C11)
- Make
- Sistema operacional: Linux, macOS ou Windows (com MinGW)
- Biblioteca matemática padrão (libm)

## Limitações

- Máximo de 300 pontos por padrão (configurável em `config.h`)
- Pontos com valores x duplicados podem causar divisão por zero
- Extrapolação fora do intervalo de pontos pode ser imprecisa

## Notas Técnicas

- **Padrão C**: C11 com flags `-Wall -Wextra`
- **Gerenciamento de memória**: Arrays dinâmicos com realocação automática
- **Tratamento de erros**: Validação de parâmetros e verificação de falhas de alocação
- **Debug**: Mensagens detalhadas disponíveis com `-DVERBOSE`

## Autor

**Projeto desenvolvido para a disciplina Algoritmos II**
- Data: 12 de Novembro de 2025
- Aluno: Iuri Guilherme
- Professor: Cassandro
- Escola: IFRS - Campus Veranópolis
- Turma: 2025/1
- Tecnologias de IA Gerativa: GitHub Copilot, Claude Sonnet 4.5
- Ambiente: VSCode
- Linguagem: C (Padrão C11)

## Licença

Copyright (C) 2025 Iuri Guilherme

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

See the [LICENSE](LICENSE) file for the complete GNU General Public License v3.0.
