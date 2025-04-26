#ifndef TOKENS_switch_H
#define TOKENS_switch_H

/* Tokens para estruturas switch-case */
#define C_SWITCH    1   /* switch */
#define C_CASE      2   /* case */
#define C_DEFAULT   3   /* default */
#define C_BREAK     4   /* break */

/* Tokens para símbolos e pontuação */
#define C_LBRACE    5   /* { */
#define C_RBRACE    6   /* } */
#define C_LPAREN    7   /* ( */
#define C_RPAREN    8   /* ) */
#define C_COLON     9   /* : */
#define C_SEMICOLON 10  /* ; */

/* Tokens para identificadores e valores */
#define C_IDENTIFIER 11 /* identificador */
#define C_NUMBER      12 /* número */

/* Estrutura para valores semânticos */
typedef union {
    int integer; /* Guarda valores inteiros */
    char* string; /* Guarda strings */
    void* node; /* Guarda ponteiros */
} YYSTYPE;

extern YYSTYPE yylval;

#endif /* TOKENS_H */
