%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"

extern int yylex();
extern char* yytext;
extern FILE* yyin;
void yyerror(const char* s);

AstNode* ast_root = NULL;
%}

/* Tokens e tipos */
%token TIPO_REAL TIPO_DUPLO TIPO_CARACTERE TIPO_VAZIO TIPO_LONGO TIPO_CURTO
%token TIPO_SEM_SINAL TIPO_COM_SINAL TIPO_INTEIRO

%token SE SENAO ENQUANTO PARA FACA RETORNE QUEBRA CONTINUE ESCOLHA CASO PADRAO

%token UNIAO ENUM CONST ESTATICO EXTERNO REGISTRO TYPEDEF ESTRUTURA PRINCIPAL

%token MAIS_IGUAL MENOS_IGUAL MULT_IGUAL DIV_IGUAL INCREMENTO DECREMENTO
%token IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token E_LOGICO OU_LOGICO NAO_LOGICO
%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO MODULO IGUAL

%token ABRE_PAREN FECHA_PAREN ABRE_CHAVE FECHA_CHAVE ABRE_COLCHETE FECHA_COLCHETE
%token PONTO_E_VIRGULA VIRGULA PONTO DOIS_PONTOS

%token IDENTIFICADOR NUMERO LITERAL_STRING LITERAL_CHAR
%nonassoc IFX
%nonassoc SENAO

%union {
    int ival;
    float fval;
    char* sval;
    AstNode* node;
}

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
    : declaracoes { ast_root = $1; printf("Programa analisado com sucesso!\\n"); }
    ;

declaracoes
    : declaracao { $$ = $1; }
    | declaracoes declaracao { $$ = $2; }
    ;

declaracao
    : declaracao_variavel { $$ = $1; }
    | declaracao_funcao { $$ = $1; }
    | definicao_funcao { $$ = $1; }
    | declaracao_estrutura { $$ = NULL; }
    ;

declaracao_variavel
    : tipo IDENTIFICADOR PONTO_E_VIRGULA { $$ = NULL; }
    | tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA { $$ = create_equal_node(NULL, $4); }
    ;

declaracao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN PONTO_E_VIRGULA { $$ = NULL; }
    ;

definicao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN bloco_comandos { $$ = $5; }
    ;

declaracao_estrutura
    : ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA { $$ = NULL; }
    ;

lista_campos
    : declaracao_campo { $$ = NULL; }
    ;

declaracao_campo
    : tipo IDENTIFICADOR PONTO_E_VIRGULA { $$ = NULL; }
    ;

tipo
    : TIPO_INTEIRO { $$ = NULL; }
    ;

bloco_comandos
    : ABRE_CHAVE comandos FECHA_CHAVE { $$ = $2; }
    | ABRE_CHAVE FECHA_CHAVE { $$ = NULL; }
    ;

comandos
    : comando { $$ = $1; }
    | comandos comando { $$ = $2; }
    ;

comando
    : comando_se { $$ = $1; }
    | comando_enquanto { $$ = $1; }
    | comando_retorno { $$ = $1; }
    | bloco_comandos { $$ = $1; }
    | expressao PONTO_E_VIRGULA { $$ = $1; }
    ;

comando_se
    : SE ABRE_PAREN expressao FECHA_PAREN comando %prec IFX { $$ = $3; }
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando { $$ = $3; }
    ;

comando_enquanto
    : ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando { $$ = $3; }
    ;

comando_retorno
    : RETORNE expressao PONTO_E_VIRGULA { $$ = $2; }
    | RETORNE PONTO_E_VIRGULA { $$ = NULL; }
    ;

expressao
    : expressao_atribuicao { $$ = $1; }
    ;

expressao_atribuicao
    : expressao_logica { $$ = $1; }
    | IDENTIFICADOR IGUAL expressao_atribuicao { $$ = create_equal_node(NULL, $3); }
    ;

expressao_logica
    : expressao_relacional { $$ = $1; }
    ;

expressao_relacional
    : expressao_aditiva { $$ = $1; }
    | expressao_relacional IGUAL_IGUAL expressao_aditiva { $$ = create_equal_node($1, $3); }
    ;

expressao_aditiva
    : expressao_multiplicativa { $$ = $1; }
    | expressao_aditiva SOMA expressao_multiplicativa { $$ = create_binop_node(OP_ADD, $1, $3); }
    ;

expressao_multiplicativa
    : expressao_unaria { $$ = $1; }
    | expressao_multiplicativa MULTIPLICACAO expressao_unaria { $$ = create_binop_node(OP_MUL, $1, $3); }
    ;

expressao_unaria
    : expressao_primaria { $$ = $1; }
    ;

expressao_primaria
    : NUMERO { $$ = create_literal_node($1); }
    | ABRE_PAREN expressao FECHA_PAREN { $$ = $2; }
    ;

lista_argumentos
    : expressao { $$ = $1; }
    | lista_argumentos VIRGULA expressao { $$ = $3; }
    ;

comando_faca_enquanto
    : FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA {
        /* Nodo de laço do tipo "do-while" */
        $$ = $2;  // simplificado para retornar o corpo
    }
    ;

comando_para
    : PARA ABRE_PAREN tipo_opcional IDENTIFICADOR IGUAL expressao
      PONTO_E_VIRGULA expressao_condicao PONTO_E_VIRGULA expressao_incremento
      FECHA_PAREN bloco_comandos {
        $$ = $12; // também simplificado, o ideal seria criar um nó para "for"
    }
    ;

comando_switch
    : ESCOLHA ABRE_PAREN expressao FECHA_PAREN ABRE_CHAVE lista_casos FECHA_CHAVE {
        $$ = $3;
    }
    ;

lista_casos
    : lista_casos caso { $$ = $2; }
    | caso { $$ = $1; }
    ;

caso
    : CASO caso_escolha DOIS_PONTOS lista_comandos { $$ = $4; }
    | PADRAO DOIS_PONTOS lista_comandos { $$ = $3; }
    ;

lista_comandos
    : lista_comandos comando { $$ = $2; }
    | comando { $$ = $1; }
    ;

caso_escolha
    : IDENTIFICADOR { $$ = NULL; }
    | NUMERO { $$ = create_literal_node($1); }
    ;

tipo_opcional
    : tipo { $$ = NULL; }
    | /* vazio */ { $$ = NULL; }
    ;

expressao_condicao
    : expressao { $$ = $1; }
    | /* vazio */ { $$ = NULL; }
    ;

expressao_incremento
    : expressao { $$ = $1; }
    | /* vazio */ { $$ = NULL; }
    ;

expressao_inicializacao
    : declaracao_variavel { $$ = $1; }
    | expressao { $$ = $1; }
    | /* vazio */ { $$ = NULL; }
    ;

%%

/* Função principal opcional
int main() {
    return yyparse();
}
*/

%%

