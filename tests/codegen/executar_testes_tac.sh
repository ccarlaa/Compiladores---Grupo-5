#!/bin/bash

# Script para executar testes de código intermediário (TAC)
# Autor: Cascade
# Data: 02/06/2025

# Diretórios do projeto
PROJETO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
TESTES_DIR="$PROJETO_DIR/tests/codegen"
SAIDA_DIR="$PROJETO_DIR/tests/codegen/saida"

# Arquivo do compilador
COMPILADOR="$PROJETO_DIR/build/compilador"

# Criar diretório de saída se não existir
mkdir -p "$SAIDA_DIR"

# Cores para output
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AMARELO='\033[0;33m'
RESET='\033[0m'

# Compilar o projeto
echo -e "${AMARELO}Compilando o projeto...${RESET}"
cd "$PROJETO_DIR" && make clean && make
if [ $? -ne 0 ]; then
    echo -e "${VERMELHO}Erro ao compilar o projeto!${RESET}"
    exit 1
fi
echo -e "${VERDE}Compilação concluída.${RESET}\n"

# Função para executar um teste
executar_teste() {
    local arquivo="$1"
    local nome=$(basename "$arquivo" .txt)
    local saida="$SAIDA_DIR/${nome}_tac.txt"
    
    echo -e "${AMARELO}Executando teste: ${RESET}$nome"
    
    # Executar o compilador com o arquivo de teste e a flag para gerar TAC
    $COMPILADOR -t "$arquivo" > "$saida" 2>&1
    
    if [ $? -eq 0 ]; then
        echo -e "${VERDE}✓ Teste concluído: ${RESET}$nome"
        echo -e "  Saída salva em: $saida\n"
    else
        echo -e "${VERMELHO}✗ Erro ao executar teste: ${RESET}$nome"
        echo -e "  Verifique o arquivo de saída: $saida\n"
    fi
}

# Listar todos os arquivos de teste
TESTES=$(find "$TESTES_DIR" -name "teste_*.txt" | sort)

# Verificar se existem testes
if [ -z "$TESTES" ]; then
    echo -e "${VERMELHO}Nenhum arquivo de teste encontrado!${RESET}"
    exit 1
fi

# Executar cada teste
echo -e "${AMARELO}Iniciando execução dos testes de código intermediário...${RESET}\n"

for teste in $TESTES; do
    executar_teste "$teste"
done

# Gerar relatório de resumo
TOTAL=$(echo "$TESTES" | wc -l)
echo -e "${VERDE}=== Resumo da Execução ===${RESET}"
echo -e "Total de testes executados: $TOTAL"
echo -e "Resultados salvos em: $SAIDA_DIR"
echo -e "${VERDE}===========================${RESET}"

echo -e "\n${AMARELO}Nota: Examine os arquivos de saída para verificar se o código TAC foi gerado corretamente.${RESET}"
echo -e "${AMARELO}Você pode comparar os resultados com a saída esperada para cada teste.${RESET}"
