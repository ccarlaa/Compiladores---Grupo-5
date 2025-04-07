#ifndef TOKENS_H
#define TOKENS_H

/* Definição dos tokens para operações aritméticas básicas */
#define NUMERO      1000
#define SOMA        1001
#define SUBTRACAO   1002
#define MULTIPLICACAO 1003
#define DIVISAO     1004
#define IGUAL       1005
#define ABRE_PAREN  1006
#define FECHA_PAREN 1007

/* União para armazenar valores associados a tokens */
typedef union {
    int ival;       /* Para números inteiros */
    double dval;    /* Para números de ponto flutuante (para uso futuro) */
} YYSTYPE;

extern YYSTYPE yylval;

#endif /* TOKENS_H */
