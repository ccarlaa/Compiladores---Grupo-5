%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversor.h"
#include "ast.h"
#include "y.tab.h"
#include <stdarg.h>

#define MAX_RULES 1000
char *rule_names[MAX_RULES];
int rule_counts[MAX_RULES];
int rule_total = 0;

void rule_hit(const char *name) {
    for (int i = 0; i < rule_total; ++i) {
        if (strcmp(rule_names[i], name) == 0) {
            rule_counts[i]++;
            return;
        }
    }
    if (rule_total < MAX_RULES) {
        rule_names[rule_total] = strdup(name);
        rule_counts[rule_total] = 1;
        rule_total++;
    }
}

void print_grammar_coverage() {
    FILE *f = fopen("coverage_report.txt", "w");
    if (!f) return;

    fprintf(f, "Cobertura:\n");
    for (int i = 0; i < rule_total; ++i) {
        fprintf(f, "%s: %d\n", rule_names[i], rule_counts[i]);
    }
    fclose(f);
}

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
%token T_PRINTF_ARGS

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
%type <ast> function_call argument_list
%type <ast> printf_args
%type <sval> type_specifier declarator direct_declarator pointer


%start program

%%

program:
    {
        rule_hit("program");
        init_symbol_table();
        ast_root = create_node(NODE_PROGRAM, "programa");
    }
    function_list
    {
        generate_portugol(ast_root);
        free_ast(ast_root);
        print_symbol_table_stderr();
        free_symbol_table();

        print_grammar_coverage();
    }
;

function_list:
    %empty 
    {
        rule_hit("function_list_empty");
        $$ = create_node(NODE_EMPTY, NULL);
    }
    | function_list function_declaration
    {
        rule_hit("function_list_append");
        add_child(ast_root, $2);
        $$ = $1;
    }
    ;

function_declaration:
    type_specifier T_ID T_LPAREN function_parameter T_RPAREN
    {
        rule_hit("function_declaration");
        current_scope++;

        insert_symbol($2, $1, current_scope - 1);

        add_parameters_to_symbol_table($4);

        ASTNode *func_node = create_node(NODE_FUNCTION, strdup($2));
        ASTNode *type_node = create_node(NODE_TYPE, strdup($1));
        ASTNode *body_node = create_node(NODE_BLOCK, NULL);

        add_child(func_node, type_node);
        add_child(func_node, $4); 
        add_child(func_node, body_node);

        func_node_temp = func_node;
        body_node_temp = body_node;
    }
    T_LBRACE
    declarations
    statements
    T_RBRACE
    {
        if ($8 && $8->type != NODE_EMPTY) {
            add_child(body_node_temp, $8);
        }
        if ($9 && $9->type != NODE_EMPTY) {
            add_child(body_node_temp, $9);
        }
        
        $$ = func_node_temp;
        
        current_scope--;

        func_node_temp = NULL;
        body_node_temp = NULL;
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
        rule_hit("parameter_list_single");
        ASTNode *param_list_node = create_node(NODE_PARAM_LIST, NULL);
        ASTNode *param_node = create_node(NODE_PARAMETER, strdup($2));
        ASTNode *type_node = create_node(NODE_TYPE, strdup($1));
        
        add_child(param_node, type_node);
        add_child(param_list_node, param_node);
        
        $$ = param_list_node;
        
    }
    | parameter_list T_COMMA type_specifier declarator
    {
        rule_hit("parameter_list_multiple");
        ASTNode *param_node = create_node(NODE_PARAMETER, strdup($4));
        ASTNode *type_node = create_node(NODE_TYPE, strdup($3));
        
        add_child(param_node, type_node);
        add_child($1, param_node);
        
        $$ = $1;
        
        // free($3); free($4);
    }
    ;

    function_call:
    T_ID T_LPAREN argument_list T_RPAREN
    {
        rule_hit("function_call");
        ASTNode *call_node = create_node(NODE_FUNCTION_CALL, $1);
        add_child(call_node, $3);
        $$ = call_node;
    }
    ;

argument_list:
    %empty
    {
        rule_hit("argument_list_empty");
        $$ = create_node(NODE_STATEMENT_LIST, NULL); 
    }
    | expression
    {
        rule_hit("argument_list_single");
        ASTNode *list = create_node(NODE_STATEMENT_LIST, NULL);
        add_child(list, $1);
        $$ = list;
    }
    | argument_list T_COMMA expression
    {
        rule_hit("argument_list_multiple");
        add_child($1, $3);
        $$ = $1;
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
        rule_hit("declaration_simple");
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
        rule_hit("declaration_with_assignment");
        // Checagem de tipo da atribuição
        if ($4->data_type && strcmp($1, $4->data_type) != 0) {
            char msg[256];
            snprintf(msg, sizeof(msg),
                "Erro de tipo na linha %d: não é possível atribuir %s em %s.",
                yylineno, $4->data_type, $1);
            yyerror(msg);
        }

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
        rule_hit("statements_empty");
        $$ = create_node(NODE_STATEMENT_LIST, NULL);
    }
    | statements statement
    {
        add_child($1, $2);
        
        $$ = $1;
    }
    ;

statement:
    printf_statement                  { rule_hit("statement_printf"); $$ = $1; }
    | scanf_statement                   { rule_hit("statement_scanf"); $$ = $1; }
    | declaration                       { rule_hit("statement_declaration"); $$ = $1; }
    | if_statement                      { rule_hit("statement_if"); $$ = $1; }
    | while_statement                   { rule_hit("statement_while"); $$ = $1; }
    | do_while_statement                { rule_hit("statement_do_while"); $$ = $1; }
    | return_statement                  { rule_hit("statement_return"); $$ = $1; }
    | assignment_statement              { rule_hit("statement_assignment"); $$ = $1; }
    | function_call T_SEMICOLON        { rule_hit("statement_function_call"); $$ = $1; }
    | T_SEMICOLON                       { rule_hit("statement_empty"); $$ = create_node(NODE_EMPTY, NULL); }
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
        rule_hit("do_while_statement");
        ASTNode *do_while = create_node(NODE_DO_WHILE, NULL);
        add_child(do_while, $3); // Bloco de statements
        add_child(do_while, $7); // Condição
        $$ = do_while;
    }
    ;

break_statement:
    T_BREAK T_SEMICOLON
    {
        rule_hit("break_statement");
        $$ = create_node(NODE_BREAK, NULL);
    }
    ;

continue_statement:
    T_CONTINUE T_SEMICOLON
    {
        rule_hit("continue_statement");
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
        rule_hit("while_statement");
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
        rule_hit("for_statement");
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
    {
        rule_hit("declaration_or_expression_declaration");
        $$ = $1;
    }
  | assignment_statement
    {
        rule_hit("declaration_or_expression_assignment");
        $$ = $1;
    }
  | expression
    {
        rule_hit("declaration_or_expression_expression");
        $$ = $1;
    }
  | %empty
    {
        rule_hit("declaration_or_expression_empty");
        $$ = create_node(NODE_EMPTY, NULL);
    }
;


assignment_statement:
    | T_ID T_ASSIGN expression T_SEMICOLON
    {
        rule_hit("assignment_simple");
        Symbol *sym = lookup_symbol($1);
        if (sym == NULL) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Erro semântico na linha %d: Variável '%s' não declarada.", yylineno, $1);
            yyerror(msg);
        }

        if ($3->data_type && strcmp(sym->type, $3->data_type) != 0) {
            char msg[256];
            snprintf(msg, sizeof(msg),
                "Erro de tipo na linha %d: não é possível atribuir %s a variável do tipo %s.",
                yylineno, $3->data_type, sym->type);
            yyerror(msg);
        }

        $$ = create_assignment_node("=", create_node(NODE_IDENTIFIER, $1), $3);
        free($1);
    }
    | T_ID T_PLUS_ASSIGN expression T_SEMICOLON
    {
        rule_hit("assignment_simple");
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
        rule_hit("assignment_simple");
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
        rule_hit("increment_statement_post");
        ASTNode *inc = create_node(NODE_UNARY_OP, "++");
        add_child(inc, create_node(NODE_IDENTIFIER, $1));
        $$ = inc;
        free($1);
    }
    | T_INC T_ID T_SEMICOLON
    {
        rule_hit("increment_statement_pre");
        ASTNode *inc = create_node(NODE_UNARY_OP, "++");
        add_child(inc, create_node(NODE_IDENTIFIER, $2));
        $$ = inc;
        free($2);
    }
    ;

decrement_statement:
    T_ID T_DEC T_SEMICOLON
    {
        rule_hit("decrement_statement_post");
        ASTNode *dec = create_node(NODE_UNARY_OP, "--");
        add_child(dec, create_node(NODE_IDENTIFIER, $1));
        $$ = dec;
        free($1);
    }
    | T_DEC T_ID T_SEMICOLON
    {
        rule_hit("decrement_statement_pre");
        ASTNode *dec = create_node(NODE_UNARY_OP, "--");
        add_child(dec, create_node(NODE_IDENTIFIER, $2));
        $$ = dec;
        free($2);
    }
    ;

return_statement:
    T_RETURN expression T_SEMICOLON
    {
        rule_hit("return_statement");
        ASTNode *ret = create_node(NODE_RETURN, NULL);
        add_child(ret, $2);
        $$ = ret;
    }
    ;

if_statement:
    T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE
    {
        rule_hit("if_simple");
        ASTNode *if_node = create_node(NODE_IF, NULL);
        add_child(if_node, $3); // Condição
        add_child(if_node, $6); // Then
        if_node_temp = if_node;
        $$ = if_node;
    }
    | T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE T_ELSE T_IF T_LPAREN expression T_RPAREN T_LBRACE statements T_RBRACE
    {
        rule_hit("if_simple");
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
        rule_hit("if_simple");
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
        rule_hit("if_simple");
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
    T_ID
    {
        rule_hit("expression_id");
        Symbol *sym = lookup_symbol($1);
        if (sym == NULL) {
            fprintf(stderr, "Erro semântico: Variável '%s' usada, mas não declarada\n", $1);
            yyerror("erro semântico: variável não declarada");
        }
        $$ = create_node(NODE_IDENTIFIER, $1);
    }
    | T_NUMBER_INT           
    { 
        rule_hit("expression_int");
        char num[20]; 
        sprintf(num, "%d", $1); 
        $$ = create_node(NODE_CONST_INT, num); 
        $$->data_type = strdup("inteiro");
    }
    | T_NUMBER_FLOAT         
    { 
        rule_hit("expression_float");
        $$ = create_node(NODE_CONST_FLOAT, $1); 
        $$->data_type = strdup("real");
    }
    | T_STRING               
    { 
        rule_hit("expression_string");
        $$ = create_node(NODE_CONST_STRING, $1); 
        $$->data_type = strdup("string");
    }
    | T_CHAR_LITERAL         
    { 
        rule_hit("expression_char");
        $$ = create_node(NODE_CONST_CHAR, $1); 
        $$->data_type = strdup("caracter");
    }
    | expression T_PLUS expression    { rule_hit("expression_plus"); $$ = create_binary_op("+", $1, $3); }
    | expression T_MINUS expression   { rule_hit("expression_minus"); $$ = create_binary_op("-", $1, $3); }
    | expression T_MULT expression    { rule_hit("expression_mult"); $$ = create_binary_op("*", $1, $3); }
    | expression T_DIV expression     { rule_hit("expression_div"); $$ = create_binary_op("/", $1, $3); }
    | expression T_MOD expression     { rule_hit("expression_mod"); $$ = create_binary_op("%", $1, $3); }
    | expression T_EQ expression      { rule_hit("expression_eq"); $$ = create_binary_op("==", $1, $3); }
    | expression T_NEQ expression     { rule_hit("expression_neq"); $$ = create_binary_op("!=", $1, $3); }
    | expression T_LT expression      { rule_hit("expression_lt"); $$ = create_binary_op("<", $1, $3); }
    | expression T_GT expression      { rule_hit("expression_gt"); $$ = create_binary_op(">", $1, $3); }
    | expression T_LE expression      { rule_hit("expression_le"); $$ = create_binary_op("<=", $1, $3); }
    | expression T_GE expression      { rule_hit("expression_ge"); $$ = create_binary_op(">=", $1, $3); }
    | expression T_AND expression     { rule_hit("expression_and"); $$ = create_binary_op("e", $1, $3); }
    | expression T_OR expression      { rule_hit("expression_or"); $$ = create_binary_op("ou", $1, $3); }
    | expression T_BIT_OR expression  { rule_hit("expression_bit_or"); $$ = create_binary_op("|", $1, $3); }
    | T_AMPERSAND expression         { rule_hit("expression_amp"); $$ = create_unary_op("&", $2); }
    | T_NOT expression               { rule_hit("expression_not"); $$ = create_unary_op("nao", $2); }
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
    | function_call { $$ = $1; }
    ;

printf_statement:
    T_PRINTF T_LPAREN printf_args T_RPAREN T_SEMICOLON
    {
        ASTNode *printf_node = create_node(NODE_PRINTF, NULL);
        add_child(printf_node, $3);
        $$ = printf_node;
    }
    ;

printf_args:
    expression
    {
        rule_hit("printf_args_single");
        ASTNode *args = create_node(NODE_PRINTF_ARGS, NULL);
        add_child(args, $1);
        $$ = args;
    }
    | printf_args T_COMMA expression
    {
        rule_hit("printf_args_multiple");
        add_child($1, $3);
        $$ = $1;
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