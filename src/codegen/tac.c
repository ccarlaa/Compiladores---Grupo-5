#include "codegen/tac.h"
#include "ast/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Implementação das funções para manipulação de endereços TAC */

TacAddress tac_empty_address() {
    TacAddress addr;
    addr.kind = TAC_ADDR_EMPTY;
    addr.type = TIPO_INVALIDO;
    return addr;
}

TacAddress tac_name_address(const char* name, TipoSimples type) {
    TacAddress addr;
    addr.kind = TAC_ADDR_NAME;
    addr.value.name = strdup(name);
    addr.type = type;
    return addr;
}

TacAddress tac_temp_address(int temp_number, TipoSimples type) {
    TacAddress addr;
    addr.kind = TAC_ADDR_TEMP;
    addr.value.temp_number = temp_number;
    addr.type = type;
    return addr;
}

TacAddress tac_const_int_address(int value) {
    TacAddress addr;
    addr.kind = TAC_ADDR_CONST_INT;
    addr.value.const_int = value;
    addr.type = TIPO_INT;
    return addr;
}

TacAddress tac_const_real_address(float value) {
    TacAddress addr;
    addr.kind = TAC_ADDR_CONST_REAL;
    addr.value.const_real = value;
    addr.type = TIPO_REAL_;
    return addr;
}

char* tac_address_to_string(TacAddress addr) {
    char* str = (char*)malloc(50);
    switch (addr.kind) {
        case TAC_ADDR_EMPTY:
            strcpy(str, "");
            break;
        case TAC_ADDR_NAME:
            strcpy(str, addr.value.name);
            break;
        case TAC_ADDR_TEMP:
            sprintf(str, "t%d", addr.value.temp_number);
            break;
        case TAC_ADDR_CONST_INT:
            sprintf(str, "%d", addr.value.const_int);
            break;
        case TAC_ADDR_CONST_REAL:
            sprintf(str, "%.2f", addr.value.const_real);
            break;
        default:
            strcpy(str, "UNKNOWN");
    }
    return str;
}

/* Implementação das funções para manipulação de instruções TAC */

TacInstruction* tac_create_instruction(TacOpType op, TacAddress result, TacAddress arg1, TacAddress arg2) {
    TacInstruction* instr = (TacInstruction*)malloc(sizeof(TacInstruction));
    instr->op = op;
    instr->result = result;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    instr->next = NULL;
    instr->prev = NULL;
    return instr;
}

void tac_free_instruction(TacInstruction* instr) {
    if (instr == NULL) return;
    
    // Liberar strings alocadas nos endereços
    if (instr->result.kind == TAC_ADDR_NAME) {
        free(instr->result.value.name);
    }
    if (instr->arg1.kind == TAC_ADDR_NAME) {
        free(instr->arg1.value.name);
    }
    if (instr->arg2.kind == TAC_ADDR_NAME) {
        free(instr->arg2.value.name);
    }
    
    free(instr);
}

/* Implementação das funções para manipulação de listas TAC */

TacList* tac_create_list() {
    TacList* list = (TacList*)malloc(sizeof(TacList));
    list->first = NULL;
    list->last = NULL;
    list->temp_count = 0;
    list->label_count = 0;
    return list;
}

void tac_append_instruction(TacList* list, TacInstruction* instr) {
    if (list == NULL || instr == NULL) return;
    
    if (list->first == NULL) {
        list->first = instr;
        list->last = instr;
    } else {
        instr->prev = list->last;
        list->last->next = instr;
        list->last = instr;
    }
}

TacList* tac_concat_lists(TacList* list1, TacList* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    
    if (list1->first == NULL) {
        free(list1);
        return list2;
    }
    
    if (list2->first == NULL) {
        free(list2);
        return list1;
    }
    
    // Conectar as duas listas
    list1->last->next = list2->first;
    list2->first->prev = list1->last;
    list1->last = list2->last;
    
    // Atualizar contadores
    list1->temp_count = (list1->temp_count > list2->temp_count) ? list1->temp_count : list2->temp_count;
    list1->label_count = (list1->label_count > list2->label_count) ? list1->label_count : list2->label_count;
    
    free(list2);
    return list1;
}

void tac_free_list(TacList* list) {
    if (list == NULL) return;
    
    TacInstruction* curr = list->first;
    while (curr != NULL) {
        TacInstruction* next = curr->next;
        tac_free_instruction(curr);
        curr = next;
    }
    
    free(list);
}

const char* tac_op_to_string(TacOpType op) {
    switch (op) {
        case TAC_NONE: return "NOP";
        case TAC_ADD: return "ADD";
        case TAC_SUB: return "SUB";
        case TAC_MUL: return "MUL";
        case TAC_DIV: return "DIV";
        case TAC_MOD: return "MOD";
        case TAC_COPY: return "COPY";
        case TAC_ASSIGN: return "ASSIGN";
        case TAC_LABEL: return "LABEL";
        case TAC_JUMP: return "JUMP";
        case TAC_JUMPTRUE: return "JUMPTRUE";
        case TAC_JUMPFALSE: return "JUMPFALSE";
        case TAC_EQ: return "EQ";
        case TAC_NE: return "NE";
        case TAC_LT: return "LT";
        case TAC_LE: return "LE";
        case TAC_GT: return "GT";
        case TAC_GE: return "GE";
        case TAC_AND: return "AND";
        case TAC_OR: return "OR";
        case TAC_NOT: return "NOT";
        case TAC_PARAM: return "PARAM";
        case TAC_CALL: return "CALL";
        case TAC_RETURN: return "RETURN";
        case TAC_FUNCTION: return "FUNCTION";
        case TAC_END: return "END";
        case TAC_LOAD: return "LOAD";
        case TAC_STORE: return "STORE";
        case TAC_ADDR: return "ADDR";
        case TAC_DEREF: return "DEREF";
        case TAC_INDEX: return "INDEX";
        case TAC_ARRAY_ASSIGN: return "ARRAY_ASSIGN";
        default: return "UNKNOWN";
    }
}

void tac_print_list(TacList* list, FILE* out) {
    if (list == NULL || out == NULL) return;
    
    fprintf(out, "----------------------\n");
    fprintf(out, "Three-Address Code:\n");
    fprintf(out, "----------------------\n");
    
    TacInstruction* curr = list->first;
    int line = 1;
    
    while (curr != NULL) {
        char* result_str = tac_address_to_string(curr->result);
        char* arg1_str = tac_address_to_string(curr->arg1);
        char* arg2_str = tac_address_to_string(curr->arg2);
        
        fprintf(out, "%3d: ", line++);
        
        switch (curr->op) {
            case TAC_LABEL:
                fprintf(out, "%s:", result_str);
                break;
                
            case TAC_JUMP:
                fprintf(out, "goto %s", result_str);
                break;
                
            case TAC_JUMPTRUE:
                fprintf(out, "if %s goto %s", arg1_str, result_str);
                break;
                
            case TAC_JUMPFALSE:
                fprintf(out, "ifFalse %s goto %s", arg1_str, result_str);
                break;
                
            case TAC_PARAM:
                fprintf(out, "param %s", arg1_str);
                break;
                
            case TAC_CALL:
                if (curr->result.kind != TAC_ADDR_EMPTY) {
                    fprintf(out, "%s = call %s, %s", result_str, arg1_str, arg2_str);
                } else {
                    fprintf(out, "call %s, %s", arg1_str, arg2_str);
                }
                break;
                
            case TAC_RETURN:
                if (curr->arg1.kind != TAC_ADDR_EMPTY) {
                    fprintf(out, "return %s", arg1_str);
                } else {
                    fprintf(out, "return");
                }
                break;
                
            case TAC_FUNCTION:
                fprintf(out, "function %s", result_str);
                break;
                
            case TAC_END:
                fprintf(out, "endfunction");
                break;
                
            case TAC_NONE:
                fprintf(out, "nop");
                break;
                
            case TAC_ASSIGN:
                fprintf(out, "%s = %s", result_str, arg1_str);
                break;
                
            case TAC_LOAD:
                fprintf(out, "%s = mem[%s]", result_str, arg1_str);
                break;
                
            case TAC_STORE:
                fprintf(out, "mem[%s] = %s", result_str, arg1_str);
                break;
                
            case TAC_INDEX:
                fprintf(out, "%s = %s[%s]", result_str, arg1_str, arg2_str);
                break;
                
            case TAC_ARRAY_ASSIGN:
                fprintf(out, "%s[%s] = %s", result_str, arg1_str, arg2_str);
                break;
                
            default:
                // Operações binárias e outras
                if (curr->arg2.kind != TAC_ADDR_EMPTY) {
                    fprintf(out, "%s = %s %s %s", result_str, arg1_str, tac_op_to_string(curr->op), arg2_str);
                } else if (curr->arg1.kind != TAC_ADDR_EMPTY) {
                    fprintf(out, "%s = %s %s", result_str, tac_op_to_string(curr->op), arg1_str);
                } else {
                    fprintf(out, "%s %s", tac_op_to_string(curr->op), result_str);
                }
        }
        
        fprintf(out, "\n");
        
        free(result_str);
        free(arg1_str);
        free(arg2_str);
        
        curr = curr->next;
    }
    
    fprintf(out, "----------------------\n");
}

/* Implementação de utilitários */

int tac_new_temp(TacList* list) {
    return ++list->temp_count;
}

char* tac_new_label(TacList* list) {
    char* label = (char*)malloc(20);
    sprintf(label, "L%d", ++list->label_count);
    return label;
}

/* Implementação das funções de geração de TAC a partir da AST */

// Função auxiliar para mapear operações binárias da AST para operações TAC
TacOpType map_binop_to_tac(BinOpType op) {
    switch (op) {
        case OP_ADD: return TAC_ADD;
        case OP_SUB: return TAC_SUB;
        case OP_MUL: return TAC_MUL;
        case OP_DIV: return TAC_DIV;
        case OP_MOD: return TAC_MOD;
        default: return TAC_NONE;
    }
}

TacAddress tac_generate_expression(AstNode* node, TacList* list) {
    if (node == NULL || list == NULL) {
        return tac_empty_address();
    }
    
    switch (node->type) {
        case NODE_LITERAL: {
            // Caso simples, apenas retorna um endereço constante
            return tac_const_int_address(node->data.value);
        }
        
        case NODE_BINOP: {
            // Gerar código para as subexpressões
            TacAddress left_addr = tac_generate_expression(node->data.binop.left, list);
            TacAddress right_addr = tac_generate_expression(node->data.binop.right, list);
            
            // Criar temporário para o resultado
            int temp = tac_new_temp(list);
            TacAddress result = tac_temp_address(temp, node->tipo);
            
            // Mapear a operação e criar a instrução
            TacOpType op = map_binop_to_tac(node->data.binop.op);
            TacInstruction* instr = tac_create_instruction(op, result, left_addr, right_addr);
            tac_append_instruction(list, instr);
            
            return result;
        }
        
        case NODE_EQUAL: {
            // Gerar código para o lado direito
            TacAddress right_addr = tac_generate_expression(node->data.equal.right, list);
            
            // Se o lado esquerdo for um identificador (variável)
            if (node->data.equal.left != NULL) {
                TacAddress left_addr = tac_generate_expression(node->data.equal.left, list);
                TacInstruction* instr = tac_create_instruction(TAC_ASSIGN, left_addr, right_addr, tac_empty_address());
                tac_append_instruction(list, instr);
                return left_addr;
            } else {
                // Se não houver lado esquerdo, retornar o valor do lado direito
                return right_addr;
            }
        }
        
        default:
            // Tipos de nós não suportados retornam endereço vazio
            return tac_empty_address();
    }
}

TacList* tac_generate_if(AstNode* node) {
    if (node == NULL || node->type != NODE_IF) {
        return tac_create_list();
    }
    
    TacList* list = tac_create_list();
    
    // Gerar código para a condição
    TacAddress cond_addr = tac_generate_expression(node->data.if_stmt.cond, list);
    
    // Criar rótulos para os saltos
    char* else_label = tac_new_label(list);
    char* end_label = tac_new_label(list);
    
    // Salto para o else se a condição for falsa
    TacInstruction* jump_to_else = tac_create_instruction(
        TAC_JUMPFALSE,
        tac_name_address(else_label, TIPO_INVALIDO),
        cond_addr,
        tac_empty_address()
    );
    tac_append_instruction(list, jump_to_else);
    
    // Gerar código para o bloco then
    if (node->data.if_stmt.then_branch != NULL) {
        TacList* then_list = tac_generate_statement(node->data.if_stmt.then_branch);
        list = tac_concat_lists(list, then_list);
    }
    
    // Salto para o fim após o bloco then
    TacInstruction* jump_to_end = tac_create_instruction(
        TAC_JUMP,
        tac_name_address(end_label, TIPO_INVALIDO),
        tac_empty_address(),
        tac_empty_address()
    );
    tac_append_instruction(list, jump_to_end);
    
    // Rótulo para o else
    TacInstruction* else_label_instr = tac_create_instruction(
        TAC_LABEL,
        tac_name_address(else_label, TIPO_INVALIDO),
        tac_empty_address(),
        tac_empty_address()
    );
    tac_append_instruction(list, else_label_instr);
    free(else_label); // Já foi copiado para a instrução
    
    // Gerar código para o bloco else, se existir
    if (node->data.if_stmt.else_branch != NULL) {
        TacList* else_list = tac_generate_statement(node->data.if_stmt.else_branch);
        list = tac_concat_lists(list, else_list);
    }
    
    // Rótulo para o fim
    TacInstruction* end_label_instr = tac_create_instruction(
        TAC_LABEL,
        tac_name_address(end_label, TIPO_INVALIDO),
        tac_empty_address(),
        tac_empty_address()
    );
    tac_append_instruction(list, end_label_instr);
    free(end_label); // Já foi copiado para a instrução
    
    return list;
}

TacList* tac_generate_while(AstNode* node) {
    if (node == NULL || node->type != NODE_WHILE) {
        return tac_create_list();
    }
    
    TacList* list = tac_create_list();
    
    // Criar rótulos para os saltos
    char* start_label = tac_new_label(list);
    char* end_label = tac_new_label(list);
    
    // Rótulo para o início do loop
    TacInstruction* start_label_instr = tac_create_instruction(
        TAC_LABEL,
        tac_name_address(start_label, TIPO_INVALIDO),
        tac_empty_address(),
        tac_empty_address()
    );
    tac_append_instruction(list, start_label_instr);
    
    // Gerar código para a condição
    TacAddress cond_addr = tac_generate_expression(node->data.while_stmt.cond, list);
    
    // Salto para o fim se a condição for falsa
    TacInstruction* jump_to_end = tac_create_instruction(
        TAC_JUMPFALSE,
        tac_name_address(end_label, TIPO_INVALIDO),
        cond_addr,
        tac_empty_address()
    );
    tac_append_instruction(list, jump_to_end);
    
    // Gerar código para o corpo do loop
    if (node->data.while_stmt.body != NULL) {
        TacList* body_list = tac_generate_statement(node->data.while_stmt.body);
        list = tac_concat_lists(list, body_list);
    }
    
    // Salto para o início do loop
    TacInstruction* jump_to_start = tac_create_instruction(
        TAC_JUMP,
        tac_name_address(start_label, TIPO_INVALIDO),
        tac_empty_address(),
        tac_empty_address()
    );
    tac_append_instruction(list, jump_to_start);
    free(start_label); // Já foi copiado para as instruções
    
    // Rótulo para o fim do loop
    TacInstruction* end_label_instr = tac_create_instruction(
        TAC_LABEL,
        tac_name_address(end_label, TIPO_INVALIDO),
        tac_empty_address(),
        tac_empty_address()
    );
    tac_append_instruction(list, end_label_instr);
    free(end_label); // Já foi copiado para as instruções
    
    return list;
}

TacList* tac_generate_return(AstNode* node) {
    if (node == NULL || node->type != NODE_RETURN) {
        return tac_create_list();
    }
    
    TacList* list = tac_create_list();
    
    // Gerar código para a expressão de retorno, se existir
    TacAddress value_addr = tac_empty_address();
    if (node->data.ret.value != NULL) {
        value_addr = tac_generate_expression(node->data.ret.value, list);
    }
    
    // Criar instrução de retorno
    TacInstruction* ret_instr = tac_create_instruction(
        TAC_RETURN,
        tac_empty_address(),
        value_addr,
        tac_empty_address()
    );
    tac_append_instruction(list, ret_instr);
    
    return list;
}

TacList* tac_generate_statement(AstNode* node) {
    if (node == NULL) {
        return tac_create_list();
    }
    
    switch (node->type) {
        case NODE_IF:
            return tac_generate_if(node);
            
        case NODE_WHILE:
            return tac_generate_while(node);
            
        case NODE_RETURN:
            return tac_generate_return(node);
            
        case NODE_BINOP:
        case NODE_EQUAL:
        case NODE_LITERAL: {
            // Expressões como comandos
            TacList* list = tac_create_list();
            tac_generate_expression(node, list);
            return list;
        }
            
        default:
            // Nós não suportados geram listas vazias
            return tac_create_list();
    }
}

TacList* tac_generate_from_ast(AstNode* node) {
    if (node == NULL) {
        return tac_create_list();
    }
    
    // A geração começa pelo nó raiz e processa recursivamente
    return tac_generate_statement(node);
}
