# Análise Sintática

Esta seção documenta a implementação do analisador sintático definido no arquivo `parser.y`. O parser utiliza **Bison**, um gerador de analisadores descendentes para gramáticas livres de contexto. Ele valida a estrutura do código reconhecido pelo analisador léxico (`lexer.l`), constrói a **Árvore Sintática Abstrata (AST)** e realiza verificações de semântica.

---

## Objetivo

- Validar a estrutura sintática do programa segundo uma gramática definida
- Construir a AST de maneira incremental
- Preparar os dados para a verificação semântica e tradução

---

## Estratégia de Parsing Utilizada

O compilador utiliza a estratégia **LR (Left-to-Right)**, por meio da ferramenta **Bison**, que gera um parser ascendente com base em uma gramática livre de contexto.

### Por que LR?

O LR é adequado para esse projeto por atender aos seguintes critérios:

- **Poder gramatical**: é capaz de reconhecer uma classe maior de gramáticas do que LL (por exemplo, suporta recursão à esquerda), o que permite escrever regras mais próximas da linguagem C.
- **Simplicidade de uso com Bison**: o Bison já fornece a infraestrutura pronta para geração de parsers LR, com tratamento automático de conflitos comuns e suporte a precedência de operadores.
- **Precisão e robustez**: o parser LR detecta erros de forma mais precisa e oferece mensagens melhores do que parsers simples LL ou ad-hoc.
- **Integração com ações semânticas**: o modelo de parser ascendente se encaixa bem com a construção da AST a partir das folhas para a raiz, refletindo naturalmente a semântica de linguagens imperativas.

### Comparação com outras estratégias

| Estratégia | Características | Por que não foi usada? |
|-----------|------------------|-------------------------|
| **LL**    | Parser descendente, fácil de depurar, mais restrito (não suporta recursão à esquerda) | Exigiria reescrever a gramática em formato não natural para C |
| **GLR**   | Suporta ambiguidade e múltiplos caminhos, mais poderoso | Complexidade maior e desnecessária para o escopo da linguagem implementada |

A escolha por um parser **LR via Bison** oferece um bom equilíbrio entre **potência, suporte a gramáticas realistas**, e **integração com análise semântica e geração de código**, sendo a abordagem mais adequada para um compilador educacional que visa cobrir um subconjunto significativo da linguagem C.

## Estrutura do Arquivo `parser.y`

O arquivo segue o padrão de três seções:

---

### 1. **Declarações de código C (`%{ ... %}`)**

Inclui bibliotecas e variáveis globais usadas nas ações semânticas:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"
#include "ast.h"
#include "y.tab.h"

extern int yylineno;

void yyerror(const char *s);
int yylex(void);

ASTNode *ast_root = NULL;
int current_scope = 0;
```

Funções auxiliares como `create_binary_op()` e `create_assignment_node()` são usadas para montar a AST.

---

### 2. **Declarações de tokens, tipos e precedência**

Tokens importados do lexer são declarados com tipos associados via `%token <tipo>`:

```c
%union {
    char *sval;
    int ival;
    float fval;
    ASTNode *ast;
}

%token <sval> T_ID T_STRING T_CHAR_LITERAL T_NUMBER_FLOAT
%token <ival> T_NUMBER_INT
```

Também são declaradas as palavras-chave (`T_IF`, `T_RETURN`, etc.), operadores (`T_PLUS`, `T_EQ`, etc.), e símbolos (`T_LPAREN`, `T_RBRACE`, etc.).

A precedência dos operadores é especificada para resolver ambiguidades:

```c
%right T_ASSIGN T_PLUS_ASSIGN T_MINUS_ASSIGN
%left T_OR
%left T_AND
%left T_BIT_OR
%left T_EQ T_NEQ
%left T_GT T_LT T_GE T_LE
%left T_PLUS T_MINUS
%left T_MULT T_DIV
%right T_NOT
```

---

### 3. **Regras Gramaticais e Ações**

As produções sintáticas são definidas com regras BNF-like, com ações em C entre `{}`. Exemplo:

```bison
programa:
    declaracoes
    {
        ast_root = $1;
    }
;
```

Cada produção retorna (via `$$`) um ponteiro para um nó da AST.

Outros exemplos de regras incluem:

#### Função principal

```bison
funcao_main:
    T_INT T_MAIN T_LPAREN T_RPAREN bloco
    {
        $$ = create_function_node("inteiro", "inicio", NULL, $5);
    }
;
```

#### Declaração de variável

```bison
declaracao:
    tipo T_ID T_SEMICOLON
    {
        $$ = create_declaration_node($1, $2, NULL);
    }
;
```

#### Expressões aritméticas e relacionais

```bison
expressao:
    expressao T_PLUS expressao
    {
        $$ = create_binary_op("+", $1, $3);
    }
  | T_LPAREN expressao T_RPAREN
    {
        $$ = $2;
    }
  | T_NUMBER_INT
    {
        $$ = create_literal_node("int", $1);
    }
;
```

---

## Construção da AST

Cada produção cria um nó da AST com chamadas:

- `create_declaration_node()`
- `create_binary_op()`
- `create_assignment_node()`

Essas funções estão implementadas em `ast.c` e representam cada parte do código como um nó com tipo, valor e filhos.

A raiz da AST é armazenada em `ast_root`.

---

## Tratamento de Erros

Erros sintáticos são tratados com a função `yyerror()`:

```c
void yyerror(const char *s) {
    fprintf(stderr, "Erro na linha %d: %s
", yylineno, s);
}
```

Se ocorrer um erro durante a análise, ele será relatado com a linha correspondente.

---

## Exemplo de Fluxo

**Entrada C:**

```c
int main() {
    int x = 10;
    return x;
}
```

**Produções ativadas:**

- `programa → declaracoes`
- `funcao_main`
- `bloco → comandos`
- `comando → declaracao`
- `declaracao → tipo T_ID T_SEMICOLON`
- `comando → return`

**AST gerada** (estrutura lógica simplificada):

```
programa
└── funcao inicio
    ├── declaracao: inteiro x
    └── retorno: x
```

---

## Integração com o Lexer

O parser recebe tokens por meio da função `yylex()`, que é automaticamente invocada. Cada token enviado pelo lexer deve estar declarado no parser com `%token`, com os mesmos nomes e tipos.

---