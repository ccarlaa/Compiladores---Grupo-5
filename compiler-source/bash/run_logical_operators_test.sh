#!/bin/bash

# Nome do executável gerado pelo Makefile
COMPILADOR="./compilador"

# Arquivos de teste
INPUT_FILE="tests/logical_operators_test/logical_operators_test.c"
EXPECTED_FILE="tests/logical_operators_test/logical_operators_expected.txt"
TEMP_OUTPUT="/tmp/test_output.txt"

# Verifica se o compilador existe antes de continuar
if [ ! -f "$COMPILADOR" ]; then
    echo "❌ Erro: O executável '$COMPILADOR' não foi encontrado."
    echo "   Por favor, compile o projeto com o comando 'make' primeiro."
    exit 1
fi

# Executa o compilador com o arquivo de entrada e salva a saída
cat "$INPUT_FILE" | $COMPILADOR > "$TEMP_OUTPUT"

# Compara a saída gerada com a saída esperada
if diff -w -B "$TEMP_OUTPUT" "$EXPECTED_FILE"; then
  echo "✅ Teste passou!"
else
  echo "❌ Teste falhou! Diferenças encontradas (Esperado vs. Obtido):"
  # Mostra as diferenças lado a lado para facilitar a comparação
  diff --side-by-side -W 200 "$EXPECTED_FILE" "$TEMP_OUTPUT"
fi
