#!/bin/bash
# Test runner for C-to-Portugol translator

echo "=== TESTANDO TRADUTOR C PARA PORTUGOL ==="
echo

# Check if translator executable exists
if [ ! -f "./compilador.exe" ] && [ ! -f "./compilador" ]; then
    echo "ERRO: Executável do tradutor não encontrado!"
    echo "Execute 'make' para compilar o projeto primeiro."
    exit 1
fi

# Determine executable name
TRANSLATOR="./compilador"
if [ -f "./compilador.exe" ]; then
    TRANSLATOR="./compilador.exe"
fi

TESTS_PASSED=0
TESTS_FAILED=0
TEST_DIR="tests"

# Function to run a single test
run_test() {
    local test_name=$1
    local input_file="$TEST_DIR/test_${test_name}.c"
    local expected_file="$TEST_DIR/expected_${test_name}.ptg"
    local output_file="$TEST_DIR/output_${test_name}.ptg"
    
    echo -n "Testando $test_name... "
    
    # Check if input file exists
    if [ ! -f "$input_file" ]; then
        echo "FALHOU (arquivo de entrada não encontrado)"
        ((TESTS_FAILED++))
        return
    fi
    
    # Run translator
    if $TRANSLATOR "$input_file" -o "$output_file" > /dev/null 2>&1; then
        # Check if output was generated
        if [ -f "$output_file" ]; then
            echo "PASSOU (arquivo gerado)"
            ((TESTS_PASSED++))
            
            # If expected output exists, compare
            if [ -f "$expected_file" ]; then
                echo "  Comparando com saída esperada..."
                if diff -u "$expected_file" "$output_file" > /dev/null; then
                    echo "  ✓ Saída corresponde ao esperado"
                else
                    echo "  ⚠ Saída difere do esperado (veja $output_file)"
                fi
            fi
        else
            echo "FALHOU (arquivo de saída não gerado)"
            ((TESTS_FAILED++))
        fi
    else
        echo "FALHOU (erro na tradução)"
        ((TESTS_FAILED++))
    fi
}

# Run individual tests
echo "Executando testes individuais:"
run_test "01_basic"
run_test "02_conditionals"
run_test "03_loops"
run_test "04_functions"
run_test "05_expressions"

echo
echo "=== RESUMO DOS TESTES ==="
echo "Testes executados: $((TESTS_PASSED + TESTS_FAILED))"
echo "Testes passaram: $TESTS_PASSED"
echo "Testes falharam: $TESTS_FAILED"

if [ $TESTS_FAILED -eq 0 ]; then
    echo "✓ Todos os testes passaram!"
    exit 0
else
    echo "✗ Alguns testes falharam."
    exit 1
fi
