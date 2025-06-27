# Compilador a ser usado (GNU C Compiler)
CC=gcc
# Flags de compilação (-I para incluir diretórios)
CFLAGS=-Iinclude -I$(BUILD_DIR) -Wall -Wextra
# Ferramentas de análise
LEX=flex
YACC=bison
# Nome do executável final
TARGET=compilador

# Diretórios do projeto
SRC_DIR=src
LEXER_DIR=lexer
PARSER_DIR=parser
BUILD_DIR=build
BASH_DIR=bash

# Encontra todos os scripts de teste na pasta bash
TEST_SCRIPTS := $(wildcard $(BASH_DIR)/*.sh)

# Arquivos fonte C (incluindo main.c)
C_SOURCES=$(wildcard $(SRC_DIR)/*.c)
# Arquivo fonte do Lexer (Flex)
LEX_SOURCE=$(LEXER_DIR)/lexer.l
# Arquivo fonte do Parser (Bison)
YACC_SOURCE=$(PARSER_DIR)/parser.y

# Arquivos objeto (compilados) a serem gerados no diretório de build
C_OBJECTS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
LEX_OBJECT=$(BUILD_DIR)/lex.yy.o
YACC_OBJECT=$(BUILD_DIR)/y.tab.o

# Arquivos gerados pelo Flex e Bison
LEX_GENERATED_C=$(BUILD_DIR)/lex.yy.c
YACC_GENERATED_C=$(BUILD_DIR)/y.tab.c
YACC_GENERATED_H=$(BUILD_DIR)/y.tab.h

# Regra padrão: executada quando você digita 'make'
all: $(TARGET)

# Regra para linkar tudo e criar o executável final
$(TARGET): $(C_OBJECTS) $(LEX_OBJECT) $(YACC_OBJECT)
	$(CC) $(CFLAGS) $^ -o $@

# Regra para compilar cada arquivo .c do diretório src para um .o no diretório build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar o C gerado pelo Flex
$(LEX_OBJECT): $(LEX_GENERATED_C) $(YACC_GENERATED_H)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para compilar o C gerado pelo Bison
$(YACC_OBJECT): $(YACC_GENERATED_C)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para gerar o código C a partir do arquivo .l do Flex
$(LEX_GENERATED_C): $(LEX_SOURCE) | $(BUILD_DIR)
	$(LEX) -o $@ $<

# Regra para gerar os arquivos .c e .h do Bison
$(YACC_GENERATED_C) $(YACC_GENERATED_H): $(YACC_SOURCE) | $(BUILD_DIR)
	$(YACC) -d -o $(YACC_GENERATED_C) $<

# Regra para criar o diretório de build se ele não existir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Regra para rodar todos os testes sequencialmente
test: $(TARGET)
	@echo "Iniciando bateria de testes..."
	@success=true; \
	for script in $(TEST_SCRIPTS); do \
		echo "Executando $$script..."; \
		if ! bash $$script; then \
			success=false; \
			echo "❌ Falha no teste $$script"; \
		fi; \
		echo ""; \
	done; \
	if [ "$$success" = true ]; then \
		echo "✅ Todos os testes foram concluídos com sucesso!"; \
	else \
		echo "❌ Alguns testes falharam. Verifique os logs acima."; \
		exit 1; \
	fi

# Regra para rodar a cobertura
coverage: $(TARGET)
	@echo "🧪 Executando testes com análise de cobertura de gramática..."
	@mkdir -p build/coverage_logs
	@> cobertura.txt
	@success=true; \
	for script in $(TEST_SCRIPTS); do \
		echo "🔍 Rodando $$script com captura de stderr..."; \
		if ! bash $$script 2>build/coverage_logs/stderr.log; then \
			success=false; \
			echo "❌ Falha no teste $$script"; \
		fi; \
		grep "COBERTURA DAS REGRAS DA GRAMÁTICA" -A 100 build/coverage_logs/stderr.log >> cobertura.txt || true; \
		echo "" >> cobertura.txt; \
	done; \
	if [ "$$success" = true ]; then \
		echo "✅ Todos os testes passaram com cobertura registrada em cobertura.txt"; \
	else \
		echo "⚠️ Alguns testes falharam — cobertura parcial registrada em cobertura.txt"; \
	fi

# Alvo para limpar os arquivos gerados
.PHONY: all clean test
clean:
	@echo "Limpando arquivos gerados..."
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)
	@echo "Limpeza concluída."

	