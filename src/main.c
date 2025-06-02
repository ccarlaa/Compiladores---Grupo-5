#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast/ast.h"
#include "../parser.tab.h"
#include "semantic/tabela.h"
#include "codegen/codegen.h"
#include "codegen/backend.h"

// Declarações externas do Flex e Bison
extern FILE *yyin;
extern int yyparse(void);
extern int yylex(void);
extern void yyerror(const char *s);
extern char* yytext;
extern AstNode* ast_root; // raiz da AST definida no parser.y

// Ativa o modo de depuração
int yydebug = 1;

// Mapeia tokens para strings (útil para debug)
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

// Função chamada pelo Bison em caso de erro
void yyerror(const char *s) {
    extern int yylineno;
    extern char *yytext;
    fprintf(stderr, "Erro: %s\nLinha: %d, Próximo token: '%s'\n", s, yylineno, yytext);
}

int main(int argc, char **argv) {
    inicializa_tabela();
    int debug_mode = 0;
    int codegen_mode = 0;
    int optimize_mode = 0;
    int backend_mode = 0;
    char *filename = NULL;
    char *output_file = NULL;
    
    // Verificar argumentos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
            debug_mode = 1;
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tac") == 0) {
            codegen_mode = 1;
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--optimize") == 0) {
            optimize_mode = 1;
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--backend") == 0) {
            backend_mode = 1;
        } else if (strcmp(argv[i], "-out") == 0 && i + 1 < argc) {
            output_file = argv[i + 1];
            i++; // Pular o próximo argumento, que é o nome do arquivo
        } else {
            filename = argv[i];
        }
    }
    
    // Entrada via arquivo, se fornecido
    if (filename) {
        FILE *input = fopen(filename, "r");
        if (!input) {
            fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'\n", filename);
            return 1;
        }
        yyin = input;
    } else {
        // Ou entrada padrão (stdin)
        yyin = stdin;
        printf("Digite uma expressão (ex: 3 * 5 = 15):\n");
    }
    
    // Modo de depuração léxica
    if (debug_mode) {
        printf("Modo de depuração ativado - mostrando tokens e erros léxicos\n");
        int token;
        while ((token = yylex()) != 0) {
            if (token == -1) {
                // Erro léxico já foi reportado pelo analisador léxico
                continue;
            } else {
                printf("Token: %d (%s) - Lexema: '%s'\n", token, token_to_string(token), yytext);
            }
        }
        if (filename && yyin != stdin) {
            fclose(yyin);
        }
        return 0;
    }

    // Executa o parser
    int result = yyparse();

    if (result == 0) {
        printf("Programa analisado com sucesso!\n");

        if (ast_root) {
            printf("\n--- Impressão da AST ---\n");
            print_ast(ast_root, 0);

            // Geração de código intermediário
            if (codegen_mode || optimize_mode || backend_mode) {
                printf("\n--- Gerando código intermediário ---\n");
                inicializa_codegen();
                if (gera_codigo_intermediario(ast_root) == 0) {
                    printf("Código intermediário gerado com sucesso!\n");
                    
                    // Mostrar código intermediário se solicitado
                    if (codegen_mode) {
                        printf("\n--- Código Intermediário (TAC) ---\n");
                        imprime_codigo_intermediario(NULL);
                    }
                    
                    // Otimizar código intermediário se solicitado
                    if (optimize_mode) {
                        printf("\n--- Otimizando código intermediário ---\n");
                        if (otimiza_codigo_intermediario() == 0) {
                            printf("Otimização concluída!\n");
                            
                            if (codegen_mode) {
                                printf("\n--- Código Intermediário Otimizado ---\n");
                                imprime_codigo_intermediario(NULL);
                            }
                        } else {
                            printf("Erro durante a otimização do código intermediário.\n");
                        }
                    }
                    
                    // Salvar código intermediário em arquivo se especificado
                    if (output_file && codegen_mode && !backend_mode) {
                        char tac_filename[256];
                        sprintf(tac_filename, "%s.tac", output_file);
                        if (salva_codigo_intermediario(tac_filename) == 0) {
                            printf("Código intermediário salvo em '%s'\n", tac_filename);
                        }
                    }
                    
                    // Gerar código de máquina se solicitado
                    if (backend_mode) {
                        printf("\n--- Gerando código de máquina ---\n");
                        inicializa_backend();
                        if (gera_codigo_maquina() == 0) {
                            printf("Código de máquina gerado com sucesso!\n");
                            
                            // Mostrar código de máquina
                            printf("\n--- Código Assembly ---\n");
                            imprime_codigo_maquina(NULL);
                            
                            // Salvar código de máquina em arquivo executável
                            if (output_file) {
                                if (salva_codigo_maquina(output_file) == 0) {
                                    printf("Código de máquina salvo em '%s'\n", output_file);
                                }
                            }
                            
                            finaliza_backend();
                        } else {
                            printf("Erro durante a geração do código de máquina.\n");
                        }
                    }
                    
                    finaliza_codegen();
                } else {
                    printf("Erro durante a geração do código intermediário.\n");
                }
            } else {
                // Comportamento padrão (apenas avaliação da AST)
                printf("\n--- Avaliação da AST ---\n");
                int resultado = evaluate_ast(ast_root);
                printf("Resultado: %d\n", resultado);
            }

            free_ast(ast_root);
        } else {
            printf("AST não gerada ou vazia.\n");
        }
    } else {
        printf("Erro durante a análise do programa.\n");
    }

    if (argc > 1 && yyin != stdin) {
        fclose(yyin);
    }

    return result;
}
