# Visão Geral

Esta seção fornece uma visão geral da arquitetura, estrutura e funcionamento do Compilador de C para Portugol, desenvolvido com base em Flex, Bison e C.

---

## Arquitetura do Compilador

O compilador foi implementado em C e segue a arquitetura clássica em etapas, composta por:

1. **Análise Léxica (Lexer)**  
   Utiliza o Flex para reconhecer tokens válidos a partir do código-fonte.

2. **Análise Sintática (Parser)**  
   Utiliza o Bison para validar a estrutura do programa com base em uma gramática livre de contexto.

3. **Análise Semântica**  
   Realiza verificação de escopo, declaração de variáveis, tipos e regras semânticas personalizadas.

4. **Geração de AST (Árvore Sintática Abstrata)**  
   Representação intermediária do código, utilizada para facilitar a tradução.

5. **Geração de Código**  
   Traduz a AST para uma versão equivalente em Portugol, respeitando a estrutura lógica do programa original.

---

## Estrutura do Projeto

O projeto está organizado da seguinte forma:

```plaintext
compiler-source/
├── bash/                    # Scripts automatizados de testes
├── build/                   # Arquivos gerados durante a compilação (temporários)
├── include/                 # Arquivos de cabeçalho (headers)
│   ├── ast.h
│   ├── conversor.h
│   └── parser.tab.h         # Gerado automaticamente pelo Bison
├── lexer/
│   └── lexer.l              # Regras léxicas (Flex)
├── parser/
│   └── parser.y             # Gramática e ações semânticas (Bison)
├── src/                     # Implementações dos módulos em C
│   ├── ast.c                # Construção e manipulação da AST
│   ├── conversor.c          # Tradução da AST para Portugol
│   └── main.c               # Função principal que invoca o compilador
├── tests/                   # Arquivos de entrada para testes manuais
├── compilador               # Executável gerado após a compilação
├── Makefile                 # Script de build automatizado
```

---

## Fluxo de Compilação

O fluxo completo da execução do compilador é o seguinte:

1. **Entrada**: código-fonte em C via stdin (`./compilador < arquivo.c`)
2. **Flex (`lexer.l`)** identifica os tokens do código-fonte
3. **Bison (`parser.y`)** interpreta os tokens com base na gramática
4. **Construção da AST** com base nas ações sintáticas
5. **Verificações semânticas** (tipos, escopos, redeclarações)
6. **Geração do código em Portugol**
7. **Saída**: código equivalente impresso em stdout

---

## Componentes Principais

* **Flex (`lexer.l`)**: identifica identificadores, palavras-chave, números, strings, operadores, delimitadores, etc.
* **Bison (`parser.y`)**: define a estrutura da linguagem-fonte e associa ações semânticas às produções.
* **`ast.c/h`**: define a estrutura em árvore das instruções analisadas, com suporte a nós compostos, operadores, chamadas de função, etc.
* **`tabela.c/h`**: armazena símbolos como variáveis, funções e seus respectivos tipos e escopos.
* **`main.c`**: inicializa a compilação, invoca o parser, exibe mensagens de erro e imprime a saída final.

---

### Tradução para Portugol

Uma das características centrais deste compilador é a **tradução direta das palavras-chave da linguagem C para Portugol**. Alguns exemplos:

| C        | Portugol   |
| -------- | ---------- |
| `int`    | `inteiro`  |
| `float`  | `real`     |
| `char`   | `caracter` |
| `if`     | `se`       |
| `else`   | `senao`    |
| `while`  | `enquanto` |
| `return` | `retorne`  |
| `printf` | `escreva`  |
| `scanf`  | `leia`     |

Essa substituição é feita durante a travessia da AST e a geração da saída textual.
