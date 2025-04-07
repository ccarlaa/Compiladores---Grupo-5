@echo off
echo Compilando projeto C em Português...

REM Verificar se o Bison está instalado
where bison >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Erro: Bison não encontrado no PATH. Por favor, instale o Bison.
    exit /b 1
)

REM Verificar se o Flex está instalado
where flex >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Erro: Flex não encontrado no PATH. Por favor, instale o Flex.
    exit /b 1
)

REM Criar diretórios necessários
if not exist build mkdir build

REM Compilar o parser com Bison
echo Gerando parser com Bison...
bison -d src/parser/parser.y -o parser.tab.c

REM Compilar o lexer com Flex
echo Gerando lexer com Flex...
flex src/lexer/lexer.l

REM Compilar os arquivos fonte
echo Compilando arquivos fonte...
gcc -Wall -Iinclude -c lex.yy.c -o lex.yy.o
gcc -Wall -Iinclude -c parser.tab.c -o parser.tab.o
gcc -Wall -Iinclude -c src/main.c -o main.o
gcc -Wall -Iinclude -c src/ast/ast.c -o ast.o

REM Linkar todos os objetos
echo Linkando executável...
gcc -Wall -Iinclude main.o lex.yy.o parser.tab.o ast.o -o compilador.exe

echo Compilação concluída!

REM Perguntar se deseja executar o teste
set /p run_test=Deseja executar o teste? (S/N): 
if /i "%run_test%"=="S" (
    echo Executando teste...
    compilador.exe < tests/teste1.txt
)

echo.
echo Processo finalizado! 