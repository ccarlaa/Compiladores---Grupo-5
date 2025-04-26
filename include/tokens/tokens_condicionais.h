#ifndef TOKENS_CONDICIONAIS_H
#define TOKENS_CONDICIONAIS_H

/* Tokens para estruturas e operadores condicionais */
#define C_IF 1     /* if */
#define C_ELSE 2   /* else */
#define C_ELSEIF 3 /* else if */
#define C_RETURN 4 /* return */
#define C_AND 5    /* && */
#define C_OR 6     /* || */
#define C_NOT 7    /* ! */
#define C_EQ 8     /* == */
#define C_NEQ 9    /* != */
#define C_GT 10    /* > */
#define C_LT 11    /* < */
#define C_GTE 12   /* >= */
#define C_LTE 13   /* <= */

/* Tokens para identificadores e números */
#define C_IDENTIFIER 14 /* identificador */
#define C_NUMBER 15     /* número */

/* Estrutura para valores semânticos */
typedef union
{
    int integer;
    char *string;
    void *node;
} YYSTYPE;

extern YYSTYPE yylval;

#endif /* TOKENS_CONDICIONAIS_H */
