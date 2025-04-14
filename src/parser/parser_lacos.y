%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "../../include/ast/ast.h"
    #include "../../include/tokens/tokens.h"

    extern int yylex(void);
    void yyerror(const char *s);
%}

/* Tokens para laços de repetição */
%token C_WHILE C_FOR C_DO C_UNTIL C_REPEAT C_FOREACH C_IN C_FROM C_STEP
%token C_MAP C_FILTER C_REDUCE C_FOLD C_APPLY C_FORALL C_EXISTS C_FIND C_COUNT
%token C_GROUP C_SORT C_REVERSE C_JOIN C_SPLIT
%token C_AWAIT C_PARALLEL C_CONCURRENT C_SEQUENTIAL
%token C_LPAREN C_RPAREN C_LBRACE C_RBRACE C_SEMICOLON
%token C_IDENTIFIER C_NUMBER

/* Tipo dos valores semânticos */
%union {
    int integer;
    char* string;
    AstNode* node;
}

/* Tipo de cada símbolo gramatical */
%type <integer> C_NUMBER
%type <string> C_IDENTIFIER
%type <node> programa bloco comando laco expressao

%%

programa:
    bloco                    { $$ = $1; }
    ;

bloco:
    C_LBRACE comando C_RBRACE  { $$ = $2; }
    | C_LBRACE C_RBRACE        { $$ = NULL; }
    ;

comando:
    laco                     { $$ = $1; }
    | expressao C_SEMICOLON   { $$ = $1; }
    | comando comando        { $$ = create_sequence_node($1, $2); }
    ;

laco:
    /* Laços tradicionais */
    C_WHILE C_LPAREN expressao C_RPAREN bloco
        { $$ = create_while_node($3, $5); }
    
    | C_FOR C_LPAREN expressao C_SEMICOLON expressao C_SEMICOLON expressao C_RPAREN bloco
        { $$ = create_for_node($3, $5, $7, $9); }
    
    | C_DO bloco C_WHILE C_LPAREN expressao C_RPAREN
        { $$ = create_do_while_node($2, $5); }
    
    | C_REPEAT bloco C_UNTIL C_LPAREN expressao C_RPAREN
        { $$ = create_repeat_until_node($2, $5); }
    
    | C_FOREACH C_LPAREN C_IDENTIFIER C_IN expressao C_RPAREN bloco
        { $$ = create_foreach_node($3, $5, $7); }

    /* Laços funcionais */
    | C_MAP C_LPAREN expressao C_RPAREN bloco
        { $$ = create_map_node($3, $5); }
    
    | C_FILTER C_LPAREN expressao C_RPAREN bloco
        { $$ = create_filter_node($3, $5); }
    
    | C_REDUCE C_LPAREN expressao C_RPAREN bloco
        { $$ = create_reduce_node($3, $5); }
    
    | C_FOLD C_LPAREN expressao C_RPAREN bloco
        { $$ = create_fold_node($3, $5); }
    
    | C_APPLY C_LPAREN expressao C_RPAREN bloco
        { $$ = create_apply_node($3, $5); }
    
    | C_FORALL C_LPAREN expressao C_RPAREN bloco
        { $$ = create_forall_node($3, $5); }
    
    | C_EXISTS C_LPAREN expressao C_RPAREN bloco
        { $$ = create_exists_node($3, $5); }
    
    | C_FIND C_LPAREN expressao C_RPAREN bloco
        { $$ = create_find_node($3, $5); }
    
    | C_COUNT C_LPAREN expressao C_RPAREN bloco
        { $$ = create_count_node($3, $5); }
    
    | C_GROUP C_LPAREN expressao C_RPAREN bloco
        { $$ = create_group_node($3, $5); }
    
    | C_SORT C_LPAREN expressao C_RPAREN bloco
        { $$ = create_sort_node($3, $5); }
    
    | C_REVERSE C_LPAREN expressao C_RPAREN bloco
        { $$ = create_reverse_node($3, $5); }
    
    | C_JOIN C_LPAREN expressao C_RPAREN bloco
        { $$ = create_join_node($3, $5); }
    
    | C_SPLIT C_LPAREN expressao C_RPAREN bloco
        { $$ = create_split_node($3, $5); }

    /* Laços assíncronos */
    | C_AWAIT C_LPAREN expressao C_RPAREN bloco
        { $$ = create_await_node($3, $5); }
    
    | C_PARALLEL bloco
        { $$ = create_parallel_node($2); }
    
    | C_CONCURRENT bloco
        { $$ = create_concurrent_node($2); }
    
    | C_SEQUENTIAL bloco
        { $$ = create_sequential_node($2); }
    ;

expressao:
    C_NUMBER                 { $$ = create_literal_node($1); }
    | C_IDENTIFIER          { $$ = create_identifier_node($1); }
    | C_LPAREN expressao C_RPAREN { $$ = $2; }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}