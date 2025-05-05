# Visão Geral

Esta seção fornece uma visão geral da arquitetura e dos componentes do Compilador C em Português.

## Arquitetura do Compilador

O compilador segue a arquitetura tradicional de compiladores, dividida em várias fases:

1. **Análise Léxica**: Implementada usando Flex, converte o código-fonte em tokens.
2. **Análise Sintática**: Implementada usando Bison, verifica se a sequência de tokens segue a gramática da linguagem.
3. **Análise Semântica**: Verifica se o programa faz sentido semanticamente (tipos, escopo, etc.).
4. **Geração de Código**: Traduz o programa para código executável.

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```
Compiladores---Grupo-5/
├── include/             # Arquivos de cabeçalho
├── src/                 # Código-fonte
│   ├── lexer/           # Analisador léxico (Flex)
│   ├── parser/          # Analisador sintático (Bison)
│   └── ...              # Outros componentes
├── tests/               # Arquivos de teste
├── docs/                # Documentação
├── Makefile             # Script de compilação
├── compilar-linux.sh    # Script para Linux
├── compilar-macos.sh    # Script para macOS
└── compilar.bat         # Script para Windows
```

## Fluxo de Compilação

O processo de compilação segue o seguinte fluxo:

1. O arquivo de entrada é lido pelo analisador léxico (lexer.l).
2. O analisador léxico converte o texto em tokens.
3. Os tokens são passados para o analisador sintático (parser.y).
4. O analisador sintático verifica se a sequência de tokens segue a gramática da linguagem.
5. Se a análise sintática for bem-sucedida, o compilador gera uma árvore sintática abstrata (AST).
6. A AST é usada para análise semântica e geração de código.

## Componentes Principais

### Analisador Léxico (lexer.l)

O analisador léxico é responsável por:
- Reconhecer tokens como identificadores, números, palavras-chave, etc.
- Ignorar espaços em branco e comentários
- Reportar erros léxicos (caracteres inválidos)

### Analisador Sintático (parser.y)

O analisador sintático é responsável por:
- Verificar se a sequência de tokens segue a gramática da linguagem
- Construir a árvore sintática abstrata (AST)
- Reportar erros sintáticos (estrutura inválida)

### Árvore Sintática Abstrata (AST)

A AST representa a estrutura do programa de forma hierárquica, facilitando:
- Análise semântica
- Otimização
- Geração de código

## Tradução de C para Português

Uma das características principais deste compilador é a tradução das palavras-chave de C para português. Isso inclui:

- Tipos de dados: `int` → `inteiro`, `float` → `real`, etc.
- Estruturas de controle: `if` → `se`, `while` → `enquanto`, etc.
- Palavras-chave: `struct` → `estrutura`, `return` → `retorne`, etc.

Esta tradução é implementada no analisador léxico, que reconhece as palavras-chave em português e as mapeia para os tokens correspondentes em C.
