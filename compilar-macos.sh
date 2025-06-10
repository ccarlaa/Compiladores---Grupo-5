#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== TRADUTOR C PARA PORTUGOL (macOS) ===${NC}"

# Verificar dependências
echo -e "${GREEN}Verificando dependências...${NC}"

# Verificar se gcc está disponível
if ! command -v gcc &> /dev/null; then
    echo -e "${YELLOW}GCC não encontrado. Tentando instalar...${NC}"
    
    # Verificar se Xcode Command Line Tools estão instalados
    if ! xcode-select -p &> /dev/null; then
        echo -e "${GREEN}Instalando Xcode Command Line Tools...${NC}"
        xcode-select --install
        echo -e "${YELLOW}Aguarde a instalação das ferramentas de desenvolvimento...${NC}"
        echo -e "${YELLOW}Execute este script novamente após a instalação.${NC}"
        exit 0
    fi
    
    # Verificar se Homebrew está instalado
    if command -v brew &> /dev/null; then
        echo -e "${GREEN}Instalando GCC via Homebrew...${NC}"
        brew install gcc
    else
        echo -e "${YELLOW}Homebrew não encontrado.${NC}"
        echo -e "${GREEN}Instale o Homebrew para obter a versão mais recente do GCC:${NC}"
        echo "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
        echo ""
        echo -e "${GREEN}Usando GCC do Xcode Command Line Tools...${NC}"
    fi
else
    echo -e "${GREEN}✓ GCC encontrado: $(gcc --version | head -n1)${NC}"
fi

# Compilar projeto
echo -e "${GREEN}Compilando tradutor...${NC}"
gcc -std=c99 -Wall -Wextra -DMANUAL_MODE -o compilador src/main.c

if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ Compilação concluída com sucesso!${NC}"
    echo -e "${GREEN}Executável criado: ./compilador${NC}"
    echo -e "${GREEN}Modo: Manual (sem flex/bison)${NC}"
    echo ""
    echo -e "${BLUE}Para testar:${NC}"
    echo -e "${YELLOW}  ./compilador tests/test_01_basic.c${NC}"
    echo -e "${YELLOW}  ./compilador tests/test_01_basic.c -o saida.ptg${NC}"
    echo ""
    
    # Perguntar se deseja executar teste
    read -p "Deseja executar um teste básico? (s/N): " run_test
    if [[ $run_test =~ ^[Ss]$ ]]; then
        echo -e "${GREEN}Executando teste básico...${NC}"
        ./compilador tests/test_01_basic.c
    fi
else
    echo -e "${RED}✗ Erro na compilação!${NC}"
    echo -e "${RED}Verifique se o GCC está instalado corretamente.${NC}"
    exit 1
fi
mkdir -p build

# Compilar o parser com Bison
echo -e "${GREEN}Gerando parser com Bison...${NC}"
bison -d src/parser/parser.y -o parser.tab.c

# Compilar o lexer com Flex
echo -e "${GREEN}Gerando lexer com Flex...${NC}"
flex src/lexer/lexer.l

# Compilar os arquivos fonte
echo -e "${GREEN}Compilando arquivos fonte...${NC}"
gcc -Wall -Iinclude -c lex.yy.c -o lex.yy.o
gcc -Wall -Iinclude -c parser.tab.c -o parser.tab.o
gcc -Wall -Iinclude -c src/main.c -o main.o
gcc -Wall -Iinclude -c src/ast/ast.c -o ast.o

# Linkar todos os objetos
echo -e "${GREEN}Linkando executável...${NC}"
gcc -Wall -Iinclude main.o lex.yy.o parser.tab.o ast.o -o build/compilador

# Verificar se a compilação foi bem-sucedida
if [ $? -ne 0 ]; then
    echo -e "${YELLOW}Falha ao compilar o projeto.${NC}"
    exit 1
fi

echo -e "${GREEN}Compilação concluída!${NC}"

# Perguntar se deseja executar o teste
read -p "Deseja executar o teste padrão? (S/n): " run_test
run_test=${run_test:-S} # Default para "S" se pressionar Enter

if [[ $run_test =~ ^[Ss]$ ]]; then
    echo -e "${GREEN}Executando teste padrão...${NC}"
    ./build/compilador < tests/teste1.txt
fi

echo -e "${BLUE}Para executar outros testes:${NC}"
echo -e "  ${YELLOW}./build/compilador < tests/seu_arquivo.txt${NC}" 