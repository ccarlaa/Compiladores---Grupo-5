%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/tokens/tokens.h"

// Variável compartilhada com o Bison
extern YYSTYPE yylval;

// Contador de linha para mensagens de erro
int line_number = 1;
%}

%option noyywrap
%option yylineno

/* Padrões básicos necessários para laços */
DIGITO       [0-9]
LETRA        [a-zA-Z]
ID           {LETRA}({LETRA}|{DIGITO})*
NUMERO       {DIGITO}+
ESPACO       [ \t\r]
QUEBRA_LINHA \n

%%

{ESPACO}     { /* Ignora espaços em branco */ }
{QUEBRA_LINHA} { line_number++; }

/* Palavras-chave para laços tradicionais */
"enquanto"   { return C_WHILE; }    /* while */
"para"       { return C_FOR; }      /* for */
"faca"       { return C_DO; }       /* do */
"ate"        { return C_UNTIL; }    /* until */
"repita"     { return C_REPEAT; }   /* repeat */
"paracada"   { return C_FOREACH; }  /* foreach */
"em"         { return C_IN; }       /* in */
"de"         { return C_FROM; }     /* from */
"passo"      { return C_STEP; }     /* step */

/* Palavras-chave para laços funcionais */
"mapear"     { return C_MAP; }      /* map */
"filtrar"    { return C_FILTER; }   /* filter */
"reduzir"    { return C_REDUCE; }   /* reduce */
"dobrar"     { return C_FOLD; }     /* fold */
"aplicar"    { return C_APPLY; }    /* apply */
"para_todos" { return C_FORALL; }   /* forall */
"existe"     { return C_EXISTS; }   /* exists */
"encontrar"  { return C_FIND; }     /* find */
"contar"     { return C_COUNT; }    /* count */
"agrupar"    { return C_GROUP; }    /* group */
"ordenar"    { return C_SORT; }     /* sort */
"inverter"   { return C_REVERSE; }  /* reverse */
"juntar"     { return C_JOIN; }     /* join */
"separar"    { return C_SPLIT; }    /* split */

/* Palavras-chave para laços assíncronos */
"aguardar"   { return C_AWAIT; }    /* await */
"paralelo"   { return C_PARALLEL; } /* parallel */
"concorrente" { return C_CONCURRENT; } /* concurrent */
"sequencial" { return C_SEQUENTIAL; } /* sequential */

/* Identificadores e números */
{ID}         { 
    yylval.string = strdup(yytext);
    return C_IDENTIFIER; 
}
{NUMERO}     { 
    yylval.integer = atoi(yytext);
    return C_NUMBER; 
}

/* Erro para caracteres não reconhecidos */
.            { 
    if (yytext[0] == '@' || yytext[0] == '#' || yytext[0] == '$') {
        printf("Erro léxico na linha %d: Símbolo especial '%s' não permitido em construções de laços.\n", 
               line_number, yytext);
    } else if (strcmp(yytext, "while") == 0) {
        printf("Erro léxico na linha %d: Palavra-chave em inglês '%s' detectada. Use 'enquanto' em vez de 'while'.\n", 
               line_number, yytext);
    } else if (strcmp(yytext, "for") == 0) {
        printf("Erro léxico na linha %d: Palavra-chave em inglês '%s' detectada. Use 'para' em vez de 'for'.\n", 
               line_number, yytext);
    } else if (strcmp(yytext, "do") == 0) {
        printf("Erro léxico na linha %d: Palavra-chave em inglês '%s' detectada. Use 'faca' em vez de 'do'.\n", 
               line_number, yytext);
    } else {
        printf("Erro léxico na linha %d: caractere não reconhecido '%s'. Verifique a sintaxe do seu código de laço.\n", 
               line_number, yytext);
    }
    return -1; /* Retorna código de erro para o parser */
}

%%

/* Função auxiliar para inicializar o analisador léxico */
void init_lexer() {
    line_number = 1;
}