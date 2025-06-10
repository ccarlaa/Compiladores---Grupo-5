/*
 * TRADUTOR C PARA PORTUGOL
 * Programa principal que converte código C em código Portugol
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Estrutura para mapear tokens C para Portugol
typedef struct {
    const char* c_token;
    const char* portugol_token;
} translation_pair;

// Tabela de traduções C -> Portugol
translation_pair translations[] = {
    {"int", "inteiro"},
    {"float", "real"},
    {"double", "duplo"},
    {"char", "caractere"},
    {"void", "vazio"},
    {"main", "principal"},
    {"if", "se"},
    {"else", "senao"},
    {"while", "enquanto"},
    {"for", "para"},
    {"return", "retorne"},
    {"break", "quebra"},
    {"continue", "continue"},
    {"#include", "#inclua"},
    {"printf", "escreva"},
    {"scanf", "leia"},
    {NULL, NULL}
};

const char* translate_word(const char* word) {
    for (int i = 0; translations[i].c_token != NULL; i++) {
        if (strcmp(word, translations[i].c_token) == 0) {
            return translations[i].portugol_token;
        }
    }
    return word;
}

int manual_translate(const char* input_file, const char* output_file) {
    FILE* input = fopen(input_file, "r");
    FILE* output;
    
    if (!input) {
        printf("Erro: Não foi possível abrir o arquivo de entrada '%s'\n", input_file);
        return 1;
    }
    
    if (output_file) {
        output = fopen(output_file, "w");
        if (!output) {
            printf("Erro: Não foi possível criar o arquivo de saída '%s'\n", output_file);
            fclose(input);
            return 1;
        }
    } else {
        output = stdout;
    }
    
    char ch;
    char word[256];
    int word_index = 0;
    int in_string = 0;
    int in_comment = 0;
    int in_line_comment = 0;
    char prev_ch = '\0';
    
    while ((ch = fgetc(input)) != EOF) {
        // Handle string literals
        if (ch == '"' && prev_ch != '\\') {
            in_string = !in_string;
            if (word_index > 0) {
                word[word_index] = '\0';
                if (!in_string && !in_comment && !in_line_comment) {
                    fprintf(output, "%s", translate_word(word));
                } else {
                    fprintf(output, "%s", word);
                }
                word_index = 0;
            }
            fputc(ch, output);
        }
        // Handle line comments
        else if (ch == '/' && prev_ch == '/' && !in_string) {
            in_line_comment = 1;
            fputc(ch, output);
        }
        // Handle multi-line comments start
        else if (ch == '*' && prev_ch == '/' && !in_string) {
            in_comment = 1;
            fputc(ch, output);
        }
        // Handle multi-line comments end
        else if (ch == '/' && prev_ch == '*' && in_comment) {
            in_comment = 0;
            fputc(ch, output);
        }
        // Handle newlines (end line comments)
        else if (ch == '\n') {
            if (word_index > 0) {
                word[word_index] = '\0';
                if (!in_string && !in_comment && !in_line_comment) {
                    fprintf(output, "%s", translate_word(word));
                } else {
                    fprintf(output, "%s", word);
                }
                word_index = 0;
            }
            in_line_comment = 0;
            fputc(ch, output);
        }
        // Handle word separators
        else if (isspace(ch) || ispunct(ch)) {
            if (word_index > 0) {
                word[word_index] = '\0';
                if (!in_string && !in_comment && !in_line_comment) {
                    fprintf(output, "%s", translate_word(word));
                } else {
                    fprintf(output, "%s", word);
                }
                word_index = 0;
            }
            fputc(ch, output);
        }
        // Build word character by character
        else {
            if (word_index < 255) {
                word[word_index++] = ch;
            }
        }
        
        prev_ch = ch;
    }
    
    // Handle last word if any
    if (word_index > 0) {
        word[word_index] = '\0';
        if (!in_string && !in_comment && !in_line_comment) {
            fprintf(output, "%s", translate_word(word));
        } else {
            fprintf(output, "%s", word);
        }
    }
    
    fclose(input);
    if (output != stdout) {
        fclose(output);
    }
    
    return 0;
}

// Declarações externas do parser/lexer (modo completo com flex/bison)
#ifndef MANUAL_MODE
extern FILE* yyin;
extern FILE* yyout;
extern int yyparse(void);
extern int yylex_destroy(void);
#endif

void print_help() {
    printf("=== TRADUTOR C PARA PORTUGOL ===\n");
    printf("Converte código C em código Portugol\n\n");
    printf("Uso: compilador [opções] <arquivo_entrada>\n\n");
    printf("Opções:\n");
    printf("  -o <arquivo>    Especifica o arquivo de saída\n");
    printf("  -h, --help      Mostra esta ajuda\n");
    printf("  --manual        Força modo manual (sem flex/bison)\n\n");
    printf("Exemplos:\n");
    printf("  compilador programa.c -o programa.ptg\n");
    printf("  compilador teste.c --manual\n");
    printf("  compilador exemplo.c (saída: stdout)\n\n");
    printf("Modo atual: ");
#ifdef MANUAL_MODE
    printf("Manual (sem flex/bison)\n");
#else
    printf("Completo (com flex/bison)\n");
#endif
}

int main(int argc, char** argv) {
    printf("=== TRADUTOR C PARA PORTUGOL ===\n");
    printf("Versão 2.0 - Compiladores UnB\n\n");
    
    char* input_file = NULL;
    char* output_file = NULL;
    int force_manual = 0;
    
    // Processar argumentos da linha de comando
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                fprintf(stderr, "Erro: opção -o requer um argumento\n");
                return 1;
            }
        } else if (strcmp(argv[i], "--manual") == 0) {
            force_manual = 1;
        } else if (argv[i][0] != '-') {
            input_file = argv[i];
        } else {
            fprintf(stderr, "Erro: opção desconhecida '%s'\n", argv[i]);
            print_help();
            return 1;
        }
    }
    
    if (!input_file) {
        fprintf(stderr, "Erro: arquivo de entrada não especificado\n\n");
        print_help();
        return 1;
    }
    
    printf("Arquivo de entrada: %s\n", input_file);
    if (output_file) {
        printf("Arquivo de saída: %s\n", output_file);
    } else {
        printf("Saída: stdout\n");
    }
    
    int result = 0;
    
#ifdef MANUAL_MODE
    // Sempre usar modo manual se compilado com MANUAL_MODE
    printf("Modo: Manual (compilado sem flex/bison)\n\n");
    result = manual_translate(input_file, output_file);
#else
    if (force_manual) {
        // Forçar modo manual mesmo com flex/bison disponível
        printf("Modo: Manual (forçado por --manual)\n\n");
        result = manual_translate(input_file, output_file);
    } else {
        // Tentar modo completo com flex/bison
        printf("Modo: Completo (com flex/bison)\n\n");
        
        // Abrir arquivo de entrada
        yyin = fopen(input_file, "r");
        if (!yyin) {
            fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s'\n", input_file);
            return 1;
        }
        
        // Configurar saída
        if (output_file) {
            yyout = fopen(output_file, "w");
            if (!yyout) {
                fprintf(stderr, "Erro: não foi possível criar o arquivo '%s'\n", output_file);
                fclose(yyin);
                return 1;
            }
        } else {
            yyout = stdout;
        }
        
        // Executar a tradução
        result = yyparse();
        
        // Limpeza
        fclose(yyin);
        if (output_file && yyout != stdout) {
            fclose(yyout);
        }
        yylex_destroy();
    }
#endif
    
    if (result == 0) {
        printf("\n✓ Tradução concluída com sucesso!\n");
        if (output_file) {
            printf("Arquivo Portugol gerado: %s\n", output_file);
        }
    } else {
        printf("\n✗ Erro durante a tradução.\n");
        printf("Verifique o código C de entrada.\n");
    }
    
    return result;
}