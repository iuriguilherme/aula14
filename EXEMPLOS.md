# Exemplos de Uso do Interpolador de Lagrange

## Compilação

```bash
make
```

## Uso Básico

### Exemplo 1: Interpolação de função quadrática

Arquivo `pontos.txt` contém pontos da função f(x) = x²:
```
0.0 0.0
1.0 1.0
2.0 4.0
3.0 9.0
```

Execute:
```bash
./lagrange pontos.txt
```

Ao ser solicitado, digite valores de x para interpolar:
- x = 1.5 → L(1.5) = 2.25
- x = 2.5 → L(2.5) = 6.25
- x = 4.0 → L(4.0) = 16.0 (extrapolação)

### Exemplo 2: Interpolação de função linear

Arquivo `pontos_linear.txt` contém pontos da função f(x) = 2x + 1:
```
0.0 1.0
1.0 3.0
2.0 5.0
```

Execute:
```bash
./lagrange pontos_linear.txt
```

Para x = 1.5, o resultado será L(1.5) = 4.0

### Exemplo 3: Interpolação de função cúbica

Arquivo `pontos_cubica.txt` contém pontos da função f(x) = x³:
```
-1.0 -1.0
0.0 0.0
1.0 1.0
2.0 8.0
```

Execute:
```bash
./lagrange pontos_cubica.txt
```

## Criando seu próprio arquivo de dados

Crie um arquivo de texto com o seguinte formato:

```
# Comentários começam com #
# Cada linha deve conter: x y

# Seus pontos aqui
1.0 2.5
2.0 5.0
3.0 7.5
4.0 10.0
```

Salve como `meus_pontos.txt` e execute:
```bash
./lagrange meus_pontos.txt
```

## Notas Importantes

1. **Número mínimo de pontos**: São necessários pelo menos 2 pontos para interpolação.

2. **Pontos únicos**: Cada valor de x deve ser único. Valores duplicados podem causar divisão por zero.

3. **Interpolação vs Extrapolação**:
   - **Interpolação**: Calcular valores dentro do intervalo dos pontos dados (mais preciso)
   - **Extrapolação**: Calcular valores fora do intervalo (pode ser impreciso)

4. **Precisão**: O polinômio de Lagrange passa exatamente por todos os pontos dados. A precisão em outros pontos depende da natureza da função original.

5. **Grau do polinômio**: Para n pontos, o polinômio terá grau no máximo n-1.

## Verificação dos Resultados

Para verificar se a interpolação está correta:

1. Teste com pontos conhecidos (devem retornar os valores y originais)
2. Compare com valores esperados de funções conhecidas
3. Verifique se o polinômio passa por todos os pontos dados

## Exemplo Completo de Sessão

```
$ ./lagrange pontos.txt

=== Interpolador Polinomial de Lagrange ===

Arquivo lido com sucesso! Total de pontos: 4

Pontos fornecidos:
  i  |    x    |    y
-----|---------|----------
   0 |    0.00 |   0.0000
   1 |    1.00 |   1.0000
   2 |    2.00 |   4.0000
   3 |    3.00 |   9.0000

Polinômio Interpolador de Lagrange:
L(x) = 0.0000 * [...] + 1.0000 * [...] + 4.0000 * [...] + 9.0000 * [...]

--- Calcular valor interpolado ---
Digite o valor de x (ou 'q' para sair): 1.5
L(1.5000) = 2.250000

Deseja calcular outro valor? (s/n): s

--- Calcular valor interpolado ---
Digite o valor de x (ou 'q' para sair): 2.5
L(2.5000) = 6.250000

Deseja calcular outro valor? (s/n): n

Programa finalizado.
```
