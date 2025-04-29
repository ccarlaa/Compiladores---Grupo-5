#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== C em Português - Compilador (Linux) ===${NC}"

# Verificar dependências
echo -e "${GREEN}Verificando dependências...${NC}"

# Detectar o gerenciador de pacotes
if command -v apt-get &> /dev/null; then
    PKG_MANAGER="apt-get"
    INSTALL_CMD="sudo apt-get install -y flex bison build-essential"
elif command -v dnf &> /dev/null; then
    PKG_MANAGER="dnf"
    INSTALL_CMD="sudo dnf install -y flex bison gcc make"
elif command -v pacman &> /dev/null; then
    PKG_MANAGER="pacman"
    INSTALL_CMD="sudo pacman -S --needed flex bison gcc make"
else
    echo -e "${YELLOW}Gerenciador de pacotes não suportado.${NC}"
    echo -e "${YELLOW}Por favor, instale manualmente: flex, bison, gcc e make${NC}"
    read -p "Deseja continuar? (S/n): " continue_anyway
    continue_anyway=${continue_anyway:-S}
    if [[ ! $continue_anyway =~ ^[Ss]$ ]]; then
        exit 1
    fi
fi

# Instalar dependências se necessário
if [ -n "$PKG_MANAGER" ]; then
    echo -e "${GREEN}Instalando dependências usando $PKG_MANAGER...${NC}"
    eval $INSTALL_CMD
fi

# Criar diretórios necessários
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

# Tornar o compilador executável
chmod +x build/compilador

# Perguntar se deseja executar o teste
read -p "Deseja executar o teste padrão? (S/n): " run_test
run_test=${run_test:-S} # Default para "S" se pressionar Enter

if [[ $run_test =~ ^[Ss]$ ]]; then
    echo -e "${GREEN}Executando teste padrão...${NC}"
    ./build/compilador < tests/teste1.txt
fi

echo -e "${BLUE}Para executar outros testes:${NC}"
echo -e "  ${YELLOW}./build/compilador < tests/seu_arquivo.txt${NC}" 