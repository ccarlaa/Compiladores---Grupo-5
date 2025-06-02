%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"
#include "semantic/tabela.h"
#include "semantic/tipos.h"

extern int yylex();
extern char* yytext;
extern FILE* yyin;
extern int yylineno;
void yyerror(const char* s);

AstNode* ast_root = NULL;
TipoSimples tipo_atual;

/* Demarcadores de erros */
int erro_sintatico = 0;
int erro_semantico = 0;

/* Não encerra o parser após erro */
void erro_semantico_msg(const char* msg) {
    fprintf(stderr, "Erro semântico (linha %d): %s\n", yylineno, msg);
    erro_semantico++;
}
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
%token error
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
    : declaracoes { 
        ast_root = $1; 
        if (erro_sintatico == 0 && erro_semantico == 0) {
            printf("Programa analisado com sucesso!\n");
        } else {
            printf("Compilação finalizada com %d erro(s) sintático(s) e %d erro(s) semântico(s).\n", 
                   erro_sintatico, erro_semantico);
        }
    }
    | error {
        yyerror("Erro na estrutura geral do programa");
        $$ = NULL;
    }
    ;

declaracoes
    : declaracao { $$ = $1; }
    | declaracoes declaracao { $$ = $2; }
    | declaracoes error {
        yyerror("Erro em declaração");
        yyerrok;
        $$ = $1; // mantém as declarações anteriores
    }
    ;

declaracao
    : declaracao_variavel { $$ = $1; }
    | declaracao_funcao { $$ = $1; }
    | definicao_funcao { $$ = $1; }
    | declaracao_estrutura { $$ = NULL; }
    | error PONTO_E_VIRGULA {
        yyerror("Declaração com erro - ';'");
        yyerrok;
        $$ = NULL;
    }
    ;

declaracao_variavel
    : tipo IDENTIFICADOR PONTO_E_VIRGULA {
        if (!insere_simbolo($2, tipo_atual)) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Variável '%s' já foi declarada anteriormente", $2);
            erro_semantico_msg(msg);
        }
        $$ = NULL;
    }
    | tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA {
        if (!insere_simbolo($2, tipo_atual)) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Variável '%s' já foi declarada anteriormente", $2);
            erro_semantico_msg(msg);
        } else if ($4 && !verifica_tipo_atribuicao(tipo_atual, $4->tipo)) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Tipos incompatíveis na inicialização da variável '%s'", $2);
            erro_semantico_msg(msg);
        }
        $$ = $4 ? create_equal_node(NULL, $4) : NULL;
        if ($$) $$->tipo = tipo_atual;
    }
    | tipo error PONTO_E_VIRGULA {
        yyerror("Nome de variável esperado após tipo");
        yyerrok;
        $$ = NULL;
    }
    | tipo IDENTIFICADOR error {
        yyerror("';' ou '=' esperado após nome da variável");
        yyerrok;
        $$ = NULL;
    }
    ;

declaracao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN PONTO_E_VIRGULA { $$ = NULL; }
    | tipo IDENTIFICADOR error PONTO_E_VIRGULA {
        yyerror("Parênteses esperados na declaração de função");
        yyerrok;
        $$ = NULL;
    }
    ;

definicao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN bloco_comandos { $$ = $5; }
    | tipo IDENTIFICADOR ABRE_PAREN error FECHA_PAREN bloco_comandos {
        yyerror("Erro na lista de parâmetros da função");
        yyerrok;
        $$ = $6;
    }
    ;

declaracao_estrutura
    : ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA { $$ = NULL; }
    | ESTRUTURA IDENTIFICADOR ABRE_CHAVE error FECHA_CHAVE PONTO_E_VIRGULA {
        yyerror("Erro na declaração de estrutura");
        yyerrok;
        $$ = NULL;
    }
    ;

lista_campos
    : declaracao_campo { $$ = NULL; }
    | lista_campos declaracao_campo { $$ = NULL; }
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
    | ABRE_CHAVE error FECHA_CHAVE {
        yyerror("Erro no bloco de comandos");
        yyerrok;
        $$ = NULL;
    }
    | ABRE_CHAVE comandos error {
        yyerror("'}' esperado para fechar bloco de comandos");
        yyerrok;
        $$ = $2;
    }
    ;

comandos
    : comando { $$ = $1; }
    | comandos comando { $$ = $2; }
    | comandos error {
        yyerror("Erro em comando");
        yyerrok;
        $$ = $1; 
    }
    ;

comando
    : comando_se { $$ = $1; }
    | comando_enquanto { $$ = $1; }
    | comando_retorno { $$ = $1; }
    | bloco_comandos { $$ = $1; }
    | expressao PONTO_E_VIRGULA { $$ = $1; }
    | error PONTO_E_VIRGULA {
        yyerror("Erro em comando - expressão esperada");
        yyerrok;
        $$ = NULL;
    }
    ;

comando_se
    : SE ABRE_PAREN expressao FECHA_PAREN comando %prec IFX { 
        if ($3 && $3->tipo != TIPO_INT) {
            erro_semantico_msg("Condição do 'se' deve ser do tipo inteiro");
        }
        $$ = $3;
    }
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando { 
        if ($3 && $3->tipo != TIPO_INT) {
            erro_semantico_msg("Condição do 'se' deve ser do tipo inteiro");
        }
        $$ = $3;
    }
    | SE ABRE_PAREN error FECHA_PAREN comando {
        yyerror("Erro no comando 'se' - expressão esperada");
        yyerrok;
        $$ = NULL;
    }
    | SE error comando {
        yyerror("Parenteses esperados no comando 'se'");
        yyerrok;
        $$ = NULL;
    }
    ;

comando_enquanto
    : ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando { $$ = $3; }
    | ENQUANTO ABRE_PAREN error FECHA_PAREN comando {
        yyerror("Erro no comando 'enquanto' - expressão inválida");
        yyerrok;
        $$ = NULL;
    }
    ; 

comando_retorno
    : RETORNE expressao PONTO_E_VIRGULA { $$ = $2; }
    | RETORNE PONTO_E_VIRGULA { $$ = NULL; }
    | RETORNE error PONTO_E_VIRGULA {
        yyerror("Erro no comando 'retorne'");
        yyerrok;
        $$ = NULL;
    }
    ;

expressao
    : expressao_atribuicao { $$ = $1; }
    ;

expressao_atribuicao
    : expressao_logica { $$ = $1; }
    | IDENTIFICADOR IGUAL expressao_atribuicao {
        TipoSimples t = busca_simbolo($1);
        if (t == TIPO_INVALIDO) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Variável '%s' não foi declarada", $1);
            erro_semantico_msg(msg);
            $$ = create_equal_node(NULL, $3);
            $$->tipo = TIPO_INT; // assume int para continuar
        } else if ($3 && !verifica_tipo_atribuicao(t, $3->tipo)) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Tipos incompatíveis na atribuição a '%s'", $1);
            erro_semantico_msg(msg);
            $$ = create_equal_node(NULL, $3);
            $$->tipo = t;
        } else {
            $$ = create_equal_node(NULL, $3);
            $$->tipo = t;
        }
    }
    ;

expressao_logica
    : expressao_relacional { $$ = $1; }
    ;

expressao_relacional
    : expressao_aditiva { $$ = $1; }
    | expressao_relacional IGUAL_IGUAL expressao_aditiva {
        if ($1 && $3) {
            TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
            if (t == TIPO_INVALIDO) {
                erro_semantico_msg("Tipos incompatíveis em comparação de igualdade");
            }
        }
        $$ = create_equal_node($1, $3);
        if ($$) $$->tipo = TIPO_INT;
    }
    ;

expressao_aditiva
    : expressao_multiplicativa { $$ = $1; }
    | expressao_aditiva SOMA expressao_multiplicativa {
        if ($1 && $3) {
            TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
            if (t == TIPO_INVALIDO) {
                erro_semantico_msg("Erro na operação de adição - tipos não compatíveis");
                t = TIPO_INT; // recebe int 
            }
        $$ = create_binop_node(OP_ADD, $1, $3);
        $$->tipo = t;
        } else {
            $$ = NULL;
        }
    }
    ;

expressao_multiplicativa
    : expressao_unaria { $$ = $1; }
    | expressao_multiplicativa MULTIPLICACAO expressao_unaria {
        if ($1 && $3) {
            TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
            if (t == TIPO_INVALIDO) {
                erro_semantico_msg("Erro: tipos incompatíveis em multiplicação.\n");
                t = TIPO_INT;
                }
        $$ = create_binop_node(OP_MUL, $1, $3);
        $$->tipo = t;
        } else { 
            $$ = NULL;
        }
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
            char msg[256];
            snprintf(msg, sizeof(msg), "Identificador '%s' não declarado", $1);
            erro_semantico_msg(msg);
            t = TIPO_INT;
        }
        $$ = create_literal_node(0); // placeholder
        $$->tipo = t;
    }
    | ABRE_PAREN expressao FECHA_PAREN { $$ = $2; }
    | ABRE_PAREN error FECHA_PAREN {
        yyerror("Expressão inválida entre parênteses");
        yyerrok;
        $$ = NULL;
    }
    ;

lista_argumentos
    : expressao { $$ = $1; }
    | lista_argumentos VIRGULA expressao { $$ = $3; }
    ;

comando_faca_enquanto
    : FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA {
        if ($5->tipo != TIPO_INT) {
            erro_semantico_msg("Condição do 'faca-enquanto' deve ser do tipo inteiro");
        }
        $$ = $2;
    }
    | FACA comando ENQUANTO ABRE_PAREN error FECHA_PAREN PONTO_E_VIRGULA {
        yyerror("Expressão inválida na condição do 'faca-enquanto'");
        yyerrok;
        $$ = $2;
    }
    ;

comando_para
    : PARA ABRE_PAREN tipo_opcional IDENTIFICADOR IGUAL expressao
      PONTO_E_VIRGULA expressao_condicao PONTO_E_VIRGULA expressao_incremento
      FECHA_PAREN bloco_comandos {
        if (!insere_simbolo($4, tipo_atual)) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Variável '%s' já declarada no escopo do 'para'", $4);
            erro_semantico_msg(msg);
        } else if ($6 && !verifica_tipo_atribuicao(tipo_atual, $6->tipo)) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Tipo incompatível na inicialização de '%s' no 'para'", $4);
            erro_semantico_msg(msg);
        }
        $$ = $12;
    }
    | PARA ABRE_PAREN error FECHA_PAREN bloco_comandos {
        yyerror("Estrutura inválida no cabeçalho do 'para'");
        yyerrok;
        $$ = $5;
    }
    ;

comando_switch
    : ESCOLHA ABRE_PAREN expressao FECHA_PAREN ABRE_CHAVE lista_casos FECHA_CHAVE {
        if ($3->tipo != TIPO_INT) {
            erro_semantico_msg("Erro: expressão do 'switch' deve ser do tipo inteiro.\n");
        }
        $$ = $3;
    }
    | ESCOLHA ABRE_PAREN error FECHA_PAREN ABRE_CHAVE lista_casos FECHA_CHAVE {
        yyerror("Erro na expressão do 'switch'");
        yyerrok;
        $$ = NULL;
    }
    ;

lista_casos
    : lista_casos caso { $$ = $2; }
    | caso { $$ = $1; }
    ;

caso
    : CASO caso_escolha DOIS_PONTOS lista_comandos {
        if ($2 && $2->tipo != TIPO_INT) {
            erro_semantico_msg("Erro: valor do 'caso' deve ser inteiro.\n");
        }
        $$ = $4;
    }
    | PADRAO DOIS_PONTOS lista_comandos { $$ = $3; }
    | CASO caso_escolha DOIS_PONTOS error {
        yyerror("Erro na lista de comandos do 'caso'");
        yyerrok;
        $$ = NULL;
    }
    ;

lista_comandos
    : lista_comandos comando { $$ = $2; }
    | comando { $$ = $1; }
    ;

caso_escolha
    : IDENTIFICADOR {
        TipoSimples t = busca_simbolo($1);
        if (t == TIPO_INVALIDO) {
            char msg[256];
            snprintf(msg, sizeof(msg), "Identificador '%s' usado em 'caso' não foi declarado", $1);
            erro_semantico_msg(msg);
            t = TIPO_INT;
        } else if (t != TIPO_INT) {
            erro_semantico_msg("Expressão 'caso' deve ser do tipo inteiro");
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
    | /* vazio */ { tipo_atual = TIPO_INT; $$ = NULL; }
    ;

expressao_condicao
    : expressao {
        if ($1->tipo != TIPO_INT) {
            erro_semantico_msg("Erro: condição de 'para' deve ser do tipo inteiro.\n");
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

void yyerror(const char* s) {
    fprintf(stderr, "Erro sintático (linha %d): %s\n", yylineno, s);
    if (yytext && strlen(yytext) > 0) {
        fprintf(stderr, "Token problemático: '%s'\n", yytext);
    }
    erro_sintatico++;
}

/* Função principal para análise */
int analisar_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'\n", nome_arquivo);
        return -1;
    }
    
    yyin = arquivo;
    
    // Inicializa contadores
    erro_sintatico = 0;
    erro_semantico = 0;
    
    // Inicia análise
    int resultado = yyparse();
    
    fclose(arquivo);
    
    // Retorna 0 se sucesso, diferente de 0 se houver erros
    return (erro_sintatico > 0 || erro_semantico > 0) ? -1 : 0;
}