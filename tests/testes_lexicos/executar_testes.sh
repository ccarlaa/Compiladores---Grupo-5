#!/bin/bash

# Script para executar automaticamente todos os testes léxicos
# Autor: Grupo 5
# Data: 01/06/2025

# Cores para formatação da saída
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AMARELO='\033[1;33m'
RESET='\033[0m'

# Diretório raiz do projeto
DIR_RAIZ="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
DIR_TESTES="$DIR_RAIZ/tests/testes_lexicos"

# Compilar o projeto se necessário
echo -e "${AMARELO}Compilando o projeto...${RESET}"
cd "$DIR_RAIZ" && make

if [ $? -ne 0 ]; then
    echo -e "${VERMELHO}Erro ao compilar o projeto. Abortando testes.${RESET}"
    exit 1
fi

echo -e "${VERDE}Compilação concluída com sucesso.${RESET}\n"

# Função para executar um teste e verificar se há erros léxicos
executar_teste() {
    local arquivo="$1"
    local nome_teste="$2"
    
    echo -e "${AMARELO}Executando teste: ${nome_teste}${RESET}"
    echo -e "${AMARELO}Arquivo: ${arquivo}${RESET}"
    echo -e "${AMARELO}----------------------------------------${RESET}"
    
    # Executa o compilador no modo de depuração
    "$DIR_RAIZ/compilador.exe" "$arquivo" -d
    
    if [ $? -eq 0 ]; then
        echo -e "\n${VERDE}Teste concluído.${RESET}\n"
    else
        echo -e "\n${VERMELHO}Erro ao executar o teste.${RESET}\n"
    fi
}

# Executar os testes léxicos
echo -e "${AMARELO}Iniciando testes léxicos...${RESET}\n"

# Teste de erros léxicos gerais
executar_teste "$DIR_TESTES/teste_erros_lexicos.txt" "Erros Léxicos Gerais"

# Teste de erros em laços
executar_teste "$DIR_RAIZ/tests/teste_lacos.txt" "Erros em Laços"

# Teste de erros de pontuação
executar_teste "$DIR_TESTES/teste_pontuacao.txt" "Erros de Pontuação"

echo -e "${VERDE}Todos os testes foram executados.${RESET}"
