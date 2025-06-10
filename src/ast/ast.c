/*
 * TRADUTOR C PARA PORTUGOL
 * Implementação da AST: Criação e manipulação de nós da árvore sintática
 */
#include "ast/ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void erro_alocacao() {
    fprintf(stderr, "Erro: falha na alocação de memória\n");
    exit(1);
}

/* ========== FUNÇÕES DE CRIAÇÃO DE NÓS ========== */

AstNode* create_function_node(char* return_type, char* name, AstNode* body) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_FUNCTION;
    node->data.function.return_type = strdup(return_type);
    node->data.function.name = strdup(name);
    node->data.function.params = NULL;
    node->data.function.body = body;
    return node;
}

AstNode* create_command_list_node(AstNode* first, AstNode* second) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_COMMAND_LIST;
    node->data.command_list.first = first;
    node->data.command_list.second = second;
    return node;
}

AstNode* create_param_list_node(AstNode* first, AstNode* second) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_PARAM_LIST;
    node->data.command_list.first = first;
    node->data.command_list.second = second;
    return node;
}

AstNode* create_param_node(char* type, char* name) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_PARAM;
    node->data.param.type = strdup(type);
    node->data.param.name = strdup(name);
    return node;
}

AstNode* create_block_node(AstNode* commands) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_BLOCK;
    node->data.block.commands = commands;
    return node;
}

AstNode* create_var_decl_node(char* type, char* name, AstNode* init) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_VAR_DECL;
    node->data.var_decl.type = strdup(type);
    node->data.var_decl.name = strdup(name);
    node->data.var_decl.init = init;
    return node;
}

AstNode* create_if_node(AstNode* condition, AstNode* then_block, AstNode* else_block) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_IF;
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_block = then_block;
    node->data.if_stmt.else_block = else_block;
    return node;
}

AstNode* create_while_node(AstNode* condition, AstNode* body) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_WHILE;
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

AstNode* create_for_node(AstNode* init, AstNode* condition, AstNode* update, AstNode* body) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_FOR;
    node->data.for_stmt.init = init;
    node->data.for_stmt.condition = condition;
    node->data.for_stmt.update = update;
    node->data.for_stmt.body = body;
    return node;
}

AstNode* create_return_node(AstNode* expr) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_RETURN;
    node->data.return_stmt.expr = expr;
    return node;
}

AstNode* create_assign_node(char* var, AstNode* expr) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_ASSIGN;
    node->data.assign.var = strdup(var);
    node->data.assign.expr = expr;
    return node;
}

AstNode* create_binop_node(BinOpType op, AstNode* left, AstNode* right) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    return node;
}

AstNode* create_unary_node(BinOpType op, AstNode* operand) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_UNARY;
    node->data.unary.op = op;
    node->data.unary.operand = operand;
    return node;
}

AstNode* create_number_node(int value) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_NUMBER;
    node->data.number.value = value;
    return node;
}

AstNode* create_real_node(float value) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_REAL;
    node->data.real.value = value;
    return node;
}

AstNode* create_id_node(char* name) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_ID;
    node->data.id.name = strdup(name);
    return node;
}

AstNode* create_string_node(char* value) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_STRING;
    node->data.string.value = strdup(value);
    return node;
}

AstNode* create_char_node(char* value) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();
    
    node->type = NODE_CHAR;
    node->data.character.value = strdup(value);
    return node;
}

/* ========== FUNÇÕES DE COMPATIBILIDADE ========== */

AstNode* create_literal_node(int value) {
    return create_number_node(value);
}

AstNode* create_equal_node(AstNode* left, AstNode* right) {
    if (left && left->type == NODE_ID) {
        return create_assign_node(left->data.id.name, right);
    }
    return create_assign_node("unknown", right);
}

/* ========== AVALIAÇÃO DA AST ========== */

int evaluate_ast(AstNode* node) {
    if (!node) return 0;
    
    switch (node->type) {
        case NODE_NUMBER:
            return node->data.number.value;
            
        case NODE_REAL:
            return (int)node->data.real.value;
            
        case NODE_BINOP: {
            int l = evaluate_ast(node->data.binop.left);
            int r = evaluate_ast(node->data.binop.right);
            switch (node->data.binop.op) {
                case OP_ADD: return l + r;
                case OP_SUB: return l - r;
                case OP_MUL: return l * r;
                case OP_DIV: return (r != 0) ? l / r : 0;
                case OP_MOD: return (r != 0) ? l % r : 0;
                case OP_EQ: return l == r;
                case OP_NE: return l != r;
                case OP_LT: return l < r;
                case OP_GT: return l > r;
                case OP_LE: return l <= r;
                case OP_GE: return l >= r;
                case OP_AND: return l && r;
                case OP_OR: return l || r;
                default: return 0;
            }
        }
        
        case NODE_UNARY: {
            int operand = evaluate_ast(node->data.unary.operand);
            switch (node->data.unary.op) {
                case OP_NOT: return !operand;
                case OP_NEG: return -operand;
                default: return operand;
            }
        }
        
        case NODE_ASSIGN:
            return evaluate_ast(node->data.assign.expr);
            
        case NODE_IF:
            return evaluate_ast(node->data.if_stmt.condition)
                ? evaluate_ast(node->data.if_stmt.then_block)
                : evaluate_ast(node->data.if_stmt.else_block);
                
        case NODE_WHILE: {
            int result = 0;
            while (evaluate_ast(node->data.while_stmt.condition)) {
                result = evaluate_ast(node->data.while_stmt.body);
            }
            return result;
        }
        
        case NODE_RETURN:
            return evaluate_ast(node->data.return_stmt.expr);
            
        default:
            return 0;
    }
}

/* ========== IMPRESSÃO DA AST ========== */

static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

void print_ast(AstNode* node, int indent) {
    if (!node) {
        print_indent(indent);
        printf("(null)\n");
        return;
    }
    
    print_indent(indent);
    
    switch (node->type) {
        case NODE_FUNCTION:
            printf("Função: %s %s\n", node->data.function.return_type, node->data.function.name);
            print_ast(node->data.function.body, indent + 1);
            break;
            
        case NODE_COMMAND_LIST:
            printf("Lista de comandos:\n");
            if (node->data.command_list.first) {
                print_ast(node->data.command_list.first, indent + 1);
            }
            if (node->data.command_list.second) {
                print_ast(node->data.command_list.second, indent + 1);
            }
            break;
            
        case NODE_VAR_DECL:
            printf("Declaração: %s %s", node->data.var_decl.type, node->data.var_decl.name);
            if (node->data.var_decl.init) {
                printf(" = ");
                print_ast(node->data.var_decl.init, 0);
            } else {
                printf("\n");
            }
            break;
            
        case NODE_IF:
            printf("Se:\n");
            print_indent(indent + 1);
            printf("Condição:\n");
            print_ast(node->data.if_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("Então:\n");
            print_ast(node->data.if_stmt.then_block, indent + 2);
            if (node->data.if_stmt.else_block) {
                print_indent(indent + 1);
                printf("Senão:\n");
                print_ast(node->data.if_stmt.else_block, indent + 2);
            }
            break;
            
        case NODE_WHILE:
            printf("Enquanto:\n");
            print_indent(indent + 1);
            printf("Condição:\n");
            print_ast(node->data.while_stmt.condition, indent + 2);
            print_indent(indent + 1);
            printf("Corpo:\n");
            print_ast(node->data.while_stmt.body, indent + 2);
            break;
            
        case NODE_RETURN:
            printf("Retorne: ");
            if (node->data.return_stmt.expr) {
                print_ast(node->data.return_stmt.expr, 0);
            } else {
                printf("(vazio)\n");
            }
            break;
            
        case NODE_ASSIGN:
            printf("Atribuição: %s = ", node->data.assign.var);
            print_ast(node->data.assign.expr, 0);
            break;
            
        case NODE_BINOP:
            printf("Operação: ");
            print_ast(node->data.binop.left, 0);
            switch (node->data.binop.op) {
                case OP_ADD: printf(" + "); break;
                case OP_SUB: printf(" - "); break;
                case OP_MUL: printf(" * "); break;
                case OP_DIV: printf(" / "); break;
                case OP_MOD: printf(" %% "); break;
                case OP_EQ: printf(" == "); break;
                case OP_NE: printf(" != "); break;
                case OP_LT: printf(" < "); break;
                case OP_GT: printf(" > "); break;
                case OP_LE: printf(" <= "); break;
                case OP_GE: printf(" >= "); break;
                case OP_AND: printf(" && "); break;
                case OP_OR: printf(" || "); break;
            }
            print_ast(node->data.binop.right, 0);
            break;
            
        case NODE_NUMBER:
            printf("Número: %d\n", node->data.number.value);
            break;
            
        case NODE_REAL:
            printf("Real: %.2f\n", node->data.real.value);
            break;
            
        case NODE_ID:
            printf("ID: %s\n", node->data.id.name);
            break;
            
        case NODE_STRING:
            printf("String: %s\n", node->data.string.value);
            break;
            
        case NODE_CHAR:
            printf("Char: %s\n", node->data.character.value);
            break;
            
        default:
            printf("Nó desconhecido (tipo %d)\n", node->type);
            break;
    }
}

/* ========== LIBERAÇÃO DE MEMÓRIA ========== */

void free_ast(AstNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_FUNCTION:
            free(node->data.function.return_type);
            free(node->data.function.name);
            free_ast(node->data.function.params);
            free_ast(node->data.function.body);
            break;
            
        case NODE_COMMAND_LIST:
        case NODE_PARAM_LIST:
            free_ast(node->data.command_list.first);
            free_ast(node->data.command_list.second);
            break;
            
        case NODE_PARAM:
            free(node->data.param.type);
            free(node->data.param.name);
            break;
            
        case NODE_BLOCK:
            free_ast(node->data.block.commands);
            break;
            
        case NODE_VAR_DECL:
            free(node->data.var_decl.type);
            free(node->data.var_decl.name);
            free_ast(node->data.var_decl.init);
            break;
            
        case NODE_IF:
            free_ast(node->data.if_stmt.condition);
            free_ast(node->data.if_stmt.then_block);
            free_ast(node->data.if_stmt.else_block);
            break;
            
        case NODE_WHILE:
            free_ast(node->data.while_stmt.condition);
            free_ast(node->data.while_stmt.body);
            break;
            
        case NODE_FOR:
            free_ast(node->data.for_stmt.init);
            free_ast(node->data.for_stmt.condition);
            free_ast(node->data.for_stmt.update);
            free_ast(node->data.for_stmt.body);
            break;
            
        case NODE_RETURN:
            free_ast(node->data.return_stmt.expr);
            break;
            
        case NODE_ASSIGN:
            free(node->data.assign.var);
            free_ast(node->data.assign.expr);
            break;
            
        case NODE_BINOP:
            free_ast(node->data.binop.left);
            free_ast(node->data.binop.right);
            break;
            
        case NODE_UNARY:
            free_ast(node->data.unary.operand);
            break;
            
        case NODE_ID:
            free(node->data.id.name);
            break;
            
        case NODE_STRING:
            free(node->data.string.value);
            break;
            
        case NODE_CHAR:
            free(node->data.character.value);
            break;
            
        default:
            break;
    }
    
    free(node);
}
