#!/bin/bash

# Script para executar automaticamente todos os testes do compilador
# Autor: Grupo 5
# Data: 01/06/2025

# Cores para formatação da saída
VERDE='\033[0;32m'
VERMELHO='\033[0;31m'
AMARELO='\033[1;33m'
RESET='\033[0m'

# Diretório raiz do projeto
DIR_RAIZ="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Compilar o projeto
echo -e "${AMARELO}Compilando o projeto...${RESET}"
cd "$DIR_RAIZ" && make

if [ $? -ne 0 ]; then
    echo -e "${VERMELHO}Erro ao compilar o projeto. Abortando testes.${RESET}"
    exit 1
fi

echo -e "${VERDE}Compilação concluída com sucesso.${RESET}\n"

# Função para executar um teste
executar_teste() {
    local arquivo="$1"
    local nome_teste="$2"
    local modo="$3"
    
    echo -e "${AMARELO}Executando teste: ${nome_teste}${RESET}"
    echo -e "${AMARELO}Arquivo: ${arquivo}${RESET}"
    echo -e "${AMARELO}----------------------------------------${RESET}"
    
    if [ "$modo" == "debug" ]; then
        # Executa o compilador no modo de depuração
        "$DIR_RAIZ/compilador.exe" "$arquivo" -d
    else
        # Executa o compilador no modo normal
        "$DIR_RAIZ/compilador.exe" "$arquivo"
    fi
    
    if [ $? -eq 0 ]; then
        echo -e "\n${VERDE}Teste concluído.${RESET}\n"
    else
        echo -e "\n${VERMELHO}Erro ao executar o teste.${RESET}\n"
    fi
}

# Executar testes básicos
echo -e "${AMARELO}Iniciando testes básicos...${RESET}\n"

for i in {1..5}; do
    executar_teste "$DIR_RAIZ/tests/teste$i.txt" "Teste Básico $i" "normal"
done

# Executar testes léxicos
echo -e "${AMARELO}Iniciando testes léxicos...${RESET}\n"

# Teste de erros léxicos gerais
executar_teste "$DIR_RAIZ/tests/testes_lexicos/teste_erros_lexicos.txt" "Erros Léxicos Gerais" "debug"

# Teste de erros em laços
executar_teste "$DIR_RAIZ/tests/teste_lacos.txt" "Erros em Laços" "debug"

# Teste de erros de pontuação
executar_teste "$DIR_RAIZ/tests/testes_lexicos/teste_pontuacao.txt" "Erros de Pontuação" "debug"

# Executar testes sintáticos
echo -e "${AMARELO}Iniciando testes sintáticos...${RESET}\n"
executar_teste "$DIR_RAIZ/tests/teste6.txt" "Teste Sintático" "normal"

# Executar testes de estruturas de controle
echo -e "${AMARELO}Iniciando testes de estruturas de controle...${RESET}\n"
executar_teste "$DIR_RAIZ/tests/teste_lacos.txt" "Estruturas de Controle" "normal"

echo -e "${VERDE}Todos os testes foram executados.${RESET}"
echo -e "${AMARELO}Verifique os resultados acima para confirmar o funcionamento do compilador.${RESET}"
