%{
#include "include/tokens/tokens_condicionais.h"
#include <stdio.h>

/* Variável definida pelo Bison */
extern YYSTYPE yylval;
%}

/* Definições de padrões */
DIGITO      [0-9]
LETRA       [a-zA-Z_]
IDENT       {LETRA}({LETRA}|{DIGITO})*

%%
 // Estrutura
"se"            { printf("TOKEN: Se\n"); return C_IF; }
"senao"         { printf("TOKEN: Senao\n"); return C_ELSE; }
"senao se"      { printf("TOKEN: Senao Se\n"); return C_ELSEIF; }
"retorne"       { printf("TOKEN: Retorne\n"); return C_RETURN; }
"e"             { printf("TOKEN: E\n"); return C_AND; }
"ou"            { printf("TOKEN: Ou\n"); return C_OR; }
"nao"           { printf("TOKEN: Nao\n"); return C_NOT; }
"igual"         { printf("TOKEN: Igual\n"); return C_EQ; }
"diferente"     { printf("TOKEN: Diferente\n"); return C_NEQ; }
"maior"         { printf("TOKEN: Maior\n"); return C_GT; }
"menor"         { printf("TOKEN: Menor\n"); return C_LT; }
"maiorigual"    { printf("TOKEN: Maior Igual\n"); return C_GTE; }
"menorigual"    { printf("TOKEN: Menor Igual\n"); return C_LTE; }

[ \t\r\n]+       { /* Ignorar espaços e quebras de linha */ }

{IDENT}          { printf("TOKEN: Identificador (%s)\n", yytext); return C_IDENTIFIER; }
{DIGITO}+        { printf("TOKEN: Numero (%s)\n", yytext); return C_NUMBER; }

.                { printf("Caractere inválido: %s\n", yytext); }

%%

/* Função principal do Flex */
int yywrap(void) {
    return 1;
}

int main() {
    yylex();
    return 0;
}
