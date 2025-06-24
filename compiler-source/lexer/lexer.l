%{
/* * Analisador Léxico (Lexer) para um subconjunto da linguagem C.
 * Este arquivo define as "palavras" ou "tokens" que o parser irá usar.
 */
#include "y.tab.h" 
#include "ast.h"
#include <string.h>

// Função para retornar strings, evitando warnings
char* dupstr(const char* s) {
    char* ret = strdup(s);
    if (!ret) {
        perror("strdup");
        exit(1);
    }
    return ret;
}
%}

/* Definições para evitar warnings de 'flex' não utilizado */
%option noyywrap nounput noinput
/* Habilita o Flex a contar o número de linhas */
%option yylineno

/* Definições de padrões para facilitar a leitura */
DIGITO              [0-9]
LETRA               [a-zA-Z_]
IDENTIFICADOR       {LETRA}({LETRA}|{DIGITO})*
NUMERO_INTEIRO      {DIGITO}+
NUMERO_REAL         {DIGITO}+\.{DIGITO}+
TEXTO               \"(\\.|[^"\\])*\"
CARACTERE           \'(.|\\.)\'

%%

"//".* ; /* Ignora comentários de uma linha */
"/*"([^*]|"*"+[^*/])*"*"+"/" ; /* Ignora comentários de múltiplas linhas */
[ \t\n\r]+          ; /* Ignora espaços em branco, tabs e novas linhas */

^#.* ; /* Ignora linhas de pré-processador (ex: #include, #define) */

 /* --- Palavras-chave --- */
"if"                { return T_IF; }
"else"              { return T_ELSE; }
"while"             { return T_WHILE; }
"for"               { return T_FOR; }
"return"            { return T_RETURN; }
"printf"            { return T_PRINTF; }
"scanf"             { return T_SCANF; }

 /* --- NOVAS Palavras-chave --- */
"switch"            { return T_SWITCH; }
"case"              { return T_CASE; }
"default"           { return T_DEFAULT; }
"break"             { return T_BREAK; }
"continue"          { return T_CONTINUE; }
"do"                { return T_DO; }

 /* --- Tipos de Dados --- */
"int"               { return T_INT; }
"float"             { return T_FLOAT; }
"char"              { return T_CHAR; }
"void"              { return T_VOID; }
"const"             { return T_CONST; }
"unsigned"          { return T_UNSIGNED; }

 /* --- Identificadores e Literais --- */
{IDENTIFICADOR}     { yylval.sval = dupstr(yytext); return T_ID; }
{NUMERO_INTEIRO}    { yylval.ival = atoi(yytext); return T_NUMBER_INT; }
{NUMERO_REAL}       { yylval.sval = dupstr(yytext); return T_NUMBER_FLOAT; }
{TEXTO}             { yylval.sval = dupstr(yytext); return T_STRING; }
{CARACTERE}         { yylval.sval = dupstr(yytext); return T_CHAR_LITERAL; }

 /* --- Operadores --- */
"++"                { return T_INC; }
"--"                { return T_DEC; }
"+="                { return T_PLUS_ASSIGN; }
"-="                { return T_MINUS_ASSIGN; }
"->"                { return T_ARROW; }
"+"                 { return T_PLUS; }
"-"                 { return T_MINUS; }
"*"                 { return T_MULT; }
"/"                 { return T_DIV; }
"%"                 { return T_MOD; }
"=="                { return T_EQ; }
"!="                { return T_NEQ; }
"<="                { return T_LE; }
">="                { return T_GE; }
"<"                 { return T_LT; }
">"                 { return T_GT; }
"&&"                { return T_AND; }
"||"                { return T_OR; }
"&"                 { return T_AMPERSAND; }
"|"                 { return T_BIT_OR; }
"!"                 { return T_NOT; }
"="                 { return T_ASSIGN; }


 /* --- Pontuação e Símbolos --- */
"{"                 { return T_LBRACE; }
"}"                 { return T_RBRACE; }
"("                 { return T_LPAREN; }
")"                 { return T_RPAREN; }
";"                 { return T_SEMICOLON; }
","                 { return T_COMMA; }
"."                 { return T_DOT; }
":"                 { return T_COLON; }


 /* Captura strings que abriram mas não foram terminadas */
\"([^\"\\]|\\.)*$    { fprintf(stderr, "Erro lexico na linha %d: string não terminada\n", yylineno); exit(1); }

 /* Mensagem de erro léxico genérico com indicação de linha */
.                   { fprintf(stderr, "Erro lexico na linha %d: Caractere inesperado '%s'\n", yylineno, yytext); exit(1); }

%%
