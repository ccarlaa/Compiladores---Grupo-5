# Makefile Multiplataforma - Tradutor C para Portugol
# Funciona em Windows, Linux e macOS

# Detectar sistema operacional
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RM := del /f /q
    MKDIR := if not exist $(1) mkdir $(1)
    PATH_SEP := \\
else
    DETECTED_OS := $(UNAME_S)
    EXE_EXT := 
    RM := rm -f
    MKDIR := mkdir -p $(1)
    PATH_SEP := /
endif

# Configurações do compilador
CC := gcc
CFLAGS := -std=c99 -Wall -Wextra
TARGET := compilador$(EXE_EXT)
SOURCE := src/main.c
TEST_DIR := tests

# Diretórios
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj

# Cores para output (se suportado)
ifneq ($(DETECTED_OS),Windows)
    RED := \033[0;31m
    GREEN := \033[0;32m
    YELLOW := \033[0;33m
    BLUE := \033[0;34m
    NC := \033[0m
else
    RED := 
    GREEN := 
    YELLOW := 
    BLUE := 
    NC := 
endif

# Target principal
all: info $(TARGET)

# Informações do sistema
info:
	@echo "$(BLUE)=== Tradutor C para Portugol ===$(NC)"
	@echo "Sistema detectado: $(DETECTED_OS)"
	@echo "Compilador: $(CC)"
	@echo "Target: $(TARGET)"
	@echo ""

# Compilação principal (modo manual)
$(TARGET): $(SOURCE)
	@echo "$(YELLOW)Compilando para $(DETECTED_OS)...$(NC)"
	$(CC) $(CFLAGS) -DMANUAL_MODE -o $(TARGET) $(SOURCE)
	@echo "$(GREEN)Compilacao concluida: $(TARGET)$(NC)"

# Compilação para Windows
windows: CFLAGS += -DWINDOWS
windows: TARGET := compilador.exe
windows: $(TARGET)

# Compilação para Linux
linux: CFLAGS += -DLINUX
linux: TARGET := compilador
linux: $(TARGET)

# Compilação para macOS
macos: CFLAGS += -DMACOS
macos: TARGET := compilador
macos: $(TARGET)

# Teste básico
test: $(TARGET)
	@echo "$(BLUE)Executando teste basico...$(NC)"
ifeq ($(DETECTED_OS),Windows)
	@if exist "$(TEST_DIR)\\test_01_basic.c" ( \
		.\\$(TARGET) "$(TEST_DIR)\\test_01_basic.c" \
	) else ( \
		echo "$(RED)Arquivo de teste nao encontrado$(NC)" \
	)
else
	@if [ -f "$(TEST_DIR)/test_01_basic.c" ]; then \
		./$(TARGET) "$(TEST_DIR)/test_01_basic.c"; \
	else \
		echo "$(RED)Arquivo de teste nao encontrado$(NC)"; \
	fi
endif

# Executar todos os testes
test-all: $(TARGET)
	@echo "$(BLUE)Executando todos os testes...$(NC)"
ifeq ($(DETECTED_OS),Windows)
	@for %%f in ($(TEST_DIR)\\test_*.c) do ( \
		echo "$(YELLOW)Testando %%f...$(NC)" && \
		.\\$(TARGET) "%%f" \
	)
else
	@for test in $(TEST_DIR)/test_*.c; do \
		echo "$(YELLOW)Testando $$test...$(NC)"; \
		./$(TARGET) "$$test"; \
		echo ""; \
	done
endif

# Teste com saída em arquivo
test-output: $(TARGET)
	@echo "$(BLUE)Teste com saida em arquivo...$(NC)"
ifeq ($(DETECTED_OS),Windows)
	.\\$(TARGET) "$(TEST_DIR)\\test_01_basic.c" -o teste_saida.ptg
	@if exist teste_saida.ptg echo "$(GREEN)Arquivo gerado: teste_saida.ptg$(NC)"
else
	./$(TARGET) "$(TEST_DIR)/test_01_basic.c" -o teste_saida.ptg
	@if [ -f "teste_saida.ptg" ]; then echo "$(GREEN)Arquivo gerado: teste_saida.ptg$(NC)"; fi
endif

# Limpeza
clean:
	@echo "$(YELLOW)Limpando arquivos...$(NC)"
ifeq ($(DETECTED_OS),Windows)
	-@if exist $(TARGET) del /f /q $(TARGET)
	-@if exist teste_saida.ptg del /f /q teste_saida.ptg
	-@if exist lex.yy.c del /f /q lex.yy.c
	-@if exist parser.tab.c del /f /q parser.tab.c
	-@if exist parser.tab.h del /f /q parser.tab.h
else
	$(RM) $(TARGET) teste_saida.ptg lex.yy.c parser.tab.c parser.tab.h
endif
	@echo "$(GREEN)Limpeza concluida$(NC)"

# Verificar dependências
check-deps:
	@echo "$(BLUE)Verificando dependencias...$(NC)"
	@$(CC) --version > /dev/null 2>&1 && echo "$(GREEN)GCC: OK$(NC)" || echo "$(RED)GCC: NAO ENCONTRADO$(NC)"
ifeq ($(DETECTED_OS),Windows)
	@echo "Sistema: Windows - usando modo manual"
else
	@which make > /dev/null 2>&1 && echo "$(GREEN)Make: OK$(NC)" || echo "$(YELLOW)Make: NAO ENCONTRADO$(NC)"
endif

# Instalar (Unix-like apenas)
install: $(TARGET)
ifneq ($(DETECTED_OS),Windows)
	@echo "$(BLUE)Instalando...$(NC)"
	sudo cp $(TARGET) /usr/local/bin/
	@echo "$(GREEN)Instalado em /usr/local/bin/$(NC)"
else
	@echo "$(YELLOW)Instalacao automatica nao suportada no Windows$(NC)"
	@echo "Copie manualmente $(TARGET) para um diretorio no PATH"
endif

# Ajuda
help:
	@echo "$(BLUE)Tradutor C para Portugol - Comandos disponíveis:$(NC)"
	@echo ""
	@echo "  make              - Compila o tradutor"
	@echo "  make windows      - Compila especificamente para Windows"
	@echo "  make linux        - Compila especificamente para Linux"  
	@echo "  make macos        - Compila especificamente para macOS"
	@echo "  make test         - Executa teste basico"
	@echo "  make test-all     - Executa todos os testes"
	@echo "  make test-output  - Teste com saida em arquivo"
	@echo "  make clean        - Remove arquivos compilados"
	@echo "  make check-deps   - Verifica dependencias"
	@echo "  make install      - Instala no sistema (Unix/Linux/Mac)"
	@echo "  make help         - Mostra esta ajuda"

.PHONY: all info windows linux macos test test-all test-output clean check-deps install help