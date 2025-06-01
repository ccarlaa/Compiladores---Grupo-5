%{
#include <stdio.h>
#include "tokens_pontuacao.h"

// Contador de linha para mensagens de erro
int linha_atual = 1;
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

[ \t\r]+                { /* ignora espaço, tabulação e retorno de carro */ }
\n                      { linha_atual++; /* incrementa o contador de linha */ }

.                        {
                            if (yytext[0] == '`' || yytext[0] == '~' || yytext[0] == '|') {
                                fprintf(stderr, "Erro léxico (linha %d): Símbolo de pontuação inválido '%s'. Este símbolo não é suportado na linguagem.\n", linha_atual, yytext);
                            } else if (yytext[0] == ':' || yytext[0] == '?' || yytext[0] == '!') {
                                fprintf(stderr, "Erro léxico (linha %d): Pontuação '%s' não implementada. Considere usar ';' para finalizar comandos.\n", linha_atual, yytext);
                            } else if (yytext[0] == '<' || yytext[0] == '>' || yytext[0] == '=' || yytext[0] == '+' || yytext[0] == '-' || yytext[0] == '*' || yytext[0] == '/') {
                                fprintf(stderr, "Erro léxico (linha %d): Operador '%s' encontrado no analisador de pontuação. Operadores devem ser processados pelo analisador principal.\n", linha_atual, yytext);
                            } else {
                                fprintf(stderr, "Erro léxico (linha %d): Caractere inesperado '%s' no analisador de pontuação.\n", linha_atual, yytext);
                            }
                            return -1; /* Retorna código de erro */
                        }

%%

int yywrap(void) {
    return 1;
}

int main() {
    yylex();
   return 0;
 }