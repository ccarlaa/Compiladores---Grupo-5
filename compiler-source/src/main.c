#include <stdio.h>

// Declarações para funções geradas pelo Flex e Bison
extern int yyparse(void);
extern FILE *yyin;

int main(int argc, char **argv) {
    // Verifica se um nome de arquivo foi passado como argumento
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Nao foi possivel abrir o arquivo");
            return 1;
        }
        // Aponta a entrada do Flex (yyin) para o arquivo
        yyin = file;
    } else {
        // Se nenhum arquivo for fornecido, usa a entrada padrão (teclado)
        yyin = stdin;
    }

    // Inicia a análise sintática
    yyparse();

    // Se um arquivo foi aberto, fecha ele
    if (argc > 1 && yyin) {
        fclose(yyin);
    }

    return 0;
}
