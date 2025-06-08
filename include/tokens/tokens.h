#ifndef TOKENS_H
#define TOKENS_H

/* Incluir as definições geradas pelo Bison */
#include "parser.tab.h"

/* Não precisamos definir os tokens aqui, pois o Bison já os define */

/* Histórico dos tokens */
/* Tokens para tipos de dados */
/*    #define TIPO_REAL 01       float */
/*    #define TIPO_DUPLO 02      double */
/*    #define TIPO_CARACTERE 03  char */
/*    #define TIPO_VAZIO 04      void */
/*    #define TIPO_LONGO 05      long */
/*    #define TIPO_CURTO 06      short */
/*    #define TIPO_SEM_SINAL 07  unsigned */
/*    #define TIPO_COM_SINAL 08  signed */
/*    #define TIPO_INTEIRO 09    int */

/* Tokens para estruturas de controle */
/*    #define SE 10       /* if */
/*    #define SENAO 11    /* else */
/*    #define ENQUANTO 12 /* while */
/*    #define PARA 13     /* for */
/*    #define FACA 14     /* do */
/*    #define RETORNE 15  /* return */
/*    #define QUEBRA 16   /* break */
/*    #define CONTINUE 17 /* continue */
/*    #define ESCOLHA 18  /* switch */
/*    #define CASO 19     /* case */
/*    #define PADRAO 20   /* default */
/*
/*    /* Tokens para declarações */
/*    #define UNIAO 21     /* union */
/*    #define ENUM 22      /* enum */
/*    #define CONST 23     /* const */
/*    #define ESTATICO 24  /* static */
/*    #define EXTERNO 25   /* extern */
/*    #define REGISTRO 26  /* register */
/*    #define TYPEDEF 27   /* typedef */
/*    #define ESTRUTURA 28 /* struct */
/*
/*    /* Tokens para operadores */
/*    #define MAIS_IGUAL 29    /* += */
/*    #define MENOS_IGUAL 30   /* -= */
/*    #define MULT_IGUAL 31    /* *= */
/*    #define DIV_IGUAL 32     /* /= */
/*    #define INCREMENTO 33    /* ++ */
/*    #define DECREMENTO 34    /* -- */
/*    #define IGUAL_IGUAL 35   /* == */
/*    #define DIFERENTE 36     /* != */
/*    #define MENOR 37         /* < */
/*    #define MAIOR 38         /* > */
/*    #define MENOR_IGUAL 39   /* <= */
/*    #define MAIOR_IGUAL 40   /* >= */
/*    #define E_LOGICO 41      /* && */
/*    #define OU_LOGICO 42     /* || */
/*    #define NAO_LOGICO 43    /* ! */
/*    #define SOMA 44          /* + */
/*    #define SUBTRACAO 45     /* - */
/*    #define MULTIPLICACAO 46 /* * */
/*    #define DIVISAO 47       /* / */
/*    #define MODULO 48        /* % */
/*    #define IGUAL 49         /* = */
/*
/*    /* Tokens para pontuação */
/*    #define ABRE_PAREN 50      /* ( */
/*    #define FECHA_PAREN 51     /* ) */
/*    #define ABRE_CHAVE 52      /* { */
/*    #define FECHA_CHAVE 53     /* } */
/*    #define ABRE_COLCHETE 54   /* [ */
/*    #define FECHA_COLCHETE 55  /* ] */
/*    #define PONTO_E_VIRGULA 56 /* ; */
/*    #define VIRGULA 57         /* , */
/*    #define PONTO 58           /* . */
/*    #define DOIS_PONTOS 59     /* : */
/*
/*    /* Tokens para identificadores e literais */
/*    #define IDENTIFICADOR 60  /* identificadores */
/*    #define NUMERO 61         /* literais inteiros */
/*    #define LITERAL_STRING 62 /* strings entre aspas duplas */
/*    #define LITERAL_CHAR 63   /* caracteres entre aspas simples */
/*
/*    /* Estrutura para valores semânticos */
/*    typedef union
/*    {
/*        int integer;
/*        char *string;
/*        void *node;
/*    } YYSTYPE;

    extern YYSTYPE yylval;





#ifndef TOKENS_LACOS_H
/* #define TOKENS_LACOS_H
/*
/* /* Tokens para laços tradicionais */
/* #define C_WHILE 1   /* while */
/* #define C_FOR 2     /* for */
/* #define C_DO 3      /* do */
/* #define C_UNTIL 4   /* until */
/* #define C_REPEAT 5  /* repeat */
/* #define C_FOREACH 6 /* foreach */
/* #define C_IN 7      /* in */
/* #define C_FROM 8    /* from */
/* #define C_STEP 9    /* step */
/*
/* /* Tokens para laços funcionais */
/* #define C_MAP 10     /* map */
/* #define C_FILTER 11  /* filter */
/* #define C_REDUCE 12  /* reduce */
/* #define C_FOLD 13    /* fold */
/* #define C_APPLY 14   /* apply */
/* #define C_FORALL 15  /* forall */
/* #define C_EXISTS 16  /* exists */
/* #define C_FIND 17    /* find */
/* #define C_COUNT 18   /* count */
/* #define C_GROUP 19   /* group */
/* #define C_SORT 20    /* sort */
/* #define C_REVERSE 21 /* reverse */
/* #define C_JOIN 22    /* join */
/* #define C_SPLIT 23   /* split */
/*
/* /* Tokens para laços assíncronos */
/* #define C_AWAIT 24      /* await */
/* #define C_PARALLEL 25   /* parallel */
/* #define C_CONCURRENT 26 /* concurrent */
/* #define C_SEQUENTIAL 27 /* sequential */
/*
/* /* Tokens para identificadores e números */
/* #define C_IDENTIFIER 33 /* identificador */
/* #define C_NUMBER 34     /* número */

/* Estrutura para valores semânticos */
/* typedef union
{
    int integer;
    char *string;
    void *node;
} YYSTYPE;

extern YYSTYPE yylval;

#endif /* TOKENS_LACOS_H */

#endif /* TOKENS_H */
