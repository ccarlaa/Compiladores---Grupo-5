#include "ast/ast.h"
#include <stdio.h>
#include <stdlib.h>

/* Função para criar um nó literal (número) */
AstNode* create_literal_node(int value) {
    AstNode* node = (AstNode*)malloc(sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        exit(1);
    }
    
    node->type = NODE_LITERAL;
    node->data.value = value;
    
    return node;
}

/* Função para criar um nó de operação binária */
AstNode* create_binop_node(BinOpType op, AstNode* left, AstNode* right) {
    AstNode* node = (AstNode*)malloc(sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        exit(1);
    }
    
    node->type = NODE_BINOP;
    node->data.binop.op = op;
    node->data.binop.left = left;
    node->data.binop.right = right;
    
    return node;
}

/* Função para criar um nó de igualdade (=) */
AstNode* create_equal_node(AstNode* left, AstNode* right) {
    AstNode* node = (AstNode*)malloc(sizeof(AstNode));
    if (!node) {
        fprintf(stderr, "Erro: falha na alocação de memória\n");
        exit(1);
    }
    
    node->type = NODE_EQUAL;
    node->data.equal.left = left;
    node->data.equal.right = right;
    
    return node;
}

/* Função para avaliar a AST */
int evaluate_ast(AstNode* node) {
    if (!node) {
        fprintf(stderr, "Erro: nó nulo na avaliação da AST\n");
        return 0;
    }
    
    switch (node->type) {
        case NODE_LITERAL:
            return node->data.value;
            
        case NODE_BINOP: {
            int left_val = evaluate_ast(node->data.binop.left);
            int right_val = evaluate_ast(node->data.binop.right);
            
            switch (node->data.binop.op) {
                case OP_ADD: return left_val + right_val;
                case OP_SUB: return left_val - right_val;
                case OP_MUL: return left_val * right_val;
                case OP_DIV:
                    if (right_val == 0) {
                        fprintf(stderr, "Erro: divisão por zero\n");
                        exit(1);
                    }
                    return left_val / right_val;
                default:
                    fprintf(stderr, "Erro: operador binário desconhecido\n");
                    return 0;
            }
        }
        
        case NODE_EQUAL: {
            int left_val = evaluate_ast(node->data.equal.left);
            int right_val = evaluate_ast(node->data.equal.right);
            
            if (left_val == right_val) {
                return left_val; // Se a igualdade for verdadeira, retorna o valor
            } else {
                printf("Aviso: valores diferentes em expressão de igualdade: %d != %d\n", 
                       left_val, right_val);
                return left_val; // Em caso de desigualdade, retorna o valor da esquerda
            }
        }
        
        default:
            fprintf(stderr, "Erro: tipo de nó desconhecido na AST\n");
            return 0;
    }
}

/* Função para liberar a memória da AST */
void free_ast(AstNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_BINOP:
            free_ast(node->data.binop.left);
            free_ast(node->data.binop.right);
            break;
            
        case NODE_EQUAL:
            free_ast(node->data.equal.left);
            free_ast(node->data.equal.right);
            break;
            
        case NODE_LITERAL:
            // Nada a fazer para nós literais
            break;
    }
    
    free(node);
} 