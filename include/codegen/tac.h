#ifndef TAC_H
#define TAC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic/tipos.h"

/* Tipos de operações em TAC */
typedef enum {
    TAC_NONE,         // Nenhuma operação (placeholder)
    
    // Operações aritméticas
    TAC_ADD,          // Adição: t1 = t2 + t3
    TAC_SUB,          // Subtração: t1 = t2 - t3
    TAC_MUL,          // Multiplicação: t1 = t2 * t3
    TAC_DIV,          // Divisão: t1 = t2 / t3
    TAC_MOD,          // Módulo: t1 = t2 % t3
    
    // Operações de atribuição
    TAC_COPY,         // Cópia: t1 = t2
    TAC_ASSIGN,       // Atribuição: var = t1
    
    // Operações de controle de fluxo
    TAC_LABEL,        // Define um rótulo: L1:
    TAC_JUMP,         // Salto incondicional: goto L1
    TAC_JUMPTRUE,     // Salto condicional (se verdadeiro): if t1 goto L1
    TAC_JUMPFALSE,    // Salto condicional (se falso): ifFalse t1 goto L1
    
    // Operações relacionais
    TAC_EQ,           // Igualdade: t1 = (t2 == t3)
    TAC_NE,           // Diferença: t1 = (t2 != t3)
    TAC_LT,           // Menor que: t1 = (t2 < t3)
    TAC_LE,           // Menor ou igual: t1 = (t2 <= t3)
    TAC_GT,           // Maior que: t1 = (t2 > t3)
    TAC_GE,           // Maior ou igual: t1 = (t2 >= t3)
    
    // Operações lógicas
    TAC_AND,          // E lógico: t1 = (t2 && t3)
    TAC_OR,           // OU lógico: t1 = (t2 || t3)
    TAC_NOT,          // NÃO lógico: t1 = !t2
    
    // Funções
    TAC_PARAM,        // Parâmetro para função: param t1
    TAC_CALL,         // Chamada de função: t1 = call f, n
    TAC_RETURN,       // Retorno de função: return t1
    TAC_FUNCTION,     // Definição de função: function f
    TAC_END,          // Fim de função: endfunction
    
    // Memória e endereçamento
    TAC_LOAD,         // Carrega da memória: t1 = mem[t2]
    TAC_STORE,        // Armazena na memória: mem[t1] = t2
    TAC_ADDR,         // Endereço de: t1 = &var
    TAC_DEREF,        // Dereferência: t1 = *t2
    
    // Operações de array
    TAC_INDEX,        // Acesso a array: t1 = t2[t3]
    TAC_ARRAY_ASSIGN  // Atribuição a array: t1[t2] = t3
} TacOpType;

/* Estrutura para um endereço temporário */
typedef struct TacAddress {
    enum {
        TAC_ADDR_EMPTY,    // Endereço vazio (não utilizado)
        TAC_ADDR_NAME,     // Nome (variável ou rótulo)
        TAC_ADDR_TEMP,     // Temporário (t1, t2, ...)
        TAC_ADDR_CONST_INT,// Constante inteira
        TAC_ADDR_CONST_REAL// Constante real
    } kind;
    
    union {
        char* name;        // Para variáveis e rótulos
        int temp_number;   // Número do temporário
        int const_int;     // Valor constante inteiro
        float const_real;  // Valor constante real
    } value;
    
    TipoSimples type;      // Tipo do endereço
} TacAddress;

/* Estrutura para uma instrução TAC */
typedef struct TacInstruction {
    TacOpType op;          // Operação
    TacAddress result;     // Resultado
    TacAddress arg1;       // Primeiro argumento
    TacAddress arg2;       // Segundo argumento
    struct TacInstruction* next; // Próxima instrução
    struct TacInstruction* prev; // Instrução anterior
} TacInstruction;

/* Estrutura para uma lista de instruções TAC */
typedef struct {
    TacInstruction* first; // Primeira instrução
    TacInstruction* last;  // Última instrução
    int temp_count;        // Contador de temporários
    int label_count;       // Contador de rótulos
} TacList;

/* Funções para manipulação de endereços TAC */
TacAddress tac_empty_address();
TacAddress tac_name_address(const char* name, TipoSimples type);
TacAddress tac_temp_address(int temp_number, TipoSimples type);
TacAddress tac_const_int_address(int value);
TacAddress tac_const_real_address(float value);
char* tac_address_to_string(TacAddress addr);

/* Funções para manipulação de instruções TAC */
TacInstruction* tac_create_instruction(TacOpType op, TacAddress result, TacAddress arg1, TacAddress arg2);
void tac_free_instruction(TacInstruction* instr);

/* Funções para manipulação de listas TAC */
TacList* tac_create_list();
void tac_append_instruction(TacList* list, TacInstruction* instr);
TacList* tac_concat_lists(TacList* list1, TacList* list2);
void tac_free_list(TacList* list);
void tac_print_list(TacList* list, FILE* out);

/* Funções para geração de TAC a partir da AST */
TacList* tac_generate_from_ast(struct AstNode* node);
TacAddress tac_generate_expression(struct AstNode* node, TacList* list);
TacList* tac_generate_statement(struct AstNode* node);
TacList* tac_generate_if(struct AstNode* node);
TacList* tac_generate_while(struct AstNode* node);
TacList* tac_generate_return(struct AstNode* node);

/* Utilitários */
int tac_new_temp(TacList* list);
char* tac_new_label(TacList* list);
TacAddress tac_get_value(TacList* list, struct AstNode* node);

#endif /* TAC_H */
