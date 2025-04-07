#include <stdio.h>
#include <stdlib.h>
#include "ast/ast.h"

// Declarações externas do Flex e Bison
extern FILE *yyin;
extern int yyparse(void);
extern int yylex(void);
extern void yyerror(const char *s);

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
    
    // Fecha o arquivo se foi aberto
    if (argc > 1 && yyin != stdin) {
        fclose(yyin);
    }

    return result;
}

// Função chamada pelo Bison em caso de erro
void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}
