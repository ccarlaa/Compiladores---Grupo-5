%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"
#include "ast.h"
#include "y.tab.h"

extern int yylineno;

void yyerror(const char *s);
int yylex(void);

ASTNode *ast_root = NULL;
int current_scope = 0;

// Funções auxiliares
ASTNode* create_declaration_node(char *type, char *name, ASTNode *init);
ASTNode* create_assignment_node(char *op, ASTNode *lhs, ASTNode *rhs);
ASTNode* create_binary_op(char *op, ASTNode *lhs, ASTNode *rhs);
ASTNode* create_unary_op(char *op, ASTNode *operand);

static ASTNode *func_node_temp = NULL;
static ASTNode *body_node_temp = NULL;
static ASTNode *if_node_temp = NULL;

%}

%code requires {
    #include "ast.h"
}

%union {
    char *sval;
    int ival;
    float fval;
    ASTNode *ast;
}

/* --- Tokens --- */
%token <sval> T_ID T_STRING T_CHAR_LITERAL T_NUMBER_FLOAT
%token <ival> T_NUMBER_INT

%token T_INT T_FLOAT T_CHAR T_VOID
%token T_IF T_ELSE T_WHILE T_FOR T_RETURN T_PRINTF T_SCANF
%token T_SWITCH T_CASE T_DEFAULT T_BREAK T_CONTINUE T_DO
%token T_MOD T_INC T_DEC T_PLUS_ASSIGN T_MINUS_ASSIGN
%token T_ARROW T_DOT T_AMPERSAND T_BIT_OR
%token T_PLUS T_MINUS T_MULT T_DIV
%token T_ASSIGN T_EQ T_NEQ T_LT T_GT T_LE T_GE
%token T_AND T_OR T_NOT
%token T_LPAREN T_RPAREN T_LBRACE T_RBRACE T_SEMICOLON T_COMMA T_COLON
%token T_CONST T_UNSIGNED

/* --- Precedência --- */
%right T_ASSIGN T_PLUS_ASSIGN T_MINUS_ASSIGN
%left T_OR
%left T_AND
%left T_BIT_OR
%left T_EQ T_NEQ
%left T_GT T_LT T_GE T_LE
%left T_PLUS T_MINUS
%left T_MULT T_DIV T_MOD
%right T_NOT T_INC T_DEC T_AMPERSAND
%left T_DOT T_ARROW
%left T_LPAREN T_RPAREN
%right '*'

/* --- Tipos AST --- */
%type <ast> function_list function_declaration declarations declaration function_parameter parameter_list
%type <ast> statements statement expression assignment_statement
%type <ast> if_statement while_statement return_statement scanf_statement printf_statement
%type <ast> do_while_statement for_statement break_statement continue_statement
%type <ast> increment_statement decrement_statement declaration_or_expression
%type <ast> block
%type <sval> type_specifier declarator direct_declarator pointer


%start program

%%

program:
    {
        init_symbol_table();
        ast_root = create_node(NODE_PROGRAM, "programa");
    }
    function_list
    {
        print_ast_stderr(ast_root, 0);  // Imprime a árvore AST no stderr
        generate_portugol(ast_root);    // Gera código Portugol
        free_ast(ast_root);
        print_symbol_table_stderr();    // Imprime a tabela de símbolos no stderr
        free_symbol_table();
    }
    ;

function_list:
    %empty 
    {
        $$ = create_node(NODE_EMPTY, NULL);
    }
    | function_list function_declaration
    {
        add_child(ast_root, $2);
        $$ = $1;
    }
    ;

function_declaration:
    type_specifier T_ID T_LPAREN function_parameter T_RPAREN T_LBRACE
    {
        // Inserir símbolo na tabela
        insert_symbol($2, $1, 0);
        
        // Criar nó da função
        ASTNode *func_node = create_node(NODE_FUNCTION, strdup($2));
        ASTNode *type_node = create_node(NODE_TYPE, strdup($1));
        ASTNode *param_list_node = $4; // Lista de parâmetros já criada
        ASTNode *body_node = create_node(NODE_BLOCK, NULL);

        add_child(func_node, type_node);
        add_child(func_node, param_list_node);
        add_child(func_node, body_node);
        
        // Armazenar em variáveis temporárias
        func_node_temp = func_node;
        body_node_temp = body_node;
    }
    declarations
    statements
    T_RBRACE
    {
        add_child(body_node_temp, $8);
        add_child(body_node_temp, $9);
        
        
        $$ = func_node_temp;
        
        func_node_temp = NULL;
        body_node_temp = NULL;
        
         free($1); free($2);
    }
    ;

function_parameter:
    %empty
    {
        $$ = create_node(NODE_PARAM_LIST, NULL);
    }
    | parameter_list
    {
        $$ = $1;
    }
    ;

parameter_list:
    type_specifier declarator
    {
        // Criar a lista de parâmetros
        ASTNode *param_list_node = create_node(NODE_PARAM_LIST, NULL);
        ASTNode *param_node = create_node(NODE_PARAMETER, strdup($2));
        ASTNode *type_node = create_node(NODE_TYPE, strdup($1));
        
        add_child(param_node, type_node);
        add_child(param_list_node, param_node);
        
        $$ = param_list_node;
        
        // free($1); free($2);
    }
    | parameter_list T_COMMA type_specifier declarator
    {
        ASTNode *param_node = create_node(NODE_PARAMETER, strdup($4));
        ASTNode *type_node = create_node(NODE_TYPE, strdup($3));
        
        add_child(param_node, type_node);
        add_child($1, param_node);
        
        $$ = $1;
        
        // free($3); free($4);
    }
    ;
declarations:
    %empty
    {
        $$ = create_node(NODE_DECLARATION_LIST, NULL);
    }
    | declarations declaration
    {
        ASTNode *decls = create_node(NODE_DECLARATION_LIST, NULL);
        add_child($1, $2);
        $$ = $1;
    }
    ;

declaration:
    type_specifier declarator T_SEMICOLON
    {
        $$ = create_declaration_node($1, $2, NULL);
        if (lookup_symbol($2) != NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' já declarada.", yylineno, $2);
            yyerror(msg);
        }
        insert_symbol($2, $1, current_scope);
        free($1); free($2);
    }
    | type_specifier declarator T_ASSIGN expression T_SEMICOLON
    {
        $$ = create_declaration_node($1, $2, $4);
        if (lookup_symbol($2) != NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' já declarada.", yylineno, $2);
            yyerror(msg);
        }
        insert_symbol($2, $1, current_scope);
        free($1); free($2);
    }
    ;

declarator:
    pointer direct_declarator
    {
        asprintf(&$$, "%s%s", $1, $2);
        free($1); free($2);
    }
    | direct_declarator
    {
        $$ = $1;
    }
    ;

pointer:
    '*'
    {
        $$ = strdup("*");
    }
    | '*' pointer
    {
        asprintf(&$$, "*%s", $2);
        free($2);
    }
    ;

direct_declarator:
    T_ID
    {
        $$ = $1;
    }
    ;

type_specifier:
    T_INT      { $$ = strdup("inteiro"); }
    | T_FLOAT    { $$ = strdup("real"); }
    | T_CHAR     { $$ = strdup("caracter"); }
    | T_VOID     { $$ = strdup("vazio"); }
    | T_CONST    { $$ = strdup("constante"); }
    | T_UNSIGNED { $$ = strdup("inteiro"); }
    ;

statements:
    %empty
    {
        $$ = create_node(NODE_STATEMENT_LIST, NULL);
    }
    | statements statement
    {
        add_child($1, $2);
        
        $$ = $1;
    }
    ;

statement:
    printf_statement
    | scanf_statement
    | declaration
    | if_statement
    | while_statement
    | do_while_statement

    | return_statement
    | assignment_statement
    | T_SEMICOLON { $$ = create_node(NODE_EMPTY, NULL); }
    ;

block:
    T_LBRACE statements T_RBRACE
    {
        $$ = $2;
    }
    ;

do_while_statement:
    T_DO T_LBRACE statements T_RBRACE T_WHILE T_LPAREN expression T_RPAREN T_SEMICOLON
    {
        ASTNode *do_while = create_node(NODE_DO_WHILE, NULL);
        add_child(do_while, $3); // Bloco de statements
        add_child(do_while, $7); // Condição
        $$ = do_while;
    }
    ;

break_statement:
    T_BREAK T_SEMICOLON
    {
        $$ = create_node(NODE_BREAK, NULL);
    }
    ;

continue_statement:
    T_CONTINUE T_SEMICOLON
    {
        $$ = create_node(NODE_CONTINUE, NULL);
    }
    ;

scanf_statement:
    T_SCANF T_LPAREN T_STRING T_COMMA T_AMPERSAND T_ID T_RPAREN T_SEMICOLON
    {
        ASTNode *scanf_node = create_node(NODE_SCANF, $3);
        add_child(scanf_node, create_node(NODE_IDENTIFIER, $6));
        $$ = scanf_node;
        free($3); free($6);
    }
    ;

while_statement:
    T_WHILE T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE
    {
        ASTNode *while_node = create_node(NODE_WHILE, NULL);
        add_child(while_node, $3); // Condição
        add_child(while_node, $6); // Corpo
        $$ = while_node;
    }
    ;

for_statement:
    T_FOR T_LPAREN declaration_or_expression T_SEMICOLON expression T_SEMICOLON expression T_RPAREN
    T_LBRACE statements T_RBRACE
    {
        ASTNode *for_node = create_node(NODE_FOR, NULL);
        add_child(for_node, $3); // Inicialização
        add_child(for_node, $5); // Condição
        add_child(for_node, $7); // Incremento
        add_child(for_node, $10); // Corpo
        $$ = for_node;
    }
    ;

declaration_or_expression:
    declaration
    | assignment_statement
    | expression
    | %empty { $$ = create_node(NODE_EMPTY, NULL); }
    ;

assignment_statement:
    T_ID T_ASSIGN expression T_SEMICOLON
    {
        if (lookup_symbol($1) == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, $1);
            yyerror(msg);
        }

        $$ = create_assignment_node("=", 
            create_node(NODE_IDENTIFIER, $1), 
            $3);
        free($1);
    }
    | T_ID T_PLUS_ASSIGN expression T_SEMICOLON
    {
        if (lookup_symbol($1) == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, $1);
            yyerror(msg);
        }

        ASTNode *lhs = create_node(NODE_IDENTIFIER, $1);
        ASTNode *rhs = create_binary_op("+", lhs, $3);
        $$ = create_assignment_node("=", lhs, rhs);
        free($1);
    }
    | T_ID T_MINUS_ASSIGN expression T_SEMICOLON
    {
        if (lookup_symbol($1) == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, $1);
            yyerror(msg);
        }

        ASTNode *lhs = create_node(NODE_IDENTIFIER, $1);
        ASTNode *rhs = create_binary_op("-", lhs, $3);
        $$ = create_assignment_node("=", lhs, rhs);
        free($1);
    }
    ;

increment_statement:
    T_ID T_INC T_SEMICOLON
    {
        ASTNode *inc = create_node(NODE_UNARY_OP, "++");
        add_child(inc, create_node(NODE_IDENTIFIER, $1));
        $$ = inc;
        free($1);
    }
    | T_INC T_ID T_SEMICOLON
    {
        ASTNode *inc = create_node(NODE_UNARY_OP, "++");
        add_child(inc, create_node(NODE_IDENTIFIER, $2));
        $$ = inc;
        free($2);
    }
    ;

decrement_statement:
    T_ID T_DEC T_SEMICOLON
    {
        ASTNode *dec = create_node(NODE_UNARY_OP, "--");
        add_child(dec, create_node(NODE_IDENTIFIER, $1));
        $$ = dec;
        free($1);
    }
    | T_DEC T_ID T_SEMICOLON
    {
        ASTNode *dec = create_node(NODE_UNARY_OP, "--");
        add_child(dec, create_node(NODE_IDENTIFIER, $2));
        $$ = dec;
        free($2);
    }
    ;

return_statement:
    T_RETURN expression T_SEMICOLON
    {
        ASTNode *ret = create_node(NODE_RETURN, NULL);
        add_child(ret, $2);
        $$ = ret;
    }
    ;

if_statement:
    T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE
    {
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, $3); // Condição
        add_child(if_node, $6); // Then
        if_node_temp = if_node;
        $$ = if_node;
    }
    | T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE
    {
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, $3); // Condição
        add_child(if_node, $6); // Then
        
        ASTNode *elseif = create_node(NODE_ELSE_IF, NULL);
        add_child(elseif, $11); // Condição do else if
        add_child(elseif, $14); // Then do else if
        
        add_child(if_node, elseif);
        $$ = if_node;
    }
    | T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_LBRACE statements T_RBRACE
    {
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, $3); // Condição
        add_child(if_node, $6); // Then
        
        ASTNode *else_node = create_node(NODE_ELSE, NULL);
        add_child(else_node, $10); // Bloco else
        
        add_child(if_node, else_node);
        $$ = if_node;
    }
    | T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_LBRACE statements T_RBRACE
    {
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, $3); // Condição
        add_child(if_node, $6); // Then
        
        ASTNode *elseif = create_node(NODE_ELSE_IF, NULL);
        add_child(elseif, $11); // Condição do else if
        add_child(elseif, $14); // Then do else if
        
        ASTNode *else_node = create_node(NODE_ELSE, NULL);
        add_child(else_node, $18); // Bloco else
        
        add_child(elseif, else_node);
        add_child(if_node, elseif);
        $$ = if_node;
    }
    ;

expression:
    T_ID                     {
        // Verificar se a variável foi declarada antes do uso
        Symbol *sym = lookup_symbol($1);
        if (sym == NULL) {
            fprintf(stderr, "Erro semântico: Variável '%s' usada, mas não declarada\n", $1);
            yyerror("erro semântico: variável não declarada");
        }
        $$ = create_node(NODE_IDENTIFIER, $1);
    }
    | T_NUMBER_INT           { 
        char num[20]; 
        sprintf(num, "%d", $1); 
        $$ = create_node(NODE_CONST_INT, num); 
    }
    | T_NUMBER_FLOAT         { 
        // Directly use the string representation from the lexer
        $$ = create_node(NODE_CONST_FLOAT, $1); 
    }
    | T_STRING               { $$ = create_node(NODE_CONST_STRING, $1); }
    | T_CHAR_LITERAL         { $$ = create_node(NODE_CONST_CHAR, $1); }
    | expression T_PLUS expression    { $$ = create_binary_op("+", $1, $3); }
    | expression T_MINUS expression   { $$ = create_binary_op("-", $1, $3); }
    | expression T_MULT expression    { $$ = create_binary_op("*", $1, $3); }
    | expression T_DIV expression     { $$ = create_binary_op("/", $1, $3); }
    | expression T_MOD expression     { $$ = create_binary_op("%", $1, $3); }
    | expression T_EQ expression      { $$ = create_binary_op("==", $1, $3); }
    | expression T_NEQ expression     { $$ = create_binary_op("!=", $1, $3); }
    | expression T_LT expression      { $$ = create_binary_op("<", $1, $3); }
    | expression T_GT expression      { $$ = create_binary_op(">", $1, $3); }
    | expression T_LE expression      { $$ = create_binary_op("<=", $1, $3); }
    | expression T_GE expression      { $$ = create_binary_op(">=", $1, $3); }
    | expression T_AND expression     { $$ = create_binary_op("e", $1, $3); }
    | expression T_OR expression      { $$ = create_binary_op("ou", $1, $3); }
    | expression T_BIT_OR expression  { $$ = create_binary_op("|", $1, $3); }
    | T_AMPERSAND expression         { $$ = create_unary_op("&", $2); }
    | T_NOT expression               { $$ = create_unary_op("nao", $2); }
    | T_LPAREN expression T_RPAREN   { $$ = $2; } // Remove parênteses
    | expression T_DOT T_ID           { 
        ASTNode *dot = create_node(NODE_MEMBER_ACCESS, ".");
        add_child(dot, $1);
        add_child(dot, create_node(NODE_IDENTIFIER, $3));
        $$ = dot;
        free($3);
    }
    | expression T_ARROW T_ID         { 
        ASTNode *arrow = create_node(NODE_POINTER_ACCESS, "->");
        add_child(arrow, $1);
        add_child(arrow, create_node(NODE_IDENTIFIER, $3));
        $$ = arrow;
        free($3);
    }
    | '*' expression                  { $$ = create_unary_op("*", $2); }
    ;

printf_statement:
    T_PRINTF T_LPAREN expression T_RPAREN T_SEMICOLON
    {
        ASTNode *printf_node = create_node(NODE_PRINTF, NULL);
        add_child(printf_node, $3);
        $$ = printf_node;
    }
    ;

%%

// Funções auxiliares
ASTNode* create_declaration_node(char *type, char *name, ASTNode *init) {
    ASTNode *decl = create_node(NODE_DECLARATION, name);
    add_child(decl, create_node(NODE_TYPE, type));
    if (init) {
        ASTNode *assign = create_node(NODE_ASSIGNMENT, "=");
        add_child(assign, create_node(NODE_IDENTIFIER, name));
        add_child(assign, init);
        add_child(decl, assign);
    }
    return decl;
}

ASTNode* create_assignment_node(char *op, ASTNode *lhs, ASTNode *rhs) {
    ASTNode *assign = create_node(NODE_ASSIGNMENT, op);
    add_child(assign, lhs);
    add_child(assign, rhs);
    return assign;
}

ASTNode* create_binary_op(char *op, ASTNode *lhs, ASTNode *rhs) {
    ASTNode *binop = create_node(NODE_BINARY_OP, op);
    add_child(binop, lhs);
    add_child(binop, rhs);
    return binop;
}

ASTNode* create_unary_op(char *op, ASTNode *operand) {
    ASTNode *unop = create_node(NODE_UNARY_OP, op);
    add_child(unop, operand);
    return unop;
}

// Mensagem de erro sintático com linha
void yyerror(const char *s) {
    fprintf(stderr, "%s\n", s);
    exit(1);
}