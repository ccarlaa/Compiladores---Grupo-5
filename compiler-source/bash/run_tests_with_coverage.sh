#!/bin/bash

set -e

PROJECT_DIR="$(dirname "$(dirname "$0")")"
TESTS_DIR="$PROJECT_DIR/bash"
COVERAGE_FILE="$PROJECT_DIR/coverage_report.txt"
TEMP_STDERR="/tmp/compilador_stderr.txt"

echo "🔍 Limpando cobertura anterior e stderr..."
rm -f "$COVERAGE_FILE" "$TEMP_STDERR"

echo "🚀 Executando testes..."
success=true
for script in "$TESTS_DIR"/*.sh; do
  echo "➡️  Executando $script"
  if ! bash "$script" 2>> "$TEMP_STDERR"; then
    echo "❌ Falha no teste $script"
    success=false
  fi
done

echo "📊 Extraindo cobertura para $COVERAGE_FILE..."
grep -A 100 "===== COBERTURA DAS REGRAS DA GRAMÁTICA =====" "$TEMP_STDERR" > "$COVERAGE_FILE" || echo "⚠️ Nenhuma cobertura encontrada."

if [ "$success" = true ]; then
  echo "✅ Todos os testes passaram com sucesso!"
else
  echo "❌ Alguns testes falharam. Verifique os logs."
  exit 1
fi
