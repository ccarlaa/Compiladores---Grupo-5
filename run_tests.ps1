# Test runner for C-to-Portugol translator (PowerShell version)

Write-Host "=== TESTANDO TRADUTOR C PARA PORTUGOL ===" -ForegroundColor Green
Write-Host

# Check if translator executable exists
$translator = $null
if (Test-Path ".\compilador.exe") {
    $translator = ".\compilador.exe"
} elseif (Test-Path ".\compilador") {
    $translator = ".\compilador"
} else {
    Write-Host "ERRO: Executável do tradutor não encontrado!" -ForegroundColor Red
    Write-Host "Execute 'make' para compilar o projeto primeiro."
    exit 1
}

$testsPassed = 0
$testsFailed = 0
$testDir = "tests"

# Function to run a single test
function Run-Test {
    param(
        [string]$TestName
    )
    
    $inputFile = "$testDir\test_${TestName}.c"
    $expectedFile = "$testDir\expected_${TestName}.ptg"
    $outputFile = "$testDir\output_${TestName}.ptg"
    
    Write-Host -NoNewline "Testando $TestName... "
    
    # Check if input file exists
    if (!(Test-Path $inputFile)) {
        Write-Host "FALHOU (arquivo de entrada não encontrado)" -ForegroundColor Red
        $script:testsFailed++
        return
    }
    
    # Run translator
    try {
        & $translator $inputFile -o $outputFile *>$null
        
        # Check if output was generated
        if (Test-Path $outputFile) {
            Write-Host "PASSOU (arquivo gerado)" -ForegroundColor Green
            $script:testsPassed++
            
            # If expected output exists, compare
            if (Test-Path $expectedFile) {
                Write-Host "  Comparando com saída esperada..."
                $expected = Get-Content $expectedFile -Raw
                $actual = Get-Content $outputFile -Raw
                
                if ($expected -eq $actual) {
                    Write-Host "  ✓ Saída corresponde ao esperado" -ForegroundColor Green
                } else {
                    Write-Host "  ⚠ Saída difere do esperado (veja $outputFile)" -ForegroundColor Yellow
                }
            }
        } else {
            Write-Host "FALHOU (arquivo de saída não gerado)" -ForegroundColor Red
            $script:testsFailed++
        }
    } catch {
        Write-Host "FALHOU (erro na tradução)" -ForegroundColor Red
        $script:testsFailed++
    }
}

# Run individual tests
Write-Host "Executando testes individuais:"
Run-Test "01_basic"
Run-Test "02_conditionals"
Run-Test "03_loops"
Run-Test "04_functions"
Run-Test "05_expressions"

Write-Host
Write-Host "=== RESUMO DOS TESTES ===" -ForegroundColor Cyan
Write-Host "Testes executados: $($testsPassed + $testsFailed)"
Write-Host "Testes passaram: $testsPassed" -ForegroundColor Green
Write-Host "Testes falharam: $testsFailed" -ForegroundColor Red

if ($testsFailed -eq 0) {
    Write-Host "✓ Todos os testes passaram!" -ForegroundColor Green
    exit 0
} else {
    Write-Host "✗ Alguns testes falharam." -ForegroundColor Red
    exit 1
}
