%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/tokens/tokens.h"

// Variável compartilhada com o Bison
extern YYSTYPE yylval;

// Contador de linha para mensagens de erro
int line_number = 1;
%}

%option noyywrap
%option yylineno

/* Padrões básicos necessários para laços */
DIGITO       [0-9]
LETRA        [a-zA-Z]
ID           {LETRA}({LETRA}|{DIGITO})*
NUMERO       {DIGITO}+
ESPACO       [ \t\r]
QUEBRA_LINHA \n

%%

/* Ignorar espaços e quebras de linha */
{ESPACO}      { /* Ignora espaços em branco */ }
{QUEBRA_LINHA} { line_number++; }

/* Operadores Matemáticos */
"+"             { return OP_MAIS; }
"-"             { return OP_MENOS; }
"*"             { return OP_VEZES; }
"/"             { return OP_DIVIDIDO; }
"%"             { return OP_MODULO; }

/* Operadores Relacionais */
"<"             { return OP_MENOR; }
"<="            { return OP_MENOR_IGUAL; }
">"             { return OP_MAIOR; }
">="            { return OP_MAIOR_IGUAL; }
"=="            { return OP_IGUAL; }
"!="            { return OP_DIFERENTE; }

/* Operadores Lógicos */
"&&"            { return OP_E_LOGICO; }
"||"            { return OP_OU_LOGICO; }
"!"             { return OP_NAO; }

/* Operadores de Atribuição */
"="             { return OP_ATRIBUIR; }
"+="            { return OP_ATRIBUIR_MAIS; }
"-="            { return OP_ATRIBUIR_MENOS; }
"*="            { return OP_ATRIBUIR_VEZES; }
"/="            { return OP_ATRIBUIR_DIVIDIDO; }

/* Identificadores e números */
{ID}            { 
    yylval.string = strdup(yytext); 
    return IDENTIFICADOR; 
}
{NUMERO}        { 
    yylval.integer = atoi(yytext); 
    return NUMERO; 
}

/* Tratamento de erros */
.                { 
    printf("Erro léxico na linha %d: caractere não reconhecido '%s'\n", 
           line_number, yytext);
}

%%

/* Função auxiliar para inicializar o analisador léxico */
void init_lexer() {
    line_number = 1;
}
