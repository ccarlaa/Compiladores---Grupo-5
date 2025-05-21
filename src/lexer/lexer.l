%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../../include/tokens/tokens.h"
#include "ast/ast.h"
#include "parser.tab.h"

/* Variável definida por Bison */
extern YYSTYPE yylval;
%}

/* Opções do Flex */
%option noyywrap
%option nounput
%option noinput
%option yylineno

/* Definições regulares */
DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
INTEIRO     {DIGITO}+
REAL        {DIGITO}+"."{DIGITO}+
ESPACO      [ \t\n\r]

%%

{ESPACO}        { /* Ignora espaços em branco e quebras de linha */ }

"//".*          { /* Ignora comentários de linha */ }

"/*"([^*]|\*+[^*/])*\*+"/" { /* Ignora comentários de bloco */ }

{INTEIRO}       { 
                    yylval.ival = atoi(yytext); 
                    return NUMERO; 
                }

{REAL}          {
                    yylval.fval = atof(yytext);
                    return NUMERO; /* Por enquanto, tratamos como o mesmo token */
                }

\"[^\"]*\"      {
                    yylval.sval = strdup(yytext);
                    return LITERAL_STRING;
                }

\'[^\']\' |
\'([^\\']|\\[nrtbf0'\"\\])\' {
                    yylval.sval = strdup(yytext);
                    return LITERAL_CHAR;
                }

"int"           { return TIPO_INTEIRO; }
"float"         { return TIPO_REAL; }
"double"        { return TIPO_DUPLO; }
"char"          { return TIPO_CARACTERE; }
"void"          { return TIPO_VAZIO; }
"long"          { return TIPO_LONGO; }
"short"         { return TIPO_CURTO; }
"unsigned"      { return TIPO_SEM_SINAL; }
"signed"        { return TIPO_COM_SINAL; }

"if"            { return SE; }
"else"          { return SENAO; }
"while"         { return ENQUANTO; }
"for"           { return PARA; }
"do"            { return FACA; }
"return"        { return RETORNE; }
"break"         { return QUEBRA; }
"continue"      { return CONTINUE; }

"struct"        { return ESTRUTURA; }
"union"         { return UNIAO; }
"enum"          { return ENUM; }
"const"         { return CONST; }
"static"        { return ESTATICO; }
"extern"        { return EXTERNO; }
"register"      { return REGISTRO; }
"typedef"       { return TYPEDEF; }

"switch"        { return ESCOLHA; }
"case"          { return CASO; }
"default"       { return PADRAO; }

"+="            { return MAIS_IGUAL; }
"-="            { return MENOS_IGUAL; }
"*="            { return MULT_IGUAL; }
"/="            { return DIV_IGUAL; }
"++"            { return INCREMENTO; }
"--"            { return DECREMENTO; }

"=="            { return IGUAL_IGUAL; }
"!="            { return DIFERENTE; }
"<"             { return MENOR; }
">"             { return MAIOR; }
"<="            { return MENOR_IGUAL; }
">="            { return MAIOR_IGUAL; }
"&&"            { return E_LOGICO; }
"||"            { return OU_LOGICO; }
"!"             { return NAO_LOGICO; }

"+"             { return SOMA; }
"-"             { return SUBTRACAO; }
"*"             { return MULTIPLICACAO; }
"/"             { return DIVISAO; }
"%"             { return MODULO; }
"="             { return IGUAL; }
"("             { return ABRE_PAREN; }
")"             { return FECHA_PAREN; }

"{"             { return ABRE_CHAVE; }
"}"             { return FECHA_CHAVE; }
"["             { return ABRE_COLCHETE; }
"]"             { return FECHA_COLCHETE; }
";"             { return PONTO_E_VIRGULA; }
","             { return VIRGULA; }
"."             { return PONTO; }
":"             { return DOIS_PONTOS; }

"principal"     { return PRINCIPAL; }



{ID}            {
                    yylval.sval = strdup(yytext);
                    return IDENTIFICADOR;
                }

.               { 
                    fprintf(stderr, "Caractere não reconhecido: %s\n", yytext); 
                    return -1;
                }

%%
