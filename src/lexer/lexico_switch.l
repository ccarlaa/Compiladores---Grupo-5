%{
#include "tokens_switch.h"
#include <string.h>

/* Variável definida por Bison */
extern YYSTYPE yylval;
%}

/* Definições de padrões */
ID      [a-zA-Z_][a-zA-Z0-9_]*
NUM     [0-9]+

%%

 /* Ignora espaços em branco e quebras de linha */
[ \t\n]

 /* Palavras-chave */
"switch"      { return C_SWITCH; }
"case"        { return C_CASE; }
"default"     { return C_DEFAULT; }
"break"       { return C_BREAK; }

 /* Símbolos */
"{"           { return C_LBRACE; }
"}"           { return C_RBRACE; }
"("           { return C_LPAREN; }
")"           { return C_RPAREN; }
":"           { return C_COLON; }
";"           { return C_SEMICOLON; }

 /* Identificadores */
{ID}          { 
                 yylval.string = strdup(yytext);
                 return C_IDENTIFIER; 
              }

 /* Números */
{NUM}         { 
                 yylval.integer = atoi(yytext);
                 return C_NUMBER; 
              }

 /* erro */
.               { 
                    fprintf(stderr, "Caractere não reconhecido: %s\n", yytext); 
                    return -1;
                }

%%