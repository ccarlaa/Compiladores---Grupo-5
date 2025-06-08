%{
    /* Cabeçalhos C comuns */
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast/ast.h"
    #include "semantic/tabela.h"
    #include "semantic/tipos.h"

    /* Interface com o Flex */
    extern int   yylex(void);
    extern char* yytext;
    void yyerror(const char *s);

    /* Raiz da AST */
    AstNode* ast_root = NULL;
    /* Tipo corrente (auxílio à análise semântica) */
    TipoSimples tipo_atual;
%}

%token TIPO_INTEIRO  TIPO_REAL  TIPO_DUPLO  TIPO_CARACTERE  TIPO_VAZIO
%token TIPO_LONGO    TIPO_CURTO TIPO_SEM_SINAL TIPO_COM_SINAL
%token TIPO_BOOLEANO TIPO_COMPLEXO TIPO_IMAGINARIO
%token TIPO_DECIMAL32 TIPO_DECIMAL64 TIPO_DECIMAL128 TIPO_INT128

%token CONST VOLATIL INLINE RESTRICT TYPEDEF AUTO REGISTRO ESTATICO EXTERNO
%token ATOMICO NAO_RETORNA THREAD_LOCAL ALIGNAS ALIGNOF GENERICO ASSERT_ESTATICO

%token SE SENAO ENQUANTO PARA FACA RETORNE QUEBRA CONTINUE
%token ESCOLHA CASO PADRAO GOTO

%token ESTRUTURA UNIAO ENUM

%token MAIS_IGUAL MENOS_IGUAL MULT_IGUAL DIV_IGUAL MOD_IGUAL
%token E_BIT_IGUAL OU_BIT_IGUAL XOR_IGUAL SHIFT_ESQ_IGUAL SHIFT_DIR_IGUAL
%token INCREMENTO DECREMENTO

%token IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%token E_LOGICO OU_LOGICO NAO_LOGICO

%token SOMA SUBTRACAO MULTIPLICACAO DIVISAO MODULO
%token SHIFT_ESQ SHIFT_DIR E_BIT OU_BIT XOR COMPLEMENTO
%token SETA PONTO SIZEOF INTERROGACAO RETICENCIAS

%token IGUAL
%token ABRE_PAREN FECHA_PAREN ABRE_CHAVE FECHA_CHAVE ABRE_COLCHETE FECHA_COLCHETE
%token PONTO_E_VIRGULA VIRGULA DOIS_PONTOS

%token IDENTIFICADOR NUMERO LITERAL_STRING LITERAL_CHAR

%token UNTIL REPITA PARA_CADA EM DE PASSO
%token MAPEAR FILTRAR REDUZIR DOBRAR APLICAR PARA_TODOS EXISTE ENCONTRAR CONTAR
%token AGRUPAR ORDENAR INVERTER JUNTAR SEPARAR
%token AGUARDAR PARALELO CONCORRENTE SEQUENCIAL

%token ASM TYPEOF ATRIBUTO

%left ORDENAR 
%left SOMA SUBTRACAO
%left MULTIPLICACAO DIVISAO MODULO
%right NAO_LOGICO

%union {
    int       ival;
    float     fval;
    char*     sval;
    AstNode*  node;
}

%type <ival> NUMERO
%type <sval> IDENTIFICADOR LITERAL_STRING LITERAL_CHAR
%type <node> programa declaracoes declaracao declaracao_variavel declaracao_funcao 
             definicao_funcao declaracao_estrutura lista_campos declaracao_campo 
             tipo bloco_comandos comandos comando comando_se comando_enquanto 
             comando_para comando_faca_enquanto comando_switch lista_argumentos 
             lista_casos caso lista_comandos caso_escolha expressao 
             expressao_atribuicao expressao_logica expressao_relacional 
             expressao_aditiva expressao_multiplicativa expressao_unaria 
             expressao_primaria expressao_inicializacao expressao_condicao 
             expressao_incremento tipo_opcional 
             laco_ext bloco_ext

%%

/* ----------- PROGRAMA ----------- */
programa
    : declaracoes                           { ast_root = $1; }
    ;

/* ----------- DECLARAÇÕES DE TOPO ----------- */
declaracoes
    : declaracao
    | declaracoes declaracao
    ;

declaracao
    : declaracao_variavel
    | declaracao_funcao
    | definicao_funcao
    | declaracao_estrutura
    ;

/* ----------- VARIÁVEIS ----------- */
declaracao_variavel
    : tipo IDENTIFICADOR PONTO_E_VIRGULA
        {
            if (!insere_simbolo($2, tipo_atual))
                yyerror("variável redeclarada");
        }
    | tipo IDENTIFICADOR IGUAL expressao PONTO_E_VIRGULA
        {
            if (!insere_simbolo($2, tipo_atual))
                yyerror("variável redeclarada");
            if (!verifica_tipo_atribuicao(tipo_atual, $4->tipo))
                yyerror("atribuição incompatível");
            $$ = create_equal_node(NULL, $4); $$->tipo = tipo_atual;
        }
    ;

/* ----------- FUNÇÕES ----------- */
declaracao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN PONTO_E_VIRGULA
    ;

definicao_funcao
    : tipo IDENTIFICADOR ABRE_PAREN FECHA_PAREN bloco_comandos
        { $$ = $5; }
    ;

/* ----------- ESTRUTURA ----------- */
declaracao_estrutura
    : ESTRUTURA IDENTIFICADOR ABRE_CHAVE lista_campos FECHA_CHAVE PONTO_E_VIRGULA
    ;

lista_campos
    : declaracao_campo
    | lista_campos declaracao_campo
    ;

declaracao_campo
    : tipo IDENTIFICADOR PONTO_E_VIRGULA
    ;

/* ----------- TIPOS BÁSICOS ----------- */
tipo
    : TIPO_INTEIRO      { tipo_atual = TIPO_INT;   }
    | TIPO_REAL         { tipo_atual = TIPO_REAL_; }
    | TIPO_DUPLO        { tipo_atual = TIPO_DUPLO_; }
    | TIPO_CARACTERE    { tipo_atual = TIPO_CHAR;  }
    ;

/* ----------- BLOCO / COMANDOS ----------- */
bloco_comandos
    : ABRE_CHAVE comandos FECHA_CHAVE      { $$ = $2; }
    | ABRE_CHAVE FECHA_CHAVE               { $$ = NULL; }
    ;

comandos
    : /* vazio */                          { $$ = NULL; }
    | comandos comando                     { $$ = $2; }
    ;

comando
    : comando_se
    | comando_enquanto
    | comando_para
    | comando_faca_enquanto
    | comando_switch
    | comando_retorno
    | bloco_comandos
    | expressao PONTO_E_VIRGULA
    ;

/* ----------- if / else ----------- */
comando_se
    : SE ABRE_PAREN expressao FECHA_PAREN comando %prec SE
    | SE ABRE_PAREN expressao FECHA_PAREN comando SENAO comando
    ;

/* ----------- while ----------- */
comando_enquanto
    : ENQUANTO ABRE_PAREN expressao FECHA_PAREN comando
    ;

/* ----------- for ----------- */
comando_para
    : PARA ABRE_PAREN tipo_opcional IDENTIFICADOR IGUAL expressao
      PONTO_E_VIRGULA expressao_condicao PONTO_E_VIRGULA expressao_incremento
      FECHA_PAREN bloco_comandos
        {
            if (!insere_simbolo($4, tipo_atual)) yyerror("var do 'for' redeclarada");
            if (!verifica_tipo_atribuicao(tipo_atual, $6->tipo))
                yyerror("tipo incompatível no 'for'");
            if ($8 && $8->tipo != TIPO_INT)
                yyerror("condição do 'for' não inteira");
            $$ = $12;
        }
    ;

/* ----------- do … while ----------- */
comando_faca_enquanto
    : FACA comando ENQUANTO ABRE_PAREN expressao FECHA_PAREN PONTO_E_VIRGULA
        {
            if ($5->tipo != TIPO_INT) yyerror("condição do 'do-while' deve ser inteira");
            $$ = $2;
        }
    ;

/* ----------- switch / case ----------- */
comando_switch
    : ESCOLHA ABRE_PAREN expressao FECHA_PAREN ABRE_CHAVE lista_casos FECHA_CHAVE
        {
            if ($3->tipo != TIPO_INT) yyerror("'switch' exige expressão inteira");
        }
    ;

lista_casos
    : /* vazio */
    | lista_casos caso
    ;

caso
    : CASO caso_escolha DOIS_PONTOS lista_comandos
        {
            if ($2 && $2->tipo != TIPO_INT) yyerror("'case' exige inteiro");
            $$ = $4;
        }
    | PADRAO DOIS_PONTOS lista_comandos
    ;

caso_escolha
    : IDENTIFICADOR
        {
            TipoSimples t = busca_simbolo($1);
            if (t != TIPO_INT) yyerror("'case' requer inteiro");
            $$ = create_literal_node(0); $$->tipo = t;
        }
    | NUMERO                 { $$ = create_literal_node($1); $$->tipo = TIPO_INT; }
    ;

/* ----------- return ----------- */
comando_retorno
    : RETORNE expressao_opt PONTO_E_VIRGULA
        { $$ = $2; }
    ;

expressao_opt
    : expressao
    | /* vazio */           { $$ = NULL; }
    ;

/* ----------- EXPRESSÕES ----------- */
expressao
    : expressao_atribuicao
    ;

expressao_atribuicao
    : expressao_logica
    | IDENTIFICADOR IGUAL expressao_atribuicao
        {
            TipoSimples t = busca_simbolo($1);
            if (!verifica_tipo_atribuicao(t, $3->tipo)) yyerror("tipos incompatíveis");
            $$ = create_equal_node(NULL, $3); $$->tipo = t;
        }
    ;

expressao_logica
    : expressao_relacional
    ;

expressao_relacional
    : expressao_aditiva
    | expressao_relacional IGUAL_IGUAL expressao_aditiva
        {
            verifica_tipo_binario($1->tipo, $3->tipo);
            $$ = create_equal_node($1, $3); $$->tipo = TIPO_INT;
        }
    ;

expressao_aditiva
    : expressao_multiplicativa
    | expressao_aditiva SOMA expressao_multiplicativa
        {
            TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
            $$ = create_binop_node(OP_ADD, $1, $3); $$->tipo = t;
        }
    ;

expressao_multiplicativa
    : expressao_unaria
    | expressao_multiplicativa MULTIPLICACAO expressao_unaria
        {
            TipoSimples t = verifica_tipo_binario($1->tipo, $3->tipo);
            $$ = create_binop_node(OP_MUL, $1, $3); $$->tipo = t;
        }
    ;

expressao_unaria
    : expressao_primaria
    ;

expressao_primaria
    : NUMERO                 { $$ = create_literal_node($1); $$->tipo = TIPO_INT; }
    | IDENTIFICADOR
        {
            TipoSimples t = busca_simbolo($1);
            if (t == TIPO_INVALIDO) yyerror("identificador não declarado");
            $$ = create_literal_node(0); $$->tipo = t; /* placeholder */
        }
    | ABRE_PAREN expressao FECHA_PAREN   { $$ = $2; }
    ;

/* ----------- utilidades para 'for' ----------- */
tipo_opcional
    : tipo
    | /* vazio */
    ;

expressao_condicao
    : expressao                { $$ = $1; }
    | /* vazio */              { $$ = NULL; }
    ;

expressao_incremento
    : expressao
    | /* vazio */              { $$ = NULL; }
    ;

/* ------------------------ LAÇOS AVANÇADOS -------------------------- */
laco_ext
    /* foreach */
    : PARA_CADA ABRE_PAREN IDENTIFICADOR EM expressao FECHA_PAREN bloco_comandos
        { $$ = create_foreach_node($3, $5, $7); }

    /* repeat … until */
    | REPITA bloco_comandos UNTIL ABRE_PAREN expressao FECHA_PAREN
        { $$ = create_repeat_until_node($2, $5); }

    /* until (forma curta) */
    | UNTIL ABRE_PAREN expressao FECHA_PAREN bloco_comandos
        { $$ = create_until_node($3, $5); }

    /* map/filter/reduce/etc. */
    | MAPEAR   ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_map_node($3,$5); }
    | FILTRAR  ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_filter_node($3,$5); }
    | REDUZIR  ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_reduce_node($3,$5); }
    | DOBRAR   ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_fold_node($3,$5); }
    | APLICAR  ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_apply_node($3,$5); }
    | PARA_TODOS ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_forall_node($3,$5); }
    | EXISTE   ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_exists_node($3,$5); }
    | ENCONTRAR ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_find_node($3,$5); }
    | CONTAR   ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_count_node($3,$5); }
    | AGRUPAR  ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_group_node($3,$5); }
    | ORDENAR  ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_sort_node($3,$5); }
    | INVERTER ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_reverse_node($3,$5); }
    | JUNTAR   ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_join_node($3,$5); }
    | SEPARAR  ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_split_node($3,$5); }

    /* async / paralelo / concorrente */
    | AGUARDAR   ABRE_PAREN expressao FECHA_PAREN bloco_comandos { $$ = create_await_node($3,$5); }
    | PARALELO   bloco_comandos                                 { $$ = create_parallel_node($2); }
    | CONCORRENTE bloco_comandos                                { $$ = create_concurrent_node($2); }
    | SEQUENCIAL bloco_comandos                                 { $$ = create_sequential_node($2); }
    ;

%%

/* ------------------- ROTINA DE ERRO PADRONIZADA ------------------- */
void yyerror(const char *s)
{
    fprintf(stderr, "Erro de sintaxe (token '%s'): %s\n", yytext, s);
}