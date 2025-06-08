%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"
#include "../parser.tab.h"
/* Variável definida pelo Bison */
extern YYSTYPE yylval;

/* Para mensagens de erro opcionais */
int erro_lexico = 0;
char mensagem_erro[256];
%}

/* ---------- Opções do Flex ---------- */
%option noyywrap
%option nounput
%option noinput
%option yylineno

/* ---------- Definições regulares ---------- */
DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
INTEIRO     {DIGITO}+
REAL        {DIGITO}+"."{DIGITO}+
ESPACO      [ \t\n\r]

%%

 /* -------- Espaços e comentários -------- */
{ESPACO}                { /* ignorar */ }
"//".*                  { /* comentário de linha */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* comentário de bloco */ }

 /* -------- Literais numéricos e textuais -------- */
{INTEIRO}               { yylval.ival = atoi(yytext);  return NUMERO; }
{REAL}                  { yylval.fval = atof(yytext);  return NUMERO; }

\"[^\"\n]*\"            { yylval.sval = strdup(yytext); return LITERAL_STRING; }
\"[^\"\n]*$             {
                            fprintf(stderr,
                                    "Erro léxico (linha %d): string não fechada \"%s\".\n",
                                    yylineno, yytext); return -1;
                        }

'[^'\n]'|'\\[nrtbf0\\\']' {
                            yylval.sval = strdup(yytext);
                            return LITERAL_CHAR;
                        }
'[^'\n]*$               {
                            fprintf(stderr,
                                    "Erro léxico (linha %d): caractere não fechado '%s'.\n",
                                    yylineno, yytext); return -1;
                        }

 /* -------- Palavras-chave: tipos e qualificadores -------- */
"int"                   { return TIPO_INTEIRO; }
"float"                 { return TIPO_REAL; }
"double"                { return TIPO_DUPLO; }
"char"                  { return TIPO_CARACTERE; }
"void"                  { return TIPO_VAZIO; }
"long"                  { return TIPO_LONGO; }
"short"                 { return TIPO_CURTO; }
"unsigned"              { return TIPO_SEM_SINAL; }
"signed"                { return TIPO_COM_SINAL; }

"typedef"               { return TYPEDEF; }
"auto"                  { return AUTO; }
"register"              { return REGISTRO; }
"static"                { return ESTATICO; }
"extern"                { return EXTERNO; }
"inline"                { return INLINE; }
"volatile"              { return VOLATIL; }
"restrict"              { return RESTRICT; }


 /* -------- Palavras-chave: controle de fluxo -------- */
"if"                    { return SE; }
"else"                  { return SENAO; }
"while"                 { return ENQUANTO; }
"for"                   { return PARA; }
"do"                    { return FACA; }
"switch"                { return ESCOLHA; }
"case"                  { return CASO; }
"default"               { return PADRAO; }
"break"                 { return QUEBRA; }
"continue"              { return CONTINUE; }
"return"                { return RETORNE; }
"goto"                  { return GOTO; }

 /* -------- Estruturas de dados -------- */
"struct"                { return ESTRUTURA; }
"union"                 { return UNIAO; }
"enum"                  { return ENUM; }
"const"                 { return CONST; }

 /* -------- Operadores compostos (+=, <<=, etc.) -------- */
"+="                    { return MAIS_IGUAL; }
"-="                    { return MENOS_IGUAL; }
"*="                    { return MULT_IGUAL; }
"/="                    { return DIV_IGUAL; }
"%="                    { return MOD_IGUAL; }
"&="                    { return E_BIT_IGUAL; }
"|="                    { return OU_BIT_IGUAL; }
"^="                    { return XOR_IGUAL; }
"<<="                   { return SHIFT_ESQ_IGUAL; }
">>="                   { return SHIFT_DIR_IGUAL; }

 /* -------- Operadores de incremento/decremento -------- */
"++"                    { return INCREMENTO; }
"--"                    { return DECREMENTO; }

 /* -------- Operadores relacionais e lógicos -------- */
"=="                    { return IGUAL_IGUAL; }
"!="                    { return DIFERENTE; }
"<="                    { return MENOR_IGUAL; }
">="                    { return MAIOR_IGUAL; }
"<"                     { return MENOR; }
">"                     { return MAIOR; }
"&&"                    { return E_LOGICO; }
"||"                    { return OU_LOGICO; }
"!"                     { return NAO_LOGICO; }

 /* -------- Operadores aritméticos e bit-a-bit -------- */
"<<"                    { return SHIFT_ESQ; }
">>"                    { return SHIFT_DIR; }
"&"                     { return E_BIT; }
"|"                     { return OU_BIT; }
"^"                     { return XOR; }
"~"                     { return COMPLEMENTO; }
"+"                     { return SOMA; }
"-"                     { return SUBTRACAO; }
"*"                     { return MULTIPLICACAO; }
"/"                     { return DIVISAO; }
"%"                     { return MODULO; }
"->"                    { return SETA; }
"."                     { return PONTO; }
"sizeof"                { return SIZEOF; }
"?"                     { return INTERROGACAO; }
":"                     { return DOIS_PONTOS; }
"..."                   { return RETICENCIAS; }

 /* -------- Atribuição simples e parênteses/colchetes -------- */
"="                     { return IGUAL; }
"("                     { return ABRE_PAREN; }
")"                     { return FECHA_PAREN; }
"{"                     { return ABRE_CHAVE; }
"}"                     { return FECHA_CHAVE; }
"["                     { return ABRE_COLCHETE; }
"]"                     { return FECHA_COLCHETE; }
";"                     { return PONTO_E_VIRGULA; }
","                     { return VIRGULA; }

 /* -------- ponto de entrada customizado (opcional) -------- */
"principal"             { return PRINCIPAL; }

 /* -------- Identificadores -------- */
{ID}                    { yylval.sval = strdup(yytext); return IDENTIFICADOR; }

 /* -------- Erro genérico -------- */
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

