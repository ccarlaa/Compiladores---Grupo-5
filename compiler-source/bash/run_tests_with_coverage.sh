#!/bin/bash

COMPILADOR=./compilador
LOG="/tmp/grammar_coverage.txt"

echo "🧪 Executando testes com cobertura..."
rm -f "$LOG"

success=true
for script in bash/*.sh; do
    # Evita executar a si mesmo
    if [[ "$script" == "bash/run_tests_with_coverage.sh" ]]; then
        continue
    fi

    echo "Executando $script..."
    if ! bash "$script" | tee -a "$LOG"; then
        echo "❌ Falha no teste $script"
        success=false
    fi
    echo ""
done

echo ""
if $success; then
    echo "✅ Todos os testes passaram!"
else
    echo "⚠️ Alguns testes falharam!"
fi

echo ""
echo "📊 Relatório de cobertura das regras da gramática:"
grep 'COBERTURA DAS REGRAS DA GRAMÁTICA' -A 100 "$LOG" || echo "⚠️ Nenhum relatório encontrado"
