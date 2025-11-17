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
│   ├── pontos.c       # Manipulação de arrays de pontos
│   └── ordering.c     # Algoritmos de ordenação e reversão
├── include/           # Arquivos de cabeçalho
│   ├── structs.h      # Definições de estruturas de dados
│   ├── local_config.h # Configurações do projeto
│   └── *.h            # Headers de cada módulo
├── tests/             # Suite de testes
│   ├── test_*.c       # Testes unitários para cada módulo
│   └── test_runner.c  # Coordenador de testes
├── .roo/              # Regras para agentes AI
│   ├── rules-architect/
│   ├── rules-ask/
│   ├── rules-code/
│   └── rules-debug/
├── visualizar.html    # Interface web para visualização
├── AGENTS.md          # Guia para agentes de desenvolvimento
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
Escolha o tipo de função:
1 - Linear (f(x) = ax + b) [padrão]
2 - Quadrática (f(x) = ax² + bx + c)
3 - Cúbica (f(x) = ax³ + bx² + cx + d)
Opção:
```

Depois:

```
Quantos pontos deseja gerar? [sugerido: 3]
```

O número sugerido varia conforme o tipo de função escolhida (3 para linear, 5 para quadrática, 7 para cúbica).

Pressione Enter para usar os valores padrão.

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

O arquivo [`pontos.txt`](pontos.txt) deve conter pares de valores (x, y) por linha:

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
Escolha o tipo de função:
1 - Linear (f(x) = ax + b) [padrão]
2 - Quadrática (f(x) = ax² + bx + c)
3 - Cúbica (f(x) = ax³ + bx² + cx + d)
Opção: 2

Quantos pontos deseja gerar? [sugerido: 5] 
Usando sugestão: 5 pontos
Gerando função quadrática: f(x) = 1.23x² + -2.45x + 3.67

5 pontos gerados com sucesso em pontos.txt!

=== Interpolador Polinomial de Lagrange ===

Arquivo lido com sucesso! Total de pontos: 5
...
```

### Exemplo 2: Usando arquivo existente

Se [`pontos.txt`](pontos.txt) já existe e é válido:

```bash
$ make run
=== Gerador de Pontos ===

Arquivo pontos.txt contém 5 coordenadas válidas.
Pontos existentes:
  1: (1.0000, 2.0000)
  2: (2.0000, 4.0000)
  ...

Deseja gerar novos pontos? (Os dados existentes serão sobrescritos) [padrão: n] (s/n): n
Usando pontos existentes.

=== Interpolador Polinomial de Lagrange ===

Arquivo lido com sucesso! Total de pontos: 5

Pontos fornecidos:
  i  |    x    |    y
-----|---------|----------
   0 |    1.00 |    2.0000
   1 |    2.00 |    4.0000
...

--- Calcular valor interpolado ---
Digite o valor de x [padrão: 3.0000] (ou 'q' para sair): 
Usando padrão: 3.0000
L(3.0000) = 6.000000

Deseja calcular outro valor? (s/n): n

Programa finalizado.

Dados exportados para 'interpolacao.json' para visualização.
```

### Exemplo 3: Visualizando os resultados graficamente

Após executar o programa, um arquivo [`interpolacao.json`](interpolacao.json) é criado. Para visualizar:

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
[DEBUG] ler_ponto_array: Successfully read 5 pontos
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

O arquivo [`include/local_config.h`](include/local_config.h) contém configurações importantes:

```c
#define MAX_POINTS 300  // Número máximo de pontos para interpolação
```

## Estruturas de Dados

### Ponto
```c
typedef struct {
    double x;
    double y;
} Ponto;
```

### PontoArray
```c
typedef struct {
    size_t size;         // Capacidade alocada
    size_t count;        // Número de elementos
    Ponto *array;        // Array dinâmico
} PontoArray;
```

## Testes

O projeto inclui testes para:
- Manipulação de arrays de pontos ([`test_pontos.c`](tests/test_pontos.c))
- Operações de arquivo ([`test_file_handler.c`](tests/test_file_handler.c))
- Algoritmos de ordenação e reversão ([`test_ordering.c`](tests/test_ordering.c))
- Geração de pontos ([`test_generator.c`](tests/test_generator.c))

Execute:
```bash
make test
```

## Requisitos

- Compilador GCC (ou compatível com C11)
- Make
- Sistema operacional: Linux, macOS ou Windows (com MinGW)
- Biblioteca matemática padrão (libm)
- Navegador web moderno (para visualização gráfica)

## Limitações

- Máximo de 300 pontos por padrão (configurável em [`local_config.h`](include/local_config.h))
- Pontos com valores x duplicados causam divisão por zero na interpolação
- Pontos gerados não são automaticamente ordenados por x
- Extrapolação fora do intervalo de pontos pode ser imprecisa
- Algoritmo de reversão recursivo pode causar stack overflow com arrays muito grandes (>1000 pontos)

## Notas Técnicas

- **Padrão C**: C11 com flags `-Wall -Wextra`
- **Gerenciamento de memória**: Arrays dinâmicos com realocação automática via [`PontoArray`](include/structs.h)
- **Tratamento de erros**: Validação de parâmetros e verificação de falhas de alocação
- **Debug**: Mensagens detalhadas disponíveis com `-DVERBOSE` (não `-DDEBUG`)
- **Complexidade**: Interpolação O(n²) por avaliação, sem otimizações ou memoização
- **Arquivos fixos**: Entrada sempre de [`pontos.txt`](pontos.txt), saída sempre para [`interpolacao.json`](interpolacao.json)

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
