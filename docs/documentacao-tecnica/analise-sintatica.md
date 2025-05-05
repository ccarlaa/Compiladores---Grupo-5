# Análise Sintática

Esta seção detalha a implementação do analisador sintático (parser) do Compilador C em Português.

## Visão Geral

O analisador sintático é implementado usando o Bison (gerador de analisadores sintáticos) e é responsável por verificar se a sequência de tokens fornecida pelo analisador léxico segue a gramática da linguagem. Ele constrói uma árvore sintática abstrata (AST) que representa a estrutura do programa.

## Implementação

O arquivo principal do analisador sintático é `src/parser/parser.y`, que contém as regras gramaticais para a linguagem C traduzida para português.

### Estrutura do Arquivo parser.y

O arquivo `parser.y` é dividido em várias seções:

1. **Declarações**: Contém inclusões de arquivos, definições de tipos, tokens e precedência de operadores.
2. **Regras Gramaticais**: Define a gramática da linguagem usando notação BNF.
3. **Código do Usuário**: Contém funções auxiliares e código C adicional.

### Regras Gramaticais Principais

#### Programa

A regra inicial da gramática define um programa como uma sequência de declarações:

```c
programa
    : declaracoes                { 
                                    printf("Programa analisado com sucesso!\n");
                                  }
    ;
```

#### Declarações

As declarações podem ser de variáveis, funções ou estruturas:

```c
declaracoes
    : declaracao                 { }
    | declaracoes declaracao     { }
    ;

declaracao
    : declaracao_variavel        { }
    | declaracao_funcao          { }
    | definicao_funcao           { }
    | declaracao_estrutura       { }
    ;
```

#### Declaração de Variáveis

As variáveis podem ser declaradas com diferentes tipos e opcionalmente inicializadas:

```c
declaracao_variavel
    : tipo IDENTIFICADOR PONTO_E_VIRGULA                        { }
    | tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_E_VIRGULA   { }
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA { }
    ;
```

#### Declaração de Funções

As funções podem ser declaradas com ou sem parâmetros:

```c
declaracao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN PONTO_E_VIRGULA { }
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN PONTO_E_VIRGULA { }
    ;
```

#### Definição de Funções

As funções podem ser definidas com ou sem parâmetros, incluindo a função principal:

```c
definicao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN bloco_comandos  { }
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN bloco_comandos { }
    | PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos { }
    | tipo PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos { }
    ;
```

#### Declaração de Estruturas

As estruturas são declaradas com uma lista de campos:

```c
declaracao_estrutura
    : ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA { }
    ;

lista_campos
    : declaracao_campo        { }
    | lista_campos declaracao_campo { }
    ;

declaracao_campo
    : tipo IDENTIFICADOR PONTO_E_VIRGULA                        { }
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA { }
    ;
```

#### Comandos

A gramática suporta vários tipos de comandos, incluindo estruturas de controle:

```c
comando
    : SE ABRE_PAREN expressao FECHA_PAREN comando                  { }
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando    { }
    | ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando            { }
    | PARA ABRE_PAREN expressao_opt PONTO_E_VIRGULA expressao_opt PONTO_E_VIRGULA expressao_opt FECHA_PAREN comando { }
    | FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA { }
    | bloco_comandos                                               { }
    | expressao PONTO_E_VIRGULA                                    { }
    | RETORNE expressao_opt PONTO_E_VIRGULA                        { }
    | CONTINUE PONTO_E_VIRGULA                                     { }
    | QUEBRE PONTO_E_VIRGULA                                       { }
    | declaracao_variavel                                          { }
    | PONTO_E_VIRGULA                                              { }
    ;
```

#### Expressões

A gramática suporta várias formas de expressões, incluindo operações aritméticas, lógicas e de comparação:

```c
expressao
    : atribuicao                                                  { }
    ;

atribuicao
    : condicional                                                 { }
    | unario ATRIBUICAO atribuicao                                { }
    | unario MAIS_IGUAL atribuicao                                { }
    | unario MENOS_IGUAL atribuicao                               { }
    | unario VEZES_IGUAL atribuicao                               { }
    | unario DIVIDIDO_IGUAL atribuicao                            { }
    | unario MODULO_IGUAL atribuicao                              { }
    ;
```

## Resolução de Problemas Específicos

### Suporte para Função Principal com Tipo de Retorno

Adicionamos suporte para que a função principal possa ter um tipo de retorno:

```c
definicao_funcao
    : /* ... outras regras ... */
    | PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos { }
    | tipo PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos { }
    ;
```

### Suporte para Arrays em Campos de Estruturas

Implementamos suporte para arrays dentro de campos de estruturas:

```c
declaracao_campo
    : tipo IDENTIFICADOR PONTO_E_VIRGULA                        { }
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA { }
    ;
```

### Suporte para o Operador de Módulo

Adicionamos suporte para o operador de módulo (%) em expressões:

```c
multiplicativo
    : cast                                                        { }
    | multiplicativo VEZES cast                                   { }
    | multiplicativo DIVIDIDO cast                                { }
    | multiplicativo MODULO cast                                  { }
    ;
```

### Suporte para Constantes e Variáveis Estáticas

Adicionamos suporte para declarações de constantes e variáveis estáticas:

```c
declaracao_variavel
    : /* ... outras regras ... */
    | CONSTANTE tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_E_VIRGULA { }
    | ESTATICO tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_E_VIRGULA { }
    ;
```

## Conflitos na Gramática

A gramática pode apresentar alguns conflitos, como o "conflito shift/reduce" relacionado ao "problema do else pendente". Este é um conflito comum em gramáticas para linguagens como C e pode ser resolvido usando a precedência de operadores.

## Extensões Futuras

Possíveis melhorias para o analisador sintático incluem:

1. Melhor tratamento de erros sintáticos
2. Suporte para mais construções da linguagem C
3. Otimização da gramática para reduzir conflitos
4. Implementação de ações semânticas para construir uma AST mais completa
