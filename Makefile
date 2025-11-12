# Makefile para o Interpolador Polinomial de Lagrange

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
TARGET = lagrange
SOURCES = lagrange.c
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão
all: $(TARGET)

# Compilar o programa
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lm

# Compilar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Executar com arquivo de exemplo
run: $(TARGET)
	./$(TARGET) pontos.txt

# Ajuda
help:
	@echo "Uso do Makefile:"
	@echo "  make         - Compila o programa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make run     - Compila e executa com pontos.txt"
	@echo "  make help    - Exibe esta mensagem de ajuda"

.PHONY: all clean run help
