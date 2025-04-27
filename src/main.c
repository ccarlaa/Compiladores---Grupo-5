#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"
#include "../parser.tab.h"

// Declarações externas do Flex e Bison
extern FILE *yyin;
extern int yyparse(void);
extern int yylex(void);
extern void yyerror(const char *s);
extern char* yytext;

// Variável para ativar o modo de depuração
int yydebug = 1;

// Função para converter tokens em strings para depuração
const char* token_to_string(int token) {
    switch(token) {
        case NUMERO: return "NUMERO";
        case SOMA: return "SOMA";
        case SUBTRACAO: return "SUBTRACAO";
        case MULTIPLICACAO: return "MULTIPLICACAO";
        case DIVISAO: return "DIVISAO";
        case MODULO: return "MODULO";
        case IGUAL: return "IGUAL";
        case ABRE_PAREN: return "ABRE_PAREN";
        case FECHA_PAREN: return "FECHA_PAREN";
        case TIPO_INTEIRO: return "TIPO_INTEIRO";
        case TIPO_REAL: return "TIPO_REAL";
        case TIPO_DUPLO: return "TIPO_DUPLO";
        case TIPO_CARACTERE: return "TIPO_CARACTERE";
        case TIPO_VAZIO: return "TIPO_VAZIO";
        case TIPO_LONGO: return "TIPO_LONGO";
        case TIPO_CURTO: return "TIPO_CURTO";
        case TIPO_SEM_SINAL: return "TIPO_SEM_SINAL";
        case TIPO_COM_SINAL: return "TIPO_COM_SINAL";
        case SE: return "SE";
        case SENAO: return "SENAO";
        case ENQUANTO: return "ENQUANTO";
        case PARA: return "PARA";
        case FACA: return "FACA";
        case RETORNE: return "RETORNE";
        case QUEBRA: return "QUEBRA";
        case CONTINUE: return "CONTINUE";
        case ESTRUTURA: return "ESTRUTURA";
        case UNIAO: return "UNIAO";
        case ENUM: return "ENUM";
        case CONST: return "CONST";
        case ESTATICO: return "ESTATICO";
        case EXTERNO: return "EXTERNO";
        case REGISTRO: return "REGISTRO";
        case TYPEDEF: return "TYPEDEF";
        case IGUAL_IGUAL: return "IGUAL_IGUAL";
        case DIFERENTE: return "DIFERENTE";
        case MENOR: return "MENOR";
        case MAIOR: return "MAIOR";
        case MENOR_IGUAL: return "MENOR_IGUAL";
        case MAIOR_IGUAL: return "MAIOR_IGUAL";
        case E_LOGICO: return "E_LOGICO";
        case OU_LOGICO: return "OU_LOGICO";
        case NAO_LOGICO: return "NAO_LOGICO";
        case IDENTIFICADOR: return "IDENTIFICADOR";
        case LITERAL_STRING: return "LITERAL_STRING";
        case LITERAL_CHAR: return "LITERAL_CHAR";
        case ABRE_CHAVE: return "ABRE_CHAVE";
        case FECHA_CHAVE: return "FECHA_CHAVE";
        case ABRE_COLCHETE: return "ABRE_COLCHETE";
        case FECHA_COLCHETE: return "FECHA_COLCHETE";
        case PONTO_E_VIRGULA: return "PONTO_E_VIRGULA";
        case VIRGULA: return "VIRGULA";
        case PONTO: return "PONTO";
        case DOIS_PONTOS: return "DOIS_PONTOS";
        case INCREMENTO: return "INCREMENTO";
        case DECREMENTO: return "DECREMENTO";
        case MAIS_IGUAL: return "MAIS_IGUAL";
        case MENOS_IGUAL: return "MENOS_IGUAL";
        case MULT_IGUAL: return "MULT_IGUAL";
        case DIV_IGUAL: return "DIV_IGUAL";
        case PRINCIPAL: return "PRINCIPAL";
        default: return "TOKEN_DESCONHECIDO";
    }
}

int main(int argc, char **argv) {
    // Se um arquivo foi fornecido como argumento
    if (argc > 1) {
        FILE *input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'\n", argv[1]);
            return 1;
        }
        yyin = input;
    } else {
        // Caso contrário, usa a entrada padrão
        yyin = stdin;
        printf("Digite uma expressão (ex: 3*5 = 15):\n");
    }

    // Inicia a análise sintática
    int result = yyparse();
    
    if (result == 0) {
        printf("Programa analisado com sucesso!\n");
    } else {
        printf("Erro durante a análise do programa.\n");
    }
    
    // Fecha o arquivo se foi aberto
    if (argc > 1 && yyin != stdin) {
        fclose(yyin);
    }

    return result;
}

// Função chamada pelo Bison em caso de erro
void yyerror(const char *s) {
    extern int yylineno;
    extern char *yytext;
    fprintf(stderr, "Erro: %s\nLinha: %d, Próximo token: '%s'\n", s, yylineno, yytext);
}
