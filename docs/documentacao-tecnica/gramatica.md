
# Gramática Formal

Esta seção apresenta a gramática formal utilizada no compilador de C para Portugol, elaborada com base em um subconjunto da linguagem C. A gramática foi definida com o objetivo de facilitar a análise sintática via Bison e permitir uma tradução clara para Portugol.

---

## Objetivo da Gramática

A gramática define as **estruturas sintáticas válidas** da linguagem-fonte reconhecida pelo compilador, com base nas seguintes premissas:

- Uso de uma **gramática livre de contexto (GLC)** para análise descendente
- Reconhecimento de estruturas básicas: funções, declarações, expressões, comandos de controle
- Priorização da clareza e modularidade para facilitar a construção da AST

---

## Estrutura da Gramática

A gramática está dividida em componentes principais, cada um representando uma categoria sintática da linguagem:

### Programa

```bison
programa:
    declaracoes
```

### Declarações

```bison
declaracoes:
    declaracao
  | declaracoes declaracao
```

### Declaração de Função Principal

```bison
funcao_main:
    T_INT T_MAIN T_LPAREN T_RPAREN bloco
```

### Declarações de Variáveis

```bison
declaracao:
    tipo T_ID T_SEMICOLON
  | tipo T_ID T_ASSIGN expressao T_SEMICOLON
```

### Tipos de Dados

```bison
tipo:
    T_INT
  | T_FLOAT
  | T_CHAR
```

---

## Comandos

```bison
comando:
    declaracao
  | atribuicao
  | retorno
  | chamada_funcao T_SEMICOLON
  | condicional
  | iteracao
  | bloco
```

### Atribuições

```bison
atribuicao:
    T_ID T_ASSIGN expressao T_SEMICOLON
```

### Retorno

```bison
retorno:
    T_RETURN expressao T_SEMICOLON
```

---

## Expressões

```bison
expressao:
    expressao T_PLUS expressao
  | expressao T_MINUS expressao
  | expressao T_MULT expressao
  | expressao T_DIV expressao
  | T_LPAREN expressao T_RPAREN
  | T_NUMBER_INT
  | T_NUMBER_FLOAT
  | T_CHAR_LITERAL
  | T_STRING
  | T_ID
```

---

## Estruturas de Controle

### Condicional

```bison
condicional:
    T_IF T_LPAREN expressao T_RPAREN bloco
  | T_IF T_LPAREN expressao T_RPAREN bloco T_ELSE bloco
```

### Iteração

```bison
iteracao:
    T_WHILE T_LPAREN expressao T_RPAREN bloco
```

---

## Bloco

```bison
bloco:
    T_LBRACE comandos T_RBRACE
```

```bison
comandos:
    comando
  | comandos comando
```

---

## Chamada de Função

```bison
chamada_funcao:
    T_ID T_LPAREN argumentos T_RPAREN

argumentos:
    /* vazio */
  | lista_argumentos

lista_argumentos:
    expressao
  | lista_argumentos T_COMMA expressao
```

---

## Considerações sobre Ambiguidades

A gramática resolve ambiguidades por meio de regras de precedência e associatividade declaradas no início do arquivo `parser.y`, como:

```bison
%left T_PLUS T_MINUS
%left T_MULT T_DIV
%right T_ASSIGN
```

Essas declarações evitam conflitos típicos de operadores binários.

---

## Cobertura e Limitações

A gramática cobre:

- Função principal `main()`
- Declaração de variáveis
- Expressões aritméticas
- Condicionais e laços
- Funções com parâmetros

Limitações conhecidas:

- Não há suporte a `struct`, `for`, `switch`, ponteiros ou arrays
- A chamada de função é suportada apenas com passagem por valor
- Apenas um escopo global (sem aninhamento de blocos ou múltiplas funções usuais)

---

## Conclusão

A gramática foi elaborada para balancear **simplicidade, clareza e funcionalidade**, permitindo reconhecer estruturas típicas de programas em C e traduzi-las adequadamente para Portugol. Ela serve de base para a análise sintática, construção da AST e posterior geração de código.
