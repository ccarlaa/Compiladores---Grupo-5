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
 * Verifica se um endereço TAC é uma constante
 */
static int is_constant(TacAddr* addr) {
    return addr != NULL && addr->type == TAC_ADDR_CONST;
}

/**
 * Verifica se um endereço TAC é uma variável temporária
 */
static int is_temp(TacAddr* addr) {
    return addr != NULL && addr->type == TAC_ADDR_TEMP;
}

/**
 * Propagação de constantes
 * Busca atribuições de constantes para variáveis e substitui usos posteriores
 */
static void otimiza_propagacao_constantes() {
    // Mapeia variáveis para suas constantes (se conhecidas)
    TacInstr* instr = codigo_intermediario->first;
    
    while (instr) {
        // Atribuição de constante para variável
        if (instr->op == TAC_ASSIGN && 
            instr->dest && instr->dest->type == TAC_ADDR_VAR &&
            instr->src1 && instr->src1->type == TAC_ADDR_CONST) {
            
            // Propaga a constante em instruções subsequentes
            TacInstr* next_instr = instr->next;
            while (next_instr) {
                // Substitui usos da variável pela constante
                if (next_instr->src1 && next_instr->src1->type == TAC_ADDR_VAR &&
                    strcmp(next_instr->src1->addr.var_name, instr->dest->addr.var_name) == 0) {
                    // Só substitui se não houver redefinição antes
                    next_instr->src1 = instr->src1;
                }
                
                // Mesma verificação para src2
                if (next_instr->src2 && next_instr->src2->type == TAC_ADDR_VAR &&
                    strcmp(next_instr->src2->addr.var_name, instr->dest->addr.var_name) == 0) {
                    next_instr->src2 = instr->src1;
                }
                
                // Para se a variável for redefinida
                if (next_instr->dest && next_instr->dest->type == TAC_ADDR_VAR &&
                    strcmp(next_instr->dest->addr.var_name, instr->dest->addr.var_name) == 0) {
                    break;
                }
                
                next_instr = next_instr->next;
            }
        }
        
        instr = instr->next;
    }
}

/**
 * Simplificação algébrica
 * Simplifica operações aritméticas com constantes
 */
static void otimiza_simplificacao_algebrica() {
    TacInstr* instr = codigo_intermediario->first;
    
    while (instr) {
        // Operações com constantes
        if ((instr->op == TAC_ADD || instr->op == TAC_SUB || 
             instr->op == TAC_MUL || instr->op == TAC_DIV) &&
            is_constant(instr->src1) && is_constant(instr->src2)) {
            
            int val1 = instr->src1->addr.const_val;
            int val2 = instr->src2->addr.const_val;
            int result = 0;
            
            // Computa o resultado em tempo de compilação
            switch (instr->op) {
                case TAC_ADD: result = val1 + val2; break;
                case TAC_SUB: result = val1 - val2; break;
                case TAC_MUL: result = val1 * val2; break;
                case TAC_DIV: 
                    if (val2 == 0) {
                        fprintf(stderr, "Aviso: divisão por zero detectada durante otimização.\n");
                        instr = instr->next;
                        continue;
                    }
                    result = val1 / val2; 
                    break;
            }
            
            // Converte a instrução para uma simples atribuição de constante
            instr->op = TAC_ASSIGN;
            instr->src1 = tac_create_const_addr(result);
            instr->src2 = NULL;
        }
        
        // Casos especiais: x + 0, x * 0, x * 1, etc.
        if (instr->op == TAC_ADD && is_constant(instr->src2) && instr->src2->addr.const_val == 0) {
            // x + 0 = x
            instr->op = TAC_ASSIGN;
            instr->src2 = NULL;
        } else if (instr->op == TAC_SUB && is_constant(instr->src2) && instr->src2->addr.const_val == 0) {
            // x - 0 = x
            instr->op = TAC_ASSIGN;
            instr->src2 = NULL;
        } else if (instr->op == TAC_MUL) {
            if (is_constant(instr->src2) && instr->src2->addr.const_val == 0) {
                // x * 0 = 0
                instr->op = TAC_ASSIGN;
                instr->src1 = tac_create_const_addr(0);
                instr->src2 = NULL;
            } else if (is_constant(instr->src2) && instr->src2->addr.const_val == 1) {
                // x * 1 = x
                instr->op = TAC_ASSIGN;
                instr->src2 = NULL;
            }
        } else if (instr->op == TAC_DIV && is_constant(instr->src2) && instr->src2->addr.const_val == 1) {
            // x / 1 = x
            instr->op = TAC_ASSIGN;
            instr->src2 = NULL;
        }
        
        instr = instr->next;
    }
}

/**
 * Eliminação de código morto
 * Remove instruções que não afetam o resultado final
 */
static void otimiza_eliminacao_codigo_morto() {
    // Marcar instruções usadas
    int* usado = (int*)calloc(tac_get_instr_count(codigo_intermediario), sizeof(int));
    if (!usado) {
        fprintf(stderr, "Erro de alocação de memória durante otimização.\n");
        return;
    }
    
    // Primeiro, marcar todos os saltos e retornos como usados
    int idx = 0;
    TacInstr* instr = codigo_intermediario->first;
    while (instr) {
        if (instr->op == TAC_JUMP || instr->op == TAC_IF || instr->op == TAC_IFZ || 
            instr->op == TAC_RETURN || instr->op == TAC_LABEL) {
            usado[idx] = 1;
        }
        instr = instr->next;
        idx++;
    }
    
    // Segunda passagem: marcar instruções que definem valores usados
    int alterado;
    do {
        alterado = 0;
        idx = 0;
        instr = codigo_intermediario->first;
        
        while (instr) {
            // Se a instrução já está marcada como usada
            if (usado[idx]) {
                // Marcar instruções que definem operandos usados
                if (instr->src1 && instr->src1->type == TAC_ADDR_TEMP) {
                    int def_idx = 0;
                    TacInstr* def_instr = codigo_intermediario->first;
                    
                    while (def_instr) {
                        if (def_instr->dest && def_instr->dest->type == TAC_ADDR_TEMP &&
                            def_instr->dest->addr.temp_id == instr->src1->addr.temp_id && 
                            !usado[def_idx]) {
                            usado[def_idx] = 1;
                            alterado = 1;
                        }
                        def_instr = def_instr->next;
                        def_idx++;
                    }
                }
                
                // Mesma verificação para src2
                if (instr->src2 && instr->src2->type == TAC_ADDR_TEMP) {
                    int def_idx = 0;
                    TacInstr* def_instr = codigo_intermediario->first;
                    
                    while (def_instr) {
                        if (def_instr->dest && def_instr->dest->type == TAC_ADDR_TEMP &&
                            def_instr->dest->addr.temp_id == instr->src2->addr.temp_id && 
                            !usado[def_idx]) {
                            usado[def_idx] = 1;
                            alterado = 1;
                        }
                        def_instr = def_instr->next;
                        def_idx++;
                    }
                }
            }
            
            instr = instr->next;
            idx++;
        }
    } while (alterado);
    
    // Remover instruções não usadas
    TacList* otimizado = tac_create_list();
    idx = 0;
    instr = codigo_intermediario->first;
    
    while (instr) {
        if (usado[idx]) {
            tac_append_instr(otimizado, tac_copy_instr(instr));
        }
        instr = instr->next;
        idx++;
    }
    
    // Substituir a lista original pela otimizada
    tac_free_list(codigo_intermediario);
    codigo_intermediario = otimizado;
    
    free(usado);
}

/**
 * Eliminação de subexpressões comuns
 * Identifica cálculos repetidos e reutiliza resultados já computados
 */
static void otimiza_subexpressoes_comuns() {
    TacInstr* instr = codigo_intermediario->first;
    
    while (instr) {
        // Procura por operações aritméticas ou relacionais
        if ((instr->op >= TAC_ADD && instr->op <= TAC_MOD) || 
            (instr->op >= TAC_EQ && instr->op <= TAC_GE)) {
            
            // Busca expressões idênticas anteriores
            TacInstr* prev = codigo_intermediario->first;
            while (prev != instr) {
                if (prev->op == instr->op && 
                    prev->src1 && instr->src1 && 
                    prev->src2 && instr->src2) {
                    
                    // Comparar os operandos
                    int src1_igual = 0, src2_igual = 0;
                    
                    // Comparar src1
                    if (prev->src1->type == instr->src1->type) {
                        if (prev->src1->type == TAC_ADDR_CONST && 
                            prev->src1->addr.const_val == instr->src1->addr.const_val) {
                            src1_igual = 1;
                        } else if (prev->src1->type == TAC_ADDR_VAR && 
                                 strcmp(prev->src1->addr.var_name, instr->src1->addr.var_name) == 0) {
                            src1_igual = 1;
                        } else if (prev->src1->type == TAC_ADDR_TEMP && 
                                 prev->src1->addr.temp_id == instr->src1->addr.temp_id) {
                            src1_igual = 1;
                        }
                    }
                    
                    // Comparar src2
                    if (prev->src2->type == instr->src2->type) {
                        if (prev->src2->type == TAC_ADDR_CONST && 
                            prev->src2->addr.const_val == instr->src2->addr.const_val) {
                            src2_igual = 1;
                        } else if (prev->src2->type == TAC_ADDR_VAR && 
                                 strcmp(prev->src2->addr.var_name, instr->src2->addr.var_name) == 0) {
                            src2_igual = 1;
                        } else if (prev->src2->type == TAC_ADDR_TEMP && 
                                 prev->src2->addr.temp_id == instr->src2->addr.temp_id) {
                            src2_igual = 1;
                        }
                    }
                    
                    // Se ambos operandos são iguais, reutilizar o resultado
                    if (src1_igual && src2_igual) {
                        instr->op = TAC_ASSIGN;
                        instr->src1 = prev->dest;
                        instr->src2 = NULL;
                        break;
                    }
                }
                
                prev = prev->next;
            }
        }
        
        instr = instr->next;
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
    
    printf("Iniciando otimização do código intermediário...\n");
    
    // 1. Propagação de constantes
    otimiza_propagacao_constantes();
    
    // 2. Simplificação algébrica
    otimiza_simplificacao_algebrica();
    
    // 3. Eliminação de subexpressões comuns
    otimiza_subexpressoes_comuns();
    
    // 4. Eliminação de código morto
    otimiza_eliminacao_codigo_morto();
    
    printf("Otimização concluída com sucesso.\n");
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