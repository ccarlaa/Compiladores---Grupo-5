%{
/*
 * TRADUTOR C PARA PORTUGOL
 * Análise Sintática: Converte estruturas C em código Portugol
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"

extern int yylex(void);
extern char* yytext;
void yyerror(const char *s);

AstNode* ast_root = NULL;
int nivel_indentacao = 0;

/* Funções para geração de código Portugol */
void imprimir_tipo_portugol(const char* tipo_c);
void imprimir_espacos(int nivel);
void gerar_codigo_portugol(AstNode* node);
%}

%union {
    int ival;
    float fval;
    char *sval;
    AstNode *node;
}

%token <sval> TIPO_INTEIRO TIPO_REAL TIPO_DUPLO TIPO_CARACTERE TIPO_VAZIO
%token <sval> TIPO_LONGO TIPO_CURTO TIPO_SEM_SINAL TIPO_COM_SINAL
%token <sval> IDENTIFICADOR LITERAL_STRING LITERAL_CHAR
%token <ival> NUMERO
%token <fval> NUMERO_REAL

%token SE SENAO ENQUANTO PARA FACA RETORNE QUEBRA CONTINUE
%token ESCOLHA CASO PADRAO ESTRUTURA UNIAO ENUM PRINCIPAL

%token MAIS_IGUAL MENOS_IGUAL MULT_IGUAL DIV_IGUAL
%token INCREMENTO DECREMENTO

%token IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token E_LOGICO OU_LOGICO NAO_LOGICO

%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO MODULO IGUAL
%token ABRE_PAREN FECHA_PAREN ABRE_CHAVE FECHA_CHAVE
%token ABRE_COLCHETE FECHA_COLCHETE PONTO_E_VIRGULA VIRGULA
%token PONTO DOIS_PONTOS

%type <node> programa funcao lista_parametros parametro
%type <node> lista_comandos comando declaracao_variavel
%type <node> comando_se comando_enquanto comando_para comando_retorno
%type <node> expressao expressao_atribuicao expressao_logica
%type <node> expressao_relacional expressao_aditiva expressao_multiplicativa
%type <node> expressao_unaria expressao_primaria
%type <sval> tipo

%nonassoc IFX
%nonassoc SENAO

%left E_LOGICO OU_LOGICO
%left IGUAL_IGUAL DIFERENTE
%left MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO MODULO
%right NAO_LOGICO

%start programa

%%

/* ========== PROGRAMA PRINCIPAL ========== */
programa:
    funcao {
        ast_root = $1;
        printf("// Código traduzido de C para Portugol\n\n");
        gerar_codigo_portugol($1);
        $$ = $1;
    }
    ;

/* ========== DEFINIÇÃO DE FUNÇÃO ========== */
funcao:
    tipo PRINCIPAL ABRE_PAREN FECHA_PAREN ABRE_CHAVE lista_comandos FECHA_CHAVE {
        printf("%s principal() {\n", 
               strcmp($1, "int") == 0 ? "inteiro" :
               strcmp($1, "void") == 0 ? "vazio" :
               strcmp($1, "float") == 0 ? "real" :
               strcmp($1, "double") == 0 ? "duplo" :
               strcmp($1, "char") == 0 ? "caractere" : $1);
        nivel_indentacao++;
        gerar_codigo_portugol($6);
        nivel_indentacao--;
        printf("}\n");
        $$ = create_function_node($1, "principal", $6);
    }
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN ABRE_CHAVE lista_comandos FECHA_CHAVE {
        printf("%s %s(", 
               strcmp($1, "int") == 0 ? "inteiro" :
               strcmp($1, "void") == 0 ? "vazio" :
               strcmp($1, "float") == 0 ? "real" :
               strcmp($1, "double") == 0 ? "duplo" :
               strcmp($1, "char") == 0 ? "caractere" : $1, $2);
        gerar_codigo_portugol($4);
        printf(") {\n");
        nivel_indentacao++;
        gerar_codigo_portugol($7);
        nivel_indentacao--;
        printf("}\n");
        $$ = create_function_node($1, $2, $7);
    }
    | tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN ABRE_CHAVE lista_comandos FECHA_CHAVE {
        printf("%s %s() {\n", 
               strcmp($1, "int") == 0 ? "inteiro" :
               strcmp($1, "void") == 0 ? "vazio" :
               strcmp($1, "float") == 0 ? "real" :
               strcmp($1, "double") == 0 ? "duplo" :
               strcmp($1, "char") == 0 ? "caractere" : $1, $2);
        nivel_indentacao++;
        gerar_codigo_portugol($6);
        nivel_indentacao--;
        printf("}\n");
        $$ = create_function_node($1, $2, $6);
    }
    ;

/* ========== LISTA DE PARÂMETROS ========== */
lista_parametros:
    parametro { $$ = $1; }
    | lista_parametros VIRGULA parametro {
        printf(", ");
        $$ = create_param_list_node($1, $3);
    }
    ;

parametro:
    tipo IDENTIFICADOR {
        printf("%s %s", 
               strcmp($1, "int") == 0 ? "inteiro" :
               strcmp($1, "void") == 0 ? "vazio" :
               strcmp($1, "float") == 0 ? "real" :
               strcmp($1, "double") == 0 ? "duplo" :
               strcmp($1, "char") == 0 ? "caractere" : $1, $2);
        $$ = create_param_node($1, $2);
    }
    ;

/* ========== TIPOS ========== */
tipo:
    TIPO_INTEIRO { $$ = "int"; }
    | TIPO_REAL { $$ = "float"; }
    | TIPO_DUPLO { $$ = "double"; }
    | TIPO_CARACTERE { $$ = "char"; }
    | TIPO_VAZIO { $$ = "void"; }
    ;

/* ========== LISTA DE COMANDOS ========== */
lista_comandos:
    /* vazio */ { $$ = NULL; }
    | lista_comandos comando {
        $$ = create_command_list_node($1, $2);
    }
    ;

/* ========== COMANDOS ========== */
comando:
    declaracao_variavel { $$ = $1; }
    | comando_se { $$ = $1; }
    | comando_enquanto { $$ = $1; }
    | comando_para { $$ = $1; }
    | comando_retorno { $$ = $1; }
    | expressao PONTO_E_VIRGULA {
        imprimir_espacos(nivel_indentacao);
        gerar_codigo_portugol($1);
        printf(";\n");
        $$ = $1;
    }
    | ABRE_CHAVE lista_comandos FECHA_CHAVE {
        imprimir_espacos(nivel_indentacao);
        printf("{\n");
        nivel_indentacao++;
        gerar_codigo_portugol($2);
        nivel_indentacao--;
        imprimir_espacos(nivel_indentacao);
        printf("}\n");
        $$ = $2;
    }
    ;

/* ========== DECLARAÇÃO DE VARIÁVEL ========== */
declaracao_variavel:
    tipo IDENTIFICADOR PONTO_E_VIRGULA {
        imprimir_espacos(nivel_indentacao);
        printf("%s %s;\n", 
               strcmp($1, "int") == 0 ? "inteiro" :
               strcmp($1, "void") == 0 ? "vazio" :
               strcmp($1, "float") == 0 ? "real" :
               strcmp($1, "double") == 0 ? "duplo" :
               strcmp($1, "char") == 0 ? "caractere" : $1, $2);
        $$ = create_var_decl_node($1, $2, NULL);
    }
    | tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA {
        imprimir_espacos(nivel_indentacao);
        printf("%s %s = ", 
               strcmp($1, "int") == 0 ? "inteiro" :
               strcmp($1, "void") == 0 ? "vazio" :
               strcmp($1, "float") == 0 ? "real" :
               strcmp($1, "double") == 0 ? "duplo" :
               strcmp($1, "char") == 0 ? "caractere" : $1, $2);
        gerar_codigo_portugol($4);
        printf(";\n");
        $$ = create_var_decl_node($1, $2, $4);
    }
    ;

/* ========== COMANDO SE ========== */
comando_se:
    SE ABRE_PAREN expressao FECHA_PAREN comando %prec IFX {
        imprimir_espacos(nivel_indentacao);
        printf("se (");
        gerar_codigo_portugol($3);
        printf(") ");
        if ($5->type == NODE_BLOCK) {
            printf("{\n");
            nivel_indentacao++;
            gerar_codigo_portugol($5);
            nivel_indentacao--;
            imprimir_espacos(nivel_indentacao);
            printf("}\n");
        } else {
            printf("\n");
            nivel_indentacao++;
            gerar_codigo_portugol($5);
            nivel_indentacao--;
        }
        $$ = create_if_node($3, $5, NULL);
    }
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando {
        imprimir_espacos(nivel_indentacao);
        printf("se (");
        gerar_codigo_portugol($3);
        printf(") ");
        if ($5->type == NODE_BLOCK) {
            printf("{\n");
            nivel_indentacao++;
            gerar_codigo_portugol($5);
            nivel_indentacao--;
            imprimir_espacos(nivel_indentacao);
            printf("} senao ");
        } else {
            printf("\n");
            nivel_indentacao++;
            gerar_codigo_portugol($5);
            nivel_indentacao--;
            imprimir_espacos(nivel_indentacao);
            printf("senao ");
        }
        if ($7->type == NODE_BLOCK) {
            printf("{\n");
            nivel_indentacao++;
            gerar_codigo_portugol($7);
            nivel_indentacao--;
            imprimir_espacos(nivel_indentacao);
            printf("}\n");
        } else {
            printf("\n");
            nivel_indentacao++;
            gerar_codigo_portugol($7);
            nivel_indentacao--;
        }
        $$ = create_if_node($3, $5, $7);
    }
    ;

/* ========== COMANDO ENQUANTO ========== */
comando_enquanto:
    ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando {
        imprimir_espacos(nivel_indentacao);
        printf("enquanto (");
        gerar_codigo_portugol($3);
        printf(") ");
        if ($5->type == NODE_BLOCK) {
            printf("{\n");
            nivel_indentacao++;
            gerar_codigo_portugol($5);
            nivel_indentacao--;
            imprimir_espacos(nivel_indentacao);
            printf("}\n");
        } else {
            printf("\n");
            nivel_indentacao++;
            gerar_codigo_portugol($5);
            nivel_indentacao--;
        }
        $$ = create_while_node($3, $5);
    }
    ;

/* ========== COMANDO PARA ========== */
comando_para:
    PARA ABRE_PAREN expressao PONTO_E_VIRGULA expressao PONTO_E_VIRGULA expressao FECHA_PAREN comando {
        imprimir_espacos(nivel_indentacao);
        printf("para (");
        gerar_codigo_portugol($3);
        printf("; ");
        gerar_codigo_portugol($5);
        printf("; ");
        gerar_codigo_portugol($7);
        printf(") ");
        if ($9->type == NODE_BLOCK) {
            printf("{\n");
            nivel_indentacao++;
            gerar_codigo_portugol($9);
            nivel_indentacao--;
            imprimir_espacos(nivel_indentacao);
            printf("}\n");
        } else {
            printf("\n");
            nivel_indentacao++;
            gerar_codigo_portugol($9);
            nivel_indentacao--;
        }
        $$ = create_for_node($3, $5, $7, $9);
    }
    ;

/* ========== COMANDO RETORNO ========== */
comando_retorno:
    RETORNE PONTO_E_VIRGULA {
        imprimir_espacos(nivel_indentacao);
        printf("retorne;\n");
        $$ = create_return_node(NULL);
    }
    | RETORNE expressao PONTO_E_VIRGULA {
        imprimir_espacos(nivel_indentacao);
        printf("retorne ");
        gerar_codigo_portugol($2);
        printf(";\n");
        $$ = create_return_node($2);
    }
    ;

/* ========== EXPRESSÕES ========== */
expressao:
    expressao_atribuicao { $$ = $1; }
    ;

expressao_atribuicao:
    expressao_logica { $$ = $1; }
    | IDENTIFICADOR IGUAL expressao_atribuicao {
        $$ = create_assign_node($1, $3);
    }
    ;

expressao_logica:
    expressao_relacional { $$ = $1; }
    | expressao_logica E_LOGICO expressao_relacional {
        $$ = create_binop_node(OP_AND, $1, $3);
    }
    | expressao_logica OU_LOGICO expressao_relacional {
        $$ = create_binop_node(OP_OR, $1, $3);
    }
    ;

expressao_relacional:
    expressao_aditiva { $$ = $1; }
    | expressao_relacional IGUAL_IGUAL expressao_aditiva {
        $$ = create_binop_node(OP_EQ, $1, $3);
    }
    | expressao_relacional DIFERENTE expressao_aditiva {
        $$ = create_binop_node(OP_NE, $1, $3);
    }
    | expressao_relacional MENOR expressao_aditiva {
        $$ = create_binop_node(OP_LT, $1, $3);
    }
    | expressao_relacional MAIOR expressao_aditiva {
        $$ = create_binop_node(OP_GT, $1, $3);
    }
    | expressao_relacional MENOR_IGUAL expressao_aditiva {
        $$ = create_binop_node(OP_LE, $1, $3);
    }
    | expressao_relacional MAIOR_IGUAL expressao_aditiva {
        $$ = create_binop_node(OP_GE, $1, $3);
    }
    ;

expressao_aditiva:
    expressao_multiplicativa { $$ = $1; }
    | expressao_aditiva SOMA expressao_multiplicativa {
        $$ = create_binop_node(OP_ADD, $1, $3);
    }
    | expressao_aditiva SUBTRACAO expressao_multiplicativa {
        $$ = create_binop_node(OP_SUB, $1, $3);
    }
    ;

expressao_multiplicativa:
    expressao_unaria { $$ = $1; }
    | expressao_multiplicativa MULTIPLICACAO expressao_unaria {
        $$ = create_binop_node(OP_MUL, $1, $3);
    }
    | expressao_multiplicativa DIVISAO expressao_unaria {
        $$ = create_binop_node(OP_DIV, $1, $3);
    }
    | expressao_multiplicativa MODULO expressao_unaria {
        $$ = create_binop_node(OP_MOD, $1, $3);
    }
    ;

expressao_unaria:
    expressao_primaria { $$ = $1; }
    | NAO_LOGICO expressao_unaria {
        $$ = create_unary_node(OP_NOT, $2);
    }
    | SOMA expressao_unaria {
        $$ = $2; /* +x é apenas x */
    }
    | SUBTRACAO expressao_unaria {
        $$ = create_unary_node(OP_NEG, $2);
    }
    ;

expressao_primaria:
    IDENTIFICADOR {
        $$ = create_id_node($1);
    }
    | NUMERO {
        $$ = create_number_node($1);
    }
    | NUMERO_REAL {
        $$ = create_real_node($1);
    }
    | LITERAL_STRING {
        $$ = create_string_node($1);
    }
    | LITERAL_CHAR {
        $$ = create_char_node($1);
    }
    | ABRE_PAREN expressao FECHA_PAREN {
        $$ = $2;
    }
    ;

%%

/* ========== FUNÇÕES AUXILIARES ========== */

void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

void imprimir_espacos(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
}

void gerar_codigo_portugol(AstNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_FUNCTION:
            /* Função já é impressa na regra gramatical */
            break;
            
        case NODE_COMMAND_LIST:
            if (node->data.command_list.first) {
                gerar_codigo_portugol(node->data.command_list.first);
            }
            if (node->data.command_list.second) {
                gerar_codigo_portugol(node->data.command_list.second);
            }
            break;
            
        case NODE_VAR_DECL:
            /* Declaração já é impressa na regra gramatical */
            break;
            
        case NODE_IF:
            /* If já é impresso na regra gramatical */
            break;
            
        case NODE_WHILE:
            /* While já é impresso na regra gramatical */
            break;
            
        case NODE_FOR:
            /* For já é impresso na regra gramatical */
            break;
            
        case NODE_RETURN:
            /* Return já é impresso na regra gramatical */
            break;
            
        case NODE_ASSIGN:
            printf("%s = ", node->data.assign.var);
            gerar_codigo_portugol(node->data.assign.expr);
            break;
            
        case NODE_BINOP:
            gerar_codigo_portugol(node->data.binop.left);
            switch (node->data.binop.op) {
                case OP_ADD: printf(" + "); break;
                case OP_SUB: printf(" - "); break;
                case OP_MUL: printf(" * "); break;
                case OP_DIV: printf(" / "); break;
                case OP_MOD: printf(" %% "); break;
                case OP_EQ: printf(" == "); break;
                case OP_NE: printf(" != "); break;
                case OP_LT: printf(" < "); break;
                case OP_GT: printf(" > "); break;
                case OP_LE: printf(" <= "); break;
                case OP_GE: printf(" >= "); break;
                case OP_AND: printf(" && "); break;
                case OP_OR: printf(" || "); break;
            }
            gerar_codigo_portugol(node->data.binop.right);
            break;
            
        case NODE_UNARY:
            switch (node->data.unary.op) {
                case OP_NOT: printf("!"); break;
                case OP_NEG: printf("-"); break;
            }
            gerar_codigo_portugol(node->data.unary.operand);
            break;
            
        case NODE_ID:
            printf("%s", node->data.id.name);
            break;
            
        case NODE_NUMBER:
            printf("%d", node->data.number.value);
            break;
            
        case NODE_REAL:
            printf("%.2f", node->data.real.value);
            break;
            
        case NODE_STRING:
            printf("%s", node->data.string.value);
            break;
            
        case NODE_CHAR:
            printf("%s", node->data.character.value);
            break;
            
        default:
            break;
    }
}