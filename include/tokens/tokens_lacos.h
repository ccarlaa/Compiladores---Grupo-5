#ifndef TOKENS_LACOS_H
#define TOKENS_LACOS_H

/* Tokens para laços tradicionais */
#define C_WHILE      1    /* while */
#define C_FOR        2    /* for */
#define C_DO         3    /* do */
#define C_UNTIL      4    /* until */
#define C_REPEAT     5    /* repeat */
#define C_FOREACH    6    /* foreach */
#define C_IN         7    /* in */
#define C_FROM       8    /* from */
#define C_STEP       9    /* step */

/* Tokens para laços funcionais */
#define C_MAP        10   /* map */
#define C_FILTER     11   /* filter */
#define C_REDUCE     12   /* reduce */
#define C_FOLD       13   /* fold */
#define C_APPLY      14   /* apply */
#define C_FORALL     15   /* forall */
#define C_EXISTS     16   /* exists */
#define C_FIND       17   /* find */
#define C_COUNT      18   /* count */
#define C_GROUP      19   /* group */
#define C_SORT       20   /* sort */
#define C_REVERSE    21   /* reverse */
#define C_JOIN       22   /* join */
#define C_SPLIT      23   /* split */

/* Tokens para laços assíncronos */
#define C_AWAIT      24   /* await */
#define C_PARALLEL   25   /* parallel */
#define C_CONCURRENT 26   /* concurrent */
#define C_SEQUENTIAL 27   /* sequential */

/* Tokens para identificadores e números */
#define C_IDENTIFIER 33   /* identificador */
#define C_NUMBER     34   /* número */

/* Estrutura para valores semânticos */
typedef union {
    int integer;
    char* string;
    void* node;
} YYSTYPE;

extern YYSTYPE yylval;

#endif /* TOKENS_LACOS_H */ 