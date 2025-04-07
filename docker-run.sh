#!/bin/bash

# Cores para output
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== C em Português - Compilador (Docker) ===${NC}"

# Verificar se o Docker está instalado
if ! command -v docker &> /dev/null; then
    echo -e "${YELLOW}Docker não encontrado. Por favor, instale o Docker primeiro.${NC}"
    echo "Visite: https://docs.docker.com/get-docker/"
    exit 1
fi

# Construir a imagem Docker
echo -e "${GREEN}Construindo imagem Docker...${NC}"
docker build -t c-em-portugues .

# Verificar se a construção foi bem-sucedida
if [ $? -ne 0 ]; then
    echo -e "${YELLOW}Falha ao construir a imagem Docker.${NC}"
    exit 1
fi

echo -e "${GREEN}Imagem construída com sucesso!${NC}"

# Perguntar se deseja executar o teste padrão
read -p "Deseja executar o teste padrão? (S/n): " run_test
run_test=${run_test:-S} # Default para "S" se pressionar Enter

if [[ $run_test =~ ^[Ss]$ ]]; then
    echo -e "${GREEN}Executando teste padrão...${NC}"
    docker run --rm -it c-em-portugues /bin/bash -c "cd /app && ./build/compilador < tests/teste1.txt"
else
    echo -e "${GREEN}Iniciando shell no container...${NC}"
    echo -e "${BLUE}Para executar o compilador manualmente:${NC}"
    echo -e "  ${YELLOW}cd /app && ./build/compilador < tests/teste1.txt${NC}"
    echo -e "${BLUE}Para sair do container:${NC}"
    echo -e "  ${YELLOW}exit${NC}"
    docker run --rm -it c-em-portugues
fi 