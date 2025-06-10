#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== TRADUTOR C PARA PORTUGOL (Linux) ===${NC}"

# Verificar dependências
echo -e "${GREEN}Verificando dependências...${NC}"

# Verificar se gcc está instalado
if ! command -v gcc &> /dev/null; then
    echo -e "${YELLOW}GCC não encontrado. Tentando instalar...${NC}"
    
    # Detectar o gerenciador de pacotes
    if command -v apt-get &> /dev/null; then
        echo -e "${GREEN}Detectado: apt-get (Ubuntu/Debian)${NC}"
        sudo apt-get update
        sudo apt-get install -y build-essential
    elif command -v dnf &> /dev/null; then
        echo -e "${GREEN}Detectado: dnf (Fedora)${NC}"
        sudo dnf install -y gcc make
    elif command -v pacman &> /dev/null; then
        echo -e "${GREEN}Detectado: pacman (Arch Linux)${NC}"
        sudo pacman -S --noconfirm base-devel
    elif command -v yum &> /dev/null; then
        echo -e "${GREEN}Detectado: yum (CentOS/RHEL)${NC}"
        sudo yum install -y gcc make
    else
        echo -e "${RED}Gerenciador de pacotes não suportado. Instale o GCC manualmente.${NC}"
        exit 1
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