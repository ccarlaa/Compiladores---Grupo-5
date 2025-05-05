# Instalação

Este guia explica como instalar e configurar o Compilador C em Português em diferentes sistemas operacionais.

## Pré-requisitos

Antes de instalar o compilador, certifique-se de que seu sistema atenda aos seguintes requisitos:

- GCC ou outro compilador C
- Flex (analisador léxico)
- Bison (analisador sintático)
- Make

## Instalação no Linux

1. Clone o repositório:
   ```bash
   git clone https://github.com/ccarlaa/Compiladores---Grupo-5.git
   cd Compiladores---Grupo-5
   ```

2. Execute o script de compilação:
   ```bash
   ./compilar-linux.sh
   ```

3. Verifique se a instalação foi bem-sucedida:
   ```bash
   ./compilador.exe tests/teste1.txt
   ```

## Instalação no macOS

1. Clone o repositório:
   ```bash
   git clone https://github.com/ccarlaa/Compiladores---Grupo-5.git
   cd Compiladores---Grupo-5
   ```

2. Execute o script de compilação:
   ```bash
   ./compilar-macos.sh
   ```

3. Verifique se a instalação foi bem-sucedida:
   ```bash
   ./compilador.exe tests/teste1.txt
   ```

## Instalação no Windows

1. Clone o repositório:
   ```bash
   git clone https://github.com/ccarlaa/Compiladores---Grupo-5.git
   cd Compiladores---Grupo-5
   ```

2. Execute o script de compilação:
   ```bash
   compilar.bat
   ```

3. Verifique se a instalação foi bem-sucedida:
   ```bash
   compilador.exe tests/teste1.txt
   ```

## Usando Docker

Para facilitar a instalação e evitar problemas de dependências, também fornecemos um Dockerfile:

1. Construa a imagem Docker:
   ```bash
   docker build -t compilador-portugues .
   ```

2. Execute o compilador usando Docker:
   ```bash
   ./docker-run.sh tests/teste1.txt
   ```

## Solução de Problemas

Se você encontrar problemas durante a instalação, verifique:

1. Se todas as dependências estão instaladas corretamente
2. Se os scripts de compilação têm permissão de execução (`chmod +x compilar-linux.sh`)
3. Se há erros específicos no console durante a compilação
