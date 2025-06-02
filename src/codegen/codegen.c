#include "codegen/tac.h"
#include "ast/ast.h"
#include <stdio.h>
#include <stdlib.h>

// Variável global para armazenar a lista de instruções TAC geradas
TacList* codigo_intermediario = NULL;

/**
 * Inicializa o gerador de código intermediário
 */
void inicializa_codegen() {
    // Liberar qualquer lista anterior, se existir
    if (codigo_intermediario != NULL) {
        tac_free_list(codigo_intermediario);
    }
    
    // Criar uma nova lista vazia
    codigo_intermediario = tac_create_list();
}

/**
 * Gera código intermediário a partir da AST
 * @param ast_root Nó raiz da árvore sintática abstrata
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int gera_codigo_intermediario(AstNode* ast_root) {
    // Verificar se o codegen foi inicializado
    if (codigo_intermediario == NULL) {
        fprintf(stderr, "Erro: gerador de código não inicializado.\n");
        return 1;
    }
    
    // Verificar se a AST é válida
    if (ast_root == NULL) {
        fprintf(stderr, "Aviso: AST vazia, nenhum código gerado.\n");
        return 0;
    }
    
    // Gerar o código a partir da AST
    TacList* new_list = tac_generate_from_ast(ast_root);
    
    // Anexar o novo código à lista global
    codigo_intermediario = tac_concat_lists(codigo_intermediario, new_list);
    
    return 0;
}

/**
 * Imprime o código intermediário gerado
 * @param output Arquivo de saída (se NULL, usa stdout)
 */
void imprime_codigo_intermediario(FILE* output) {
    if (output == NULL) {
        output = stdout;
    }
    
    if (codigo_intermediario == NULL) {
        fprintf(output, "Nenhum código intermediário disponível.\n");
        return;
    }
    
    // Imprimir a lista de instruções TAC
    tac_print_list(codigo_intermediario, output);
}

/**
 * Libera os recursos utilizados pelo gerador de código
 */
void finaliza_codegen() {
    if (codigo_intermediario != NULL) {
        tac_free_list(codigo_intermediario);
        codigo_intermediario = NULL;
    }
}

/**
 * Otimiza o código intermediário gerado
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int otimiza_codigo_intermediario() {
    if (codigo_intermediario == NULL) {
        fprintf(stderr, "Erro: nenhum código intermediário para otimizar.\n");
        return 1;
    }
    
    // Implementar otimizações aqui:
    // 1. Eliminação de código morto
    // 2. Propagação de constantes
    // 3. Eliminação de subexpressões comuns
    // 4. Otimização de laços
    
    // Por enquanto, apenas retorna sucesso sem fazer otimizações
    return 0;
}

/**
 * Salva o código intermediário em um arquivo
 * @param filename Nome do arquivo de saída
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int salva_codigo_intermediario(const char* filename) {
    if (codigo_intermediario == NULL) {
        fprintf(stderr, "Erro: nenhum código intermediário para salvar.\n");
        return 1;
    }
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Erro: não foi possível abrir o arquivo '%s' para escrita.\n", filename);
        return 2;
    }
    
    // Imprimir o código no arquivo
    tac_print_list(codigo_intermediario, file);
    
    fclose(file);
    return 0;
}