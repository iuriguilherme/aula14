# Makefile para o Interpolador Polinomial de Lagrange

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
DEBUG_CFLAGS = -Wall -Wextra -std=c11 -g -DVERBOSE
TEST_DEBUG_CFLAGS = -Wall -Wextra -std=c11 -g -DDEBUG
SRCDIR = src
TESTDIR = tests
INCDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/lagrange
TEST_TARGET = $(BUILDDIR)/test_suite

# Source files for main program
MAIN_SOURCES = $(SRCDIR)/main.c \
               $(SRCDIR)/pontos.c \
               $(SRCDIR)/file_handler.c \
               $(SRCDIR)/ordering.c \
               $(SRCDIR)/generator.c \
               $(SRCDIR)/lagrange.c \
               $(SRCDIR)/init.c

# Source files for tests
TEST_SOURCES = $(TESTDIR)/test_main.c \
               $(TESTDIR)/test_pontos.c \
               $(TESTDIR)/test_ordering.c \
               $(TESTDIR)/test_file_handler.c \
               $(TESTDIR)/test_generator.c \
               $(TESTDIR)/test_runner.c

# Shared library sources (everything except main.c and test_main.c)
LIB_SOURCES = $(SRCDIR)/pontos.c \
              $(SRCDIR)/file_handler.c \
              $(SRCDIR)/ordering.c \
              $(SRCDIR)/generator.c \
              $(SRCDIR)/lagrange.c \
              $(SRCDIR)/init.c

OBJDIR = obj
MAIN_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(MAIN_SOURCES))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TEST_SOURCES)) \
               $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))
CFLAGS += -I$(INCDIR)

# Regra padrão
all: $(TARGET)

# Compilar o programa
$(TARGET): $(MAIN_OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJECTS) -lm

# Compilar suite de testes
$(TEST_TARGET): $(TEST_OBJECTS) | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS) -lm

# Compilar arquivos objeto do src
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilar arquivos objeto do tests
$(OBJDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
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
	$(TARGET)

# Compilar em modo debug com mensagens verbose
debug: CFLAGS = $(DEBUG_CFLAGS) -I$(INCDIR)
debug: clean $(TARGET)
	$(TARGET)

# Compilar e executar testes
test: $(TEST_TARGET)
	$(TEST_TARGET)

# Compilar e executar testes em modo debug
test-debug: CFLAGS = $(TEST_DEBUG_CFLAGS) -I$(INCDIR)
test-debug: clean $(TEST_TARGET)
	$(TEST_TARGET)

# Ajuda
help:
	@echo "Uso do Makefile:"
	@echo "  make         - Compila o programa"
	@echo "  make clean   - Remove arquivos compilados"
	@echo "  make run     - Compila e executa o programa"
	@echo "  make debug   - Compila em modo debug e executa (com mensagens verbose)"
	@echo "  make test    - Compila e executa os testes"
	@echo "  make test-debug - Compila e executa os testes em modo debug"
	@echo "  make help    - Exibe esta mensagem de ajuda"

.PHONY: all clean run debug test test-debug help
