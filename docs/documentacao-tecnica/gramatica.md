# Gramática

Esta seção apresenta a gramática formal da linguagem C traduzida para português, implementada no Compilador C em Português.

## Notação

A gramática é apresentada em notação BNF (Backus-Naur Form), onde:

- Os símbolos não-terminais são escritos em minúsculas (ex: `programa`, `declaracao`)
- Os símbolos terminais são escritos em MAIÚSCULAS (ex: `IDENTIFICADOR`, `NUMERO`)
- O símbolo `|` representa alternativas
- Os símbolos entre colchetes `[ ]` são opcionais
- Os símbolos entre chaves `{ }` podem aparecer zero ou mais vezes

## Gramática Completa

### Programa

```
programa
    : declaracoes
    ;

declaracoes
    : declaracao
    | declaracoes declaracao
    ;

declaracao
    : declaracao_variavel
    | declaracao_funcao
    | definicao_funcao
    | declaracao_estrutura
    ;
```

### Declarações de Variáveis

```
declaracao_variavel
    : tipo IDENTIFICADOR PONTO_E_VIRGULA
    | tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_E_VIRGULA
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA
    | CONSTANTE tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_E_VIRGULA
    | ESTATICO tipo IDENTIFICADOR ATRIBUICAO expressao PONTO_E_VIRGULA
    ;

tipo
    : TIPO_INTEIRO
    | TIPO_REAL
    | TIPO_DUPLO
    | TIPO_CARACTERE
    | TIPO_VAZIO
    | TIPO_LONGO
    | TIPO_CURTO
    | TIPO_SEM_SINAL
    | TIPO_COM_SINAL
    | ESTRUTURA IDENTIFICADOR
    ;
```

### Declarações e Definições de Funções

```
declaracao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN PONTO_E_VIRGULA
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN PONTO_E_VIRGULA
    ;

definicao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN bloco_comandos
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN bloco_comandos
    | PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos
    | tipo PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos
    ;

lista_parametros
    : parametro
    | lista_parametros VIRGULA parametro
    ;

parametro
    : tipo IDENTIFICADOR
    | tipo IDENTIFICADOR ABRE_COLCHETE FECHA_COLCHETE
    ;
```

### Declarações de Estruturas

```
declaracao_estrutura
    : ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA
    ;

lista_campos
    : declaracao_campo
    | lista_campos declaracao_campo
    ;

declaracao_campo
    : tipo IDENTIFICADOR PONTO_E_VIRGULA
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA
    ;
```

### Comandos

```
bloco_comandos
    : ABRE_CHAVE FECHA_CHAVE
    | ABRE_CHAVE lista_comandos FECHA_CHAVE
    ;

lista_comandos
    : comando
    | lista_comandos comando
    ;

comando
    : SE ABRE_PAREN expressao FECHA_PAREN comando
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando
    | ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando
    | PARA ABRE_PAREN expressao_opt PONTO_E_VIRGULA expressao_opt PONTO_E_VIRGULA expressao_opt FECHA_PAREN comando
    | FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA
    | bloco_comandos
    | expressao PONTO_E_VIRGULA
    | RETORNE expressao_opt PONTO_E_VIRGULA
    | CONTINUE PONTO_E_VIRGULA
    | QUEBRE PONTO_E_VIRGULA
    | declaracao_variavel
    | PONTO_E_VIRGULA
    ;

expressao_opt
    : /* vazio */
    | expressao
    ;
```

### Expressões

```
expressao
    : atribuicao
    ;

atribuicao
    : condicional
    | unario ATRIBUICAO atribuicao
    | unario MAIS_IGUAL atribuicao
    | unario MENOS_IGUAL atribuicao
    | unario VEZES_IGUAL atribuicao
    | unario DIVIDIDO_IGUAL atribuicao
    | unario MODULO_IGUAL atribuicao
    ;

condicional
    : logico_ou
    | logico_ou INTERROGACAO expressao DOIS_PONTOS condicional
    ;

logico_ou
    : logico_e
    | logico_ou OU_LOGICO logico_e
    ;

logico_e
    : ou
    | logico_e E_LOGICO ou
    ;

ou
    : xor
    | ou OU xor
    ;

xor
    : e
    | xor XOR e
    ;

e
    : igualdade
    | e E igualdade
    ;

igualdade
    : relacional
    | igualdade IGUAL relacional
    | igualdade DIFERENTE relacional
    ;

relacional
    : shift
    | relacional MENOR shift
    | relacional MAIOR shift
    | relacional MENOR_IGUAL shift
    | relacional MAIOR_IGUAL shift
    ;

shift
    : aditivo
    | shift SHIFT_ESQUERDA aditivo
    | shift SHIFT_DIREITA aditivo
    ;

aditivo
    : multiplicativo
    | aditivo MAIS multiplicativo
    | aditivo MENOS multiplicativo
    ;

multiplicativo
    : cast
    | multiplicativo VEZES cast
    | multiplicativo DIVIDIDO cast
    | multiplicativo MODULO cast
    ;

cast
    : unario
    | ABRE_PAREN tipo FECHA_PAREN cast
    ;

unario
    : postfix
    | INCREMENTO unario
    | DECREMENTO unario
    | MAIS unario
    | MENOS unario
    | NAO_LOGICO unario
    | NEGACAO unario
    | VEZES unario
    | E_COMERCIAL unario
    ;

postfix
    : primario
    | postfix ABRE_COLCHETE expressao FECHA_COLCHETE
    | postfix ABRE_PAREN FECHA_PAREN
    | postfix ABRE_PAREN lista_argumentos FECHA_PAREN
    | postfix PONTO IDENTIFICADOR
    | postfix SETA IDENTIFICADOR
    | postfix INCREMENTO
    | postfix DECREMENTO
    ;

primario
    : IDENTIFICADOR
    | NUMERO
    | NUMERO_REAL
    | LITERAL_CHAR
    | LITERAL_STRING
    | ABRE_PAREN expressao FECHA_PAREN
    ;

lista_argumentos
    : atribuicao
    | lista_argumentos VIRGULA atribuicao
    ;
```

## Exemplos de Derivações

### Exemplo 1: Programa Simples

```c
inteiro principal() {
    retorne 0;
}
```

Derivação:
```
programa
-> declaracoes
-> declaracao
-> definicao_funcao
-> tipo PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE lista_comandos FECHA_CHAVE
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE comando FECHA_CHAVE
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE RETORNE expressao_opt PONTO_E_VIRGULA FECHA_CHAVE
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE RETORNE expressao PONTO_E_VIRGULA FECHA_CHAVE
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE RETORNE atribuicao PONTO_E_VIRGULA FECHA_CHAVE
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE RETORNE condicional PONTO_E_VIRGULA FECHA_CHAVE
-> ...
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE RETORNE primario PONTO_E_VIRGULA FECHA_CHAVE
-> TIPO_INTEIRO PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE RETORNE NUMERO PONTO_E_VIRGULA FECHA_CHAVE
```

### Exemplo 2: Declaração de Estrutura

```c
estrutura Pessoa {
    caractere nome[50];
    inteiro idade;
    real altura;
};
```

Derivação:
```
programa
-> declaracoes
-> declaracao
-> declaracao_estrutura
-> ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA
-> ESTRUTURA IDENTIFICADOR ABRE_CHAVE declaracao_campo FECHA_CHAVE PONTO_E_VIRGULA
-> ESTRUTURA IDENTIFICADOR ABRE_CHAVE tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA FECHA_CHAVE PONTO_E_VIRGULA
-> ESTRUTURA IDENTIFICADOR ABRE_CHAVE TIPO_CARACTERE IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA FECHA_CHAVE PONTO_E_VIRGULA
-> ...
```

## Observações sobre a Gramática

1. A gramática suporta todas as construções básicas da linguagem C, traduzidas para português.
2. Foram adicionadas regras específicas para suportar a função principal (`principal`).
3. A gramática suporta declarações de estruturas com campos que podem ser arrays.
4. Foram adicionadas regras para suportar constantes e variáveis estáticas.
5. A gramática suporta o operador de módulo (%) em expressões.

## Extensões Futuras

Possíveis extensões para a gramática incluem:

1. Suporte para enumerações (`enum`)
2. Suporte para definições de tipos (`typedef`)
3. Suporte para diretivas de pré-processador
4. Suporte para operadores bit a bit
5. Suporte para inicializadores de arrays e estruturas
