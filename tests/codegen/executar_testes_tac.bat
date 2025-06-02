@echo off
REM Script para executar testes de código intermediário (TAC) no Windows
REM Autor: Cascade
REM Data: 02/06/2025

setlocal enabledelayedexpansion

REM Diretórios do projeto
set "PROJETO_DIR=%~dp0..\..\"
set "TESTES_DIR=%PROJETO_DIR%tests\codegen"
set "SAIDA_DIR=%PROJETO_DIR%tests\codegen\saida"

REM Arquivo do compilador
set "COMPILADOR=%PROJETO_DIR%build\compilador.exe"

REM Criar diretório de saída se não existir
if not exist "%SAIDA_DIR%" mkdir "%SAIDA_DIR%"

echo.
echo [33mCompilando o projeto...[0m
cd "%PROJETO_DIR%" && nmake clean && nmake
if errorlevel 1 (
    echo [31mErro ao compilar o projeto![0m
    exit /b 1
)
echo [32mCompilação concluída.[0m
echo.

echo [33mIniciando execução dos testes de código intermediário...[0m
echo.

REM Contar total de testes
set "TOTAL=0"
for %%F in ("%TESTES_DIR%\teste_*.txt") do (
    set /a TOTAL+=1
)

REM Executar cada teste
set "CONTADOR=0"
for %%F in ("%TESTES_DIR%\teste_*.txt") do (
    set "ARQUIVO=%%F"
    set "NOME=%%~nF"
    set "SAIDA=%SAIDA_DIR%\!NOME!_tac.txt"
    
    echo [33mExecutando teste: [0m!NOME!
    
    REM Executar o compilador com o arquivo de teste e a flag para gerar TAC
    "%COMPILADOR%" -t "!ARQUIVO!" > "!SAIDA!" 2>&1
    
    if errorlevel 1 (
        echo [31m✗ Erro ao executar teste: [0m!NOME!
        echo   Verifique o arquivo de saída: !SAIDA!
    ) else (
        echo [32m✓ Teste concluído: [0m!NOME!
        echo   Saída salva em: !SAIDA!
    )
    echo.
    
    set /a CONTADOR+=1
)

REM Gerar relatório de resumo
echo [32m=== Resumo da Execução ===[0m
echo Total de testes executados: %TOTAL%
echo Resultados salvos em: %SAIDA_DIR%
echo [32m===========================[0m

echo.
echo [33mNota: Examine os arquivos de saída para verificar se o código TAC foi gerado corretamente.[0m
echo [33mVocê pode comparar os resultados com a saída esperada para cada teste.[0m

endlocal
