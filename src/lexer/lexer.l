%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens/tokens.h"

/* Variável definida por Bison */
extern YYSTYPE yylval;
%}

/* Opções do Flex */
%option noyywrap
%option nounput
%option noinput

%%

[ \t\n]         { /* Ignora espaços em branco e quebras de linha */ }
[0-9]+          { 
                    yylval.ival = atoi(yytext); 
                    return NUMERO; 
                }
"+"             { return SOMA; }
"-"             { return SUBTRACAO; }
"*"             { return MULTIPLICACAO; }
"/"             { return DIVISAO; }
"="             { return IGUAL; }
"("             { return ABRE_PAREN; }
")"             { return FECHA_PAREN; }
.               { 
                    fprintf(stderr, "Caractere não reconhecido: %s\n", yytext); 
                    return -1;
                }

%%
