@echo off
REM Compilador C para Portugol - Script de Compilacao Windows
echo === COMPILANDO TRADUTOR C PARA PORTUGOL ===

gcc -std=c99 -Wall -Wextra -DMANUAL_MODE -o compilador.exe src\main.c

if %ERRORLEVEL% == 0 (
    echo.
    echo Compilacao concluida com sucesso!
    echo Executavel: compilador.exe
    echo Modo: Manual ^(sem flex/bison^)
    echo.
    echo Para testar:
    echo   compilador.exe tests\test_01_basic.c
) else (
    echo.
    echo ERRO: Falha na compilacao!
    echo Verifique se o GCC esta instalado e disponivel no PATH.
)

pause
