%{
#include <stdio.h>
#include <stdlib.h>
#include "tokens_switch.h"

extern int yylex();
void yyerror(const char* s);
%}

/* Tokens do scanner */
%token C_SWITCH C_CASE C_DEFAULT C_BREAK
%token C_LBRACE C_RBRACE C_LPAREN C_RPAREN
%token C_COLON C_SEMICOLON
%token C_IDENTIFIER C_NUMBER

%%

programa:
    comando_switch
    ;

comando_switch:
    C_SWITCH C_LPAREN expressao C_RPAREN C_LBRACE lista_casos C_RBRACE
    ;

lista_casos:
    lista_casos caso
    |
    caso
    ;

caso:
    C_CASE expressao C_COLON lista_comandos
    |
    C_DEFAULT C_COLON lista_comandos
    ;

lista_comandos:
    lista_comandos comando
    |
    comando
    ;

comando:
    C_BREAK C_SEMICOLON
    |
    /* pode colocar mais comandos aqui no futuro */
    ;

expressao:
    C_IDENTIFIER
    |
    C_NUMBER
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}