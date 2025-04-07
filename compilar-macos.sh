#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== C em Português - Compilador (macOS) ===${NC}"

# Verificar dependências
echo -e "${GREEN}Verificando dependências...${NC}"

# Verificar se o brew está instalado
if ! command -v brew &> /dev/null; then
    echo -e "${YELLOW}Homebrew não encontrado. Por favor, instale o Homebrew primeiro:${NC}"
    echo "/bin/bash -c \"\$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\""
    exit 1
fi

# Verificar e instalar dependências
for pkg in flex bison gcc; do
    if ! brew list $pkg &> /dev/null; then
        echo -e "${YELLOW}Pacote $pkg não encontrado. Instalando...${NC}"
        brew install $pkg
    else
        echo -e "${GREEN}$pkg já está instalado.${NC}"
    fi
done

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

# Perguntar se deseja executar o teste
read -p "Deseja executar o teste padrão? (S/n): " run_test
run_test=${run_test:-S} # Default para "S" se pressionar Enter

if [[ $run_test =~ ^[Ss]$ ]]; then
    echo -e "${GREEN}Executando teste padrão...${NC}"
    ./build/compilador < tests/teste1.txt
fi

echo -e "${BLUE}Para executar outros testes:${NC}"
echo -e "  ${YELLOW}./build/compilador < tests/seu_arquivo.txt${NC}" 