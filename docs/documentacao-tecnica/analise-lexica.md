
# Análise Léxica

Esta seção documenta o funcionamento do analisador léxico (`lexer.l`), desenvolvido com Flex. O lexer é responsável por transformar a entrada textual do programa (em C) em uma sequência de **tokens** que serão processados pelo parser Bison.

---

## Objetivo

O analisador léxico atua como a primeira etapa do processo de compilação. Seu objetivo é:

- Eliminar elementos irrelevantes como espaços e comentários
- Identificar **tokens válidos** (palavras-chave, identificadores, operadores, literais)
- Realizar atribuições iniciais de valores semânticos à variável `yylval`
- Encaminhar os tokens corretamente para o parser

---

## Organização do Arquivo `lexer.l`

O arquivo é dividido em **três seções** principais, conforme a estrutura padrão do Flex.

---

### 1. **Cabeçalhos e Código C (`%{ ... %}`)**

Nesta parte são incluídas bibliotecas e funções auxiliares utilizadas nas ações léxicas:

```c
#include "y.tab.h"
#include "ast.h"
#include <string.h>
```

A função auxiliar `dupstr()` é definida para duplicar strings de forma segura:

```c
char* dupstr(const char* s) {
    char* ret = strdup(s);
    if (!ret) {
        perror("strdup");
        exit(1);
    }
    return ret;
}
```

---

### 2. **Opções e Definições (`%option` e macros)**

As diretivas do Flex configuram o comportamento do lexer:

```c
%option noyywrap nounput noinput
%option yylineno
```

- `noyywrap`: evita necessidade de função `yywrap()`
- `nounput` e `noinput`: desabilitam funções não usadas
- `yylineno`: ativa a contagem automática de linhas

Além disso, definem-se expressões regulares reutilizáveis:

```c
DIGITO              [0-9]
LETRA               [a-zA-Z_]
IDENTIFICADOR       {LETRA}({LETRA}|{DIGITO})*
NUMERO_INTEIRO      {DIGITO}+
NUMERO_REAL         {DIGITO}+\.{DIGITO}+
TEXTO               \"(\\.|[^"\\])\*\"
CARACTERE           \'(.|\\.)\'
```

---

### 3. **Regras Léxicas (corpo entre `%%`)**

A terceira seção contém as regras de tokenização. Cada linha tem a forma:

```
Padrão    { Ação a executar }
```

#### Ignorados:

```c
"//".*                             ; // Comentários de linha
"/*"([^*]|"*"+[^*/])*"*"+"/"      ; // Comentários de bloco
[ 	

]+                        ; // Espaços e quebras de linha
^#.*                              ; // Diretivas como #include
```

#### Palavras-chave:

```c
"if"       { return T_IF; }
"else"     { return T_ELSE; }
"while"    { return T_WHILE; }
"return"   { return T_RETURN; }
"printf"   { return T_PRINTF; }
"scanf"    { return T_SCANF; }
```

#### Literais:

```c
{NUMERO_INTEIRO}  { yylval.ival = atoi(yytext); return T_INT; }
{NUMERO_REAL}     { yylval.rval = atof(yytext); return T_FLOAT; }
{TEXTO}           { yylval.str = dupstr(yytext); return T_STRING; }
{CARACTERE}       { yylval.cval = yytext[1]; return T_CHAR; }
```

#### Identificadores:

```c
{IDENTIFICADOR}   { yylval.str = dupstr(yytext); return T_ID; }
```

#### Operadores e Delimitadores:

```c
"="      { return T_EQ; }
"=="     { return T_EQEQ; }
"+"      { return T_PLUS; }
"-"      { return T_MINUS; }
"*"      { return T_TIMES; }
"/"      { return T_DIVIDE; }
"("      { return T_LPAREN; }
")"      { return T_RPAREN; }
"{"      { return T_LBRACE; }
"}"      { return T_RBRACE; }
";"      { return T_SEMICOLON; }
","      { return T_COMMA; }
```

---

## Tratamento de Erros

O lexer ignora comentários malformados ou espaços inválidos, mas pode ser estendido para exibir mensagens de erro personalizadas com base em `yytext` e `yylineno`.

---

## Tokens e `yylval`

Cada token identificado pode atribuir um valor à `yylval`, que será utilizado na análise sintática. Exemplo:

```c
yylval.ival = atoi(yytext); // para inteiros
yylval.str = dupstr(yytext); // para strings e identificadores
```

---

## Exemplo de Entrada e Saída

**Entrada:**

```c
int main() {
    float pi = 3.14;
    return 0;
}
```

**Tokens gerados:**

- `T_INT` (`int`)
- `T_ID` (`main`)
- `T_LPAREN`, `T_RPAREN`, `T_LBRACE`
- `T_FLOAT` (`float`)
- `T_ID` (`pi`)
- `T_EQ`, `T_REAL_LITERAL` (`3.14`)
- `T_SEMICOLON`
- `T_RETURN`, `T_INT_LITERAL` (`0`)
- `T_SEMICOLON`, `T_RBRACE`

---

## Integração com o Parser

A função `yylex()` é chamada automaticamente pelo Bison para buscar o próximo token. O arquivo `parser.y` define os tokens esperados com `%token`, garantindo compatibilidade entre lexer e parser.

---