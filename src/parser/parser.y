%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"

extern int yylex();
extern char* yytext;
extern FILE* yyin;

/* Declaração da função yyerror, que será definida em main.c */
void yyerror(const char* s);

/* Raiz da AST */
AstNode* ast_root = NULL;
%}

/* Definição dos tokens */
%token NUMERO SOMA SUBTRACAO MULTIPLICACAO DIVISAO IGUAL ABRE_PAREN FECHA_PAREN

/* Precedência e associatividade dos operadores */
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO
%left ABRE_PAREN FECHA_PAREN

/* Tipo dos valores semânticos */
%code requires {
    #include "ast/ast.h"
}

%union {
    int ival;
    AstNode* node;
}

/* Tipo de cada símbolo gramatical */
%type <ival> NUMERO
%type <node> expressao termo fator igualdade programa

%%

programa
    : igualdade             { 
                              ast_root = $1; 
                              printf("Resultado: %d\n", evaluate_ast(ast_root));
                              free_ast(ast_root);
                            }
    ;

igualdade
    : expressao IGUAL expressao   { $$ = create_equal_node($1, $3); }
    | expressao                   { $$ = $1; }
    ;

expressao
    : expressao SOMA termo       { $$ = create_binop_node(OP_ADD, $1, $3); }
    | expressao SUBTRACAO termo  { $$ = create_binop_node(OP_SUB, $1, $3); }
    | termo                      { $$ = $1; }
    ;

termo
    : termo MULTIPLICACAO fator  { $$ = create_binop_node(OP_MUL, $1, $3); }
    | termo DIVISAO fator        { $$ = create_binop_node(OP_DIV, $1, $3); }
    | fator                      { $$ = $1; }
    ;

fator
    : NUMERO                     { $$ = create_literal_node($1); }
    | ABRE_PAREN expressao FECHA_PAREN { $$ = $2; }
    ;

%%

/* Esta função será implementada em main.c */
/* int main() {
    return yyparse();
} */
