%{
#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"
#include "semantic/tabela.h"
#include "semantic/tipos.h"

extern int yylex();
extern char* yytext;
extern FILE* yyin;
void yyerror(const char* s);

AstNode* ast_root = NULL;
TipoSimples tipo_atual;
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

%type <node> programa declaracoes declaracao declaracao_variavel declaracao_funcao definicao_funcao declaracao_estrutura
%type <node> lista_campos declaracao_campo tipo bloco_comandos comandos comando
%type <node> comando_se comando_enquanto comando_para comando_retorno comando_faca_enquanto comando_switch
%type <node> lista_argumentos lista_casos caso lista_comandos caso_escolha
%type <node> expressao expressao_atribuicao expressao_logica expressao_relacional
%type <node> expressao_aditiva expressao_multiplicativa expressao_unaria expressao_primaria
%type <node> expressao_inicializacao expressao_condicao expressao_incremento tipo_opcional

%%

programa
    : declaracoes { ast_root = $1; printf("Programa analisado com sucesso!\n"); }
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
    : tipo IDENTIFICADOR PONTO_E_VIRGULA {
        if (!insere_simbolo($2, tipo_atual)) {
            fprintf(stderr, "Erro: variável '%s' já declarada.\n", $2);
            exit(1);
        }
        $$ = NULL;
    }
    | tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA {
        if (!insere_simbolo($2, tipo_atual)) {
            fprintf(stderr, "Erro: variável '%s' já declarada.\n", $2);
            exit(1);
        }
        if (!verifica_tipo_atribuicao(tipo_atual, $4->tipo)) {
            fprintf(stderr, "Erro: atribuição incompatível para '%s'.\n", $2);
            exit(1);
        }
        $$ = create_equal_node(NULL, $4);
        $$->tipo = tipo_atual;
    }
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
    : TIPO_INTEIRO { tipo_atual = TIPO_INT; $$ = NULL; }
    | TIPO_REAL    { tipo_atual = TIPO_REAL_; $$ = NULL; }
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
    | IDENTIFICADOR IGUAL expressao_atribuicao {
        TipoSimples t = busca_simbolo($1);
        if (t == TIPO_INVALIDO) {
            fprintf(stderr, "Erro: variável '%s' não declarada.\n", $1);
            exit(1);
        }
        if (!verifica_tipo_atribuicao(t, $3->tipo)) {
            fprintf(stderr, "Erro: tipos incompatíveis na atribuição a '%s'.\n", $1);
            exit(1);
        }
        $$ = create_equal_node(NULL, $3);
        $$->tipo = t;
    }
    ;

expressao_logica
    : expressao_relacional { $$ = $1; }
    ;

expressao_relacional
    : expressao_aditiva { $$ = $1; }
    | expressao_relacional IGUAL_IGUAL expressao_aditiva {
        TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
        if (t == TIPO_INVALIDO) {
            fprintf(stderr, "Erro: tipos incompatíveis em comparação.\n");
            exit(1);
        }
        $$ = create_equal_node($1, $3);
        $$->tipo = TIPO_INT;
    }
    ;

expressao_aditiva
    : expressao_multiplicativa { $$ = $1; }
    | expressao_aditiva SOMA expressao_multiplicativa {
        TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
        if (t == TIPO_INVALIDO) {
            fprintf(stderr, "Erro: tipos incompatíveis em soma.\n");
            exit(1);
        }
        $$ = create_binop_node(OP_ADD, $1, $3);
        $$->tipo = t;
    }
    ;

expressao_multiplicativa
    : expressao_unaria { $$ = $1; }
    | expressao_multiplicativa MULTIPLICACAO expressao_unaria {
        TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
        if (t == TIPO_INVALIDO) {
            fprintf(stderr, "Erro: tipos incompatíveis em multiplicação.\n");
            exit(1);
        }
        $$ = create_binop_node(OP_MUL, $1, $3);
        $$->tipo = t;
    }
    ;

expressao_unaria
    : expressao_primaria { $$ = $1; }
    ;

expressao_primaria
    : NUMERO {
        $$ = create_literal_node($1);
        $$->tipo = TIPO_INT;
    }
    | IDENTIFICADOR {
        TipoSimples t = busca_simbolo($1);
        if (t == TIPO_INVALIDO) {
            fprintf(stderr, "Erro: variável '%s' não declarada.\n", $1);
            exit(1);
        }
        $$ = create_literal_node(0); // placeholder
        $$->tipo = t;
    }
    | ABRE_PAREN expressao FECHA_PAREN { $$ = $2; }
    ;

lista_argumentos
    : expressao { $$ = $1; }
    | lista_argumentos VIRGULA expressao { $$ = $3; }
    ;

comando_faca_enquanto
    : FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA {
        if ($5->tipo != TIPO_INT) {
            fprintf(stderr, "Erro: condição do 'faca-enquanto' deve ser do tipo inteiro.\n");
            exit(1);
        }
        $$ = $2;
    }
    ;

comando_para
    : PARA ABRE_PAREN tipo_opcional IDENTIFICADOR IGUAL expressao
      PONTO_E_VIRGULA expressao_condicao PONTO_E_VIRGULA expressao_incremento
      FECHA_PAREN bloco_comandos {
        if (!insere_simbolo($4, tipo_atual)) {
            fprintf(stderr, "Erro: variável '%s' já declarada no 'para'.\n", $4);
            exit(1);
        }

        if (!verifica_tipo_atribuicao(tipo_atual, $6->tipo)) {
            fprintf(stderr, "Erro: tipo incompatível na inicialização de '%s' no 'para'.\n", $4);
            exit(1);
        }

        if ($8 && $8->tipo != TIPO_INT) {
            fprintf(stderr, "Erro: condição do 'para' deve ser do tipo inteiro.\n");
            exit(1);
        }

        $$ = $12;
    }
    ;

comando_switch
    : ESCOLHA ABRE_PAREN expressao FECHA_PAREN ABRE_CHAVE lista_casos FECHA_CHAVE {
        if ($3->tipo != TIPO_INT) {
            fprintf(stderr, "Erro: expressão do 'switch' deve ser do tipo inteiro.\n");
            exit(1);
        }
        $$ = $3;
    }
    ;

lista_casos
    : lista_casos caso { $$ = $2; }
    | caso { $$ = $1; }
    ;

caso
    : CASO caso_escolha DOIS_PONTOS lista_comandos {
        if ($2 && $2->tipo != TIPO_INT) {
            fprintf(stderr, "Erro: valor do 'caso' deve ser inteiro.\n");
            exit(1);
        }
        $$ = $4;
    }
    | PADRAO DOIS_PONTOS lista_comandos { $$ = $3; }
    ;

lista_comandos
    : lista_comandos comando { $$ = $2; }
    | comando { $$ = $1; }
    ;

caso_escolha
    : IDENTIFICADOR {
        TipoSimples t = busca_simbolo($1);
        if (t == TIPO_INVALIDO) {
            fprintf(stderr, "Erro: identificador '%s' usado em 'caso' não declarado.\n", $1);
            exit(1);
        }
        if (t != TIPO_INT) {
            fprintf(stderr, "Erro: expressão 'caso' deve ser do tipo inteiro.\n");
            exit(1);
        }
        $$ = create_literal_node(0);
        $$->tipo = t;
    }
    | NUMERO {
        $$ = create_literal_node($1);
        $$->tipo = TIPO_INT;
    }
    ;

tipo_opcional
    : tipo { $$ = NULL; }
    | /* vazio */ { $$ = NULL; }
    ;

expressao_condicao
    : expressao {
        if ($1->tipo != TIPO_INT) {
            fprintf(stderr, "Erro: condição de 'para' deve ser do tipo inteiro.\n");
            exit(1);
        }
        $$ = $1;
    }
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

