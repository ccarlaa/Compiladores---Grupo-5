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

/* Tipos de dados */
%token TIPO_REAL TIPO_DUPLO TIPO_CARACTERE TIPO_VAZIO TIPO_LONGO TIPO_CURTO
%token TIPO_SEM_SINAL TIPO_COM_SINAL TIPO_INTEIRO

/* Estruturas de controle */
%token SE SENAO ENQUANTO PARA FACA RETORNE QUEBRA CONTINUE ESCOLHA CASO PADRAO

/* Declarações */
%token UNIAO ENUM CONST ESTATICO EXTERNO REGISTRO TYPEDEF ESTRUTURA PRINCIPAL

/* Operadores */
%token MAIS_IGUAL MENOS_IGUAL MULT_IGUAL DIV_IGUAL INCREMENTO DECREMENTO
%token IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token E_LOGICO OU_LOGICO NAO_LOGICO
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO MODULO IGUAL

/* Pontuação */
%token ABRE_PAREN FECHA_PAREN ABRE_CHAVE FECHA_CHAVE ABRE_COLCHETE FECHA_COLCHETE
%token PONTO_E_VIRGULA VIRGULA PONTO DOIS_PONTOS

/* Identificadores e literais */
%token IDENTIFICADOR NUMERO LITERAL_STRING LITERAL_CHAR
%nonassoc IFX
%nonassoc SENAO

/* Tipo dos valores semânticos */
%code requires {
    #include "ast/ast.h"
}

%union {
    int ival;
    float fval;
    char* sval;
    AstNode* node;
}

/* Tipo de cada símbolo gramatical */
%type <ival> NUMERO
%type <sval> IDENTIFICADOR LITERAL_STRING LITERAL_CHAR
%type <node> expressao programa
%type <node> declaracao declaracao_variavel declaracao_funcao definicao_funcao
%type <node> tipo lista_parametros parametro
%type <node> bloco_comandos comando comandos
%type <node> comando_se comando_enquanto comando_para comando_retorno
%type <node> expressao_atribuicao expressao_logica expressao_relacional
%type <node> expressao_aditiva expressao_multiplicativa expressao_unaria
%type <node> expressao_primaria lista_argumentos
%type <node> expressao_inicializacao expressao_condicao expressao_incremento
%type <node> tipo_opcional
%type <node> comando_switch

%%

programa
    : declaracoes                { 
                                    printf("Programa analisado com sucesso!\n");
                                  }
    ;

declaracoes
    : declaracao                 { }
    | declaracoes declaracao     { }
    ;

declaracao
    : declaracao_variavel        { }
    | declaracao_funcao          { }
    | definicao_funcao           { }
    | declaracao_estrutura       { }
    ;

/* Declaração de variáveis */
declaracao_variavel
    : tipo IDENTIFICADOR PONTO_E_VIRGULA                        { }
    | tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA        { }
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA { }
    | CONST tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA  { }
    | ESTATICO tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA { }
    | ESTATICO tipo IDENTIFICADOR PONTO_E_VIRGULA               { }
    ;

/* Declaração de funções (protótipos) */
declaracao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN PONTO_E_VIRGULA { }
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN PONTO_E_VIRGULA { }
    ;

/* Definição de funções (com corpo) */
definicao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN bloco_comandos  { }
    | tipo IDENTIFICADOR ABRE_PAREN lista_parametros FECHA_PAREN bloco_comandos { }
    | PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos { }
    | tipo PRINCIPAL ABRE_PAREN FECHA_PAREN bloco_comandos { }
    ;

/* Declaração de estruturas */
declaracao_estrutura
    : ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA { }
    ;

lista_campos
    : declaracao_campo        { }
    | lista_campos declaracao_campo { }
    ;

declaracao_campo
    : tipo IDENTIFICADOR PONTO_E_VIRGULA                        { }
    | tipo IDENTIFICADOR ABRE_COLCHETE NUMERO FECHA_COLCHETE PONTO_E_VIRGULA { }
    ;

tipo
    : TIPO_INTEIRO               { }
    | TIPO_REAL                  { }
    | TIPO_DUPLO                 { }
    | TIPO_CARACTERE             { }
    | TIPO_VAZIO                 { }
    | TIPO_LONGO                 { }
    | TIPO_CURTO                 { }
    | TIPO_SEM_SINAL             { }
    | TIPO_COM_SINAL             { }
    | ESTRUTURA IDENTIFICADOR    { }
    ;

lista_parametros
    : parametro                  { }
    | lista_parametros VIRGULA parametro { }
    ;

parametro
    : tipo IDENTIFICADOR         { }
    | tipo IDENTIFICADOR ABRE_COLCHETE FECHA_COLCHETE { }
    ;

bloco_comandos
    : ABRE_CHAVE FECHA_CHAVE     { }
    | ABRE_CHAVE comandos FECHA_CHAVE { }
    ;

comandos
    : comando                    { }
    | comandos comando           { }
    ;

comando
    : comando_se                 { }
    | comando_enquanto           { }
    | comando_faca_enquanto      { }
    | comando_para               { }
    | comando_retorno            { }
    | comando_switch             { }
    | bloco_comandos             { }
    | expressao PONTO_E_VIRGULA  { }
    | declaracao_variavel        { }
    | QUEBRA PONTO_E_VIRGULA     { }
    | CONTINUE PONTO_E_VIRGULA   { }
    | PONTO_E_VIRGULA            { }
    ;

comando_se
    : SE ABRE_PAREN expressao FECHA_PAREN comando %prec IFX { }
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando { }
    ;

comando_enquanto
    : ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando { }
    ;

comando_faca_enquanto
    : FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA { }
    ;

comando_para
    : PARA ABRE_PAREN tipo_opcional IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA expressao_condicao PONTO_E_VIRGULA expressao_incremento FECHA_PAREN bloco_comandos { }
    ;

comando_retorno
    : RETORNE PONTO_E_VIRGULA    { }
    | RETORNE expressao PONTO_E_VIRGULA { }
    ;

comando_switch
    : ESCOLHA ABRE_PAREN expressao FECHA_PAREN ABRE_CHAVE lista_casos FECHA_CHAVE { }
    ;

expressao
    : expressao_atribuicao       { $$ = $1; }
    ;

expressao_atribuicao
    : expressao_logica                       { $$ = $1; }
    | IDENTIFICADOR IGUAL expressao_atribuicao { }
    | IDENTIFICADOR MAIS_IGUAL expressao_atribuicao { }
    | IDENTIFICADOR MENOS_IGUAL expressao_atribuicao { }
    | IDENTIFICADOR MULT_IGUAL expressao_atribuicao { }
    | IDENTIFICADOR DIV_IGUAL expressao_atribuicao { }
    | IDENTIFICADOR ABRE_COLCHETE expressao FECHA_COLCHETE IGUAL expressao_atribuicao { }
    | IDENTIFICADOR PONTO IDENTIFICADOR IGUAL expressao_atribuicao { }
    ;

expressao_logica
    : expressao_relacional                   { $$ = $1; }
    | expressao_logica E_LOGICO expressao_relacional { }
    | expressao_logica OU_LOGICO expressao_relacional { }
    ;

expressao_relacional
    : expressao_aditiva                      { $$ = $1; }
    | expressao_relacional IGUAL_IGUAL expressao_aditiva { }
    | expressao_relacional DIFERENTE expressao_aditiva { }
    | expressao_relacional MENOR expressao_aditiva { }
    | expressao_relacional MAIOR expressao_aditiva { }
    | expressao_relacional MENOR_IGUAL expressao_aditiva { }
    | expressao_relacional MAIOR_IGUAL expressao_aditiva { }
    | expressao_relacional MODULO expressao_aditiva { $$ = create_binop_node(OP_MOD, $1, $3); }
    ;

expressao_aditiva
    : expressao_multiplicativa               { $$ = $1; }
    | expressao_aditiva SOMA expressao_multiplicativa { $$ = create_binop_node(OP_ADD, $1, $3); }
    | expressao_aditiva SUBTRACAO expressao_multiplicativa { $$ = create_binop_node(OP_SUB, $1, $3); }
    ;

expressao_multiplicativa
    : expressao_unaria                       { $$ = $1; }
    | expressao_multiplicativa MULTIPLICACAO expressao_unaria { $$ = create_binop_node(OP_MUL, $1, $3); }
    | expressao_multiplicativa DIVISAO expressao_unaria { $$ = create_binop_node(OP_DIV, $1, $3); }
    | expressao_multiplicativa MODULO expressao_unaria { $$ = create_binop_node(OP_MOD, $1, $3); }
    ;

expressao_unaria
    : expressao_primaria                     { $$ = $1; }
    | SUBTRACAO expressao_unaria             { }
    | NAO_LOGICO expressao_unaria            { }
    | INCREMENTO IDENTIFICADOR               { }
    | DECREMENTO IDENTIFICADOR               { }
    | IDENTIFICADOR INCREMENTO               { }
    | IDENTIFICADOR DECREMENTO               { }
    ;

expressao_primaria
    : IDENTIFICADOR                          { }
    | NUMERO                                 { $$ = create_literal_node($1); }
    | LITERAL_STRING                         { }
    | LITERAL_CHAR                           { }
    | ABRE_PAREN expressao FECHA_PAREN       { $$ = $2; }
    | IDENTIFICADOR ABRE_PAREN FECHA_PAREN   { }
    | IDENTIFICADOR ABRE_PAREN lista_argumentos FECHA_PAREN { }
    | IDENTIFICADOR ABRE_COLCHETE expressao FECHA_COLCHETE { }
    | IDENTIFICADOR PONTO IDENTIFICADOR      { }
    ;

lista_argumentos
    : expressao                              { }
    | lista_argumentos VIRGULA expressao     { }
    ;

expressao_inicializacao
    : declaracao_variavel
    | expressao
    | /* vazio */
    ;

expressao_condicao
    : expressao
    | /* vazio */
    ;

expressao_incremento
    : expressao
    | /* vazio */
    ;

tipo_opcional
    : tipo
    | /* vazio */
    ;

lista_casos
    : lista_casos caso  { }
    |
    caso                { }
    ;

caso
    : CASO caso_escolha DOIS_PONTOS lista_comandos  { }
    | PADRAO DOIS_PONTOS lista_comandos             { }
    ;

lista_comandos
    : lista_comandos comando    { }
    |
    comando                     { }
    ;

caso_escolha
    : IDENTIFICADOR
    | NUMERO
    ;
%%

/* Esta função será implementada em main.c */
/* int main() {
    return yyparse();
} */
