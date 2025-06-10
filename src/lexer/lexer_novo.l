%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"
#include "../parser.tab.h"

extern YYSTYPE yylval;
int linha_atual = 1;
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
INTEIRO     {DIGITO}+
REAL        {DIGITO}+"."{DIGITO}+
ESPACO      [ \t\r]
NOVA_LINHA  \n

%%

{ESPACO}                { /* ignorar espaços */ }
{NOVA_LINHA}            { /* ignorar quebras de linha */ }
"//".*                  { /* comentário de linha */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* comentário de bloco */ }

"int"                   { yylval.sval = strdup("inteiro"); return TIPO_INTEIRO; }
"float"                 { yylval.sval = strdup("real"); return TIPO_REAL; }
"double"                { yylval.sval = strdup("duplo"); return TIPO_DUPLO; }
"char"                  { yylval.sval = strdup("caractere"); return TIPO_CARACTERE; }
"void"                  { yylval.sval = strdup("vazio"); return TIPO_VAZIO; }

"if"                    { return SE; }
"else"                  { return SENAO; }
"while"                 { return ENQUANTO; }
"for"                   { return PARA; }
"do"                    { return FACA; }
"return"                { return RETORNE; }
"break"                 { return QUEBRA; }
"continue"              { return CONTINUE; }
"switch"                { return ESCOLHA; }
"case"                  { return CASO; }
"default"               { return PADRAO; }

"struct"                { yylval.sval = strdup("estrutura"); return ESTRUTURA; }
"union"                 { yylval.sval = strdup("uniao"); return UNIAO; }
"enum"                  { yylval.sval = strdup("enumeracao"); return ENUM; }

"main"                  { yylval.sval = strdup("principal"); return PRINCIPAL; }

"=="                    { return IGUAL_IGUAL; }
"!="                    { return DIFERENTE; }
"<="                    { return MENOR_IGUAL; }
">="                    { return MAIOR_IGUAL; }
"<"                     { return MENOR; }
">"                     { return MAIOR; }
"&&"                    { return E_LOGICO; }
"||"                    { return OU_LOGICO; }
"!"                     { return NAO_LOGICO; }

"++"                    { return INCREMENTO; }
"--"                    { return DECREMENTO; }
"+="                    { return MAIS_IGUAL; }
"-="                    { return MENOS_IGUAL; }
"*="                    { return MULT_IGUAL; }
"/="                    { return DIV_IGUAL; }

"+"                     { return SOMA; }
"-"                     { return SUBTRACAO; }
"*"                     { return MULTIPLICACAO; }
"/"                     { return DIVISAO; }
"%"                     { return MODULO; }
"="                     { return IGUAL; }

"("                     { return ABRE_PAREN; }
")"                     { return FECHA_PAREN; }
"{"                     { return ABRE_CHAVE; }
"}"                     { return FECHA_CHAVE; }
"["                     { return ABRE_COLCHETE; }
"]"                     { return FECHA_COLCHETE; }
";"                     { return PONTO_E_VIRGULA; }
","                     { return VIRGULA; }
"."                     { return PONTO; }
":"                     { return DOIS_PONTOS; }

{INTEIRO}               { yylval.ival = atoi(yytext); return NUMERO; }
{REAL}                  { yylval.fval = atof(yytext); return NUMERO_REAL; }

\"[^\"\n]*\"            { yylval.sval = strdup(yytext); return LITERAL_STRING; }
\"[^\"\n]*$             { 
                            fprintf(stderr, "Erro: string não fechada na linha %d\n", yylineno); 
                            return -1; 
                        }

'[^'\n]'|'\\[nrtbf0\\\']' { yylval.sval = strdup(yytext); return LITERAL_CHAR; }
'[^'\n]*$               { 
                            fprintf(stderr, "Erro: caractere não fechado na linha %d\n", yylineno); 
                            return -1; 
                        }

{ID}                    { yylval.sval = strdup(yytext); return IDENTIFICADOR; }

.                       { 
                            fprintf(stderr, "Erro léxico: caractere inválido '%s' na linha %d\n", 
                                    yytext, yylineno); 
                            return -1; 
                        }

%%
