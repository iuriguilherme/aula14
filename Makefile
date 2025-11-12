# Makefile para o Interpolador Polinomial de Lagrange

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
SRCDIR = src
BUILDDIR = build
TARGET = $(BUILDDIR)/lagrange
SOURCES = $(SRCDIR)/lagrange.c
OBJDIR = obj
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Regra padrão
all: $(TARGET)

# Compilar o programa
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lm

# Compilar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Criar diretórios se não existirem
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Limpar arquivos compilados
clean:
	rm -rf $(OBJDIR) $(BUILDDIR)

# Executar com arquivo de exemplo
run: $(TARGET)
	$(TARGET) pontos.txt

# Ajuda
help:
	@echo "Uso do Makefile:"
	@echo "  make         - Compila o programa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make run     - Compila e executa com pontos.txt"
	@echo "  make help    - Exibe esta mensagem de ajuda"

.PHONY: all clean run help
