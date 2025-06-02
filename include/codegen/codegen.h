#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast/ast.h"

/**
 * Inicializa o gerador de código intermediário
 */
void inicializa_codegen();

/**
 * Gera código intermediário a partir da AST
 * @param ast_root Nó raiz da árvore sintática abstrata
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int gera_codigo_intermediario(AstNode* ast_root);

/**
 * Imprime o código intermediário gerado
 * @param output Arquivo de saída (se NULL, usa stdout)
 */
void imprime_codigo_intermediario(FILE* output);

/**
 * Libera os recursos utilizados pelo gerador de código
 */
void finaliza_codegen();

/**
 * Otimiza o código intermediário gerado
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int otimiza_codigo_intermediario();

/**
 * Salva o código intermediário em um arquivo
 * @param filename Nome do arquivo de saída
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int salva_codigo_intermediario(const char* filename);

#endif /* CODEGEN_H */
