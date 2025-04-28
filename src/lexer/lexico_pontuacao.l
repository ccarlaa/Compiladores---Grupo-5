%{
#include "../../include/tokens/tokens_pontuacao.h"
%}

%%

","                      { return PONT_VIRGULA; }
";"                      { return PONT_PONTO_VIRGULA; }
"."                      { return PONT_PONTO; }
"("                      { return PONT_ABRE_PARENTESES; }
")"                      { return PONT_FECHA_PARENTESES; }
"{"                      { return PONT_ABRE_CHAVES; }
"}"                      { return PONT_FECHA_CHAVES; }
"["                      { return PONT_ABRE_COLCHETES; }
"]"                      { return PONT_FECHA_COLCHETES; }

"//".*                   { /* comentário de linha - ignorar */ }
"/*"([^*]|\*+[^*/])*\*+\/ { /* comentário de múltiplas linhas - ignorar */ }

[ \t\n\r]+               { /* ignora espaço, tabulação e quebras de linha */ }

.                        { /* caractere inesperado - erro léxico? */ }

%%

int yywrap(void) {
    return 1;
}

int main() {
    yylex();
   return 0;
 }