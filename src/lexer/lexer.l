%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"
#include "../parser.tab.h"

/* Variável definida por Bison */
extern YYSTYPE yylval;

/* Variáveis para tratamento de erros */
int erro_lexico = 0;
char mensagem_erro[256];
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

\"[^\"\n]*\"    {
                    yylval.sval = strdup(yytext);
                    return LITERAL_STRING;
                }

\"[^\"\n]*$     {
                    fprintf(stderr, "Erro léxico (linha %d): String não fechada '%s'. Falta aspas duplas de fechamento.\n", yylineno, yytext);
                    return -1;
                }

'[^'\n]'|'\\[nrtbf0\\\']' {
                    yylval.sval = strdup(yytext);
                    return LITERAL_CHAR;
                }

'[^'\n]*$       {
                    fprintf(stderr, "Erro léxico (linha %d): Caractere não fechado '%s'. Falta aspas simples de fechamento.\n", yylineno, yytext);
                    return -1;
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
                    if (yytext[0] == '@' || yytext[0] == '#' || yytext[0] == '$') {
                        fprintf(stderr, "Erro léxico (linha %d): Símbolo especial '%s' não permitido. A linguagem não suporta estes caracteres.\n", yylineno, yytext);
                    } else if (yytext[0] == '\\' && yytext[1] != '0' && yytext[1] != 'n' && yytext[1] != 't' && yytext[1] != 'r') {
                        fprintf(stderr, "Erro léxico (linha %d): Sequência de escape inválida '%s'. Sequências válidas: \\n, \\t, \\r, \\0.\n", yylineno, yytext);
                    } else if (yytext[0] == '"' || yytext[0] == '\'') {
                        fprintf(stderr, "Erro léxico (linha %d): Aspas não fechadas ou mal formadas em '%s'. Verifique se todas as aspas estão balanceadas.\n", yylineno, yytext);
                    } else {
                        fprintf(stderr, "Erro léxico (linha %d): Caractere não reconhecido '%s'. Verifique se há símbolos inválidos no seu código.\n", yylineno, yytext);
                    }
                    return -1;
                }

%%
