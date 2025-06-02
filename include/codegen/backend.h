#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>
#include "codegen/tac.h"

/**
 * Inicializa o gerador de código de máquina
 */
void inicializa_backend();

/**
 * Gera código de máquina a partir do código intermediário TAC
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int gera_codigo_maquina();

/**
 * Imprime o código de máquina gerado
 * @param output Arquivo de saída (se NULL, usa stdout)
 */
void imprime_codigo_maquina(FILE* output);

/**
 * Salva o código de máquina em um arquivo executável
 * @param filename Nome do arquivo de saída
 * @return 0 em caso de sucesso, código de erro caso contrário
 */
int salva_codigo_maquina(const char* filename);

/**
 * Libera os recursos utilizados pelo gerador de código de máquina
 */
void finaliza_backend();

#endif /* BACKEND_H */
