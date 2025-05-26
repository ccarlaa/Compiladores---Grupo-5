#include "ast/ast.h"
#include <stdio.h>
#include <stdlib.h>

static void erro_alocacao() {
    fprintf(stderr, "Erro: falha na alocação de memória\n");
    exit(1);
}

AstNode* create_literal_node(int value) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();

    node->type = NODE_LITERAL;
    node->data.value = value;
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

AstNode* create_equal_node(AstNode* left, AstNode* right) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();

    node->type = NODE_EQUAL;
    node->data.equal.left = left;
    node->data.equal.right = right;
    return node;
}

AstNode* create_if_node(AstNode* cond, AstNode* then_branch, AstNode* else_branch) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();

    node->type = NODE_IF;
    node->data.if_stmt.cond = cond;
    node->data.if_stmt.then_branch = then_branch;
    node->data.if_stmt.else_branch = else_branch;
    return node;
}

AstNode* create_while_node(AstNode* cond, AstNode* body) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();

    node->type = NODE_WHILE;
    node->data.while_stmt.cond = cond;
    node->data.while_stmt.body = body;
    return node;
}

AstNode* create_return_node(AstNode* value) {
    AstNode* node = malloc(sizeof(AstNode));
    if (!node) erro_alocacao();

    node->type = NODE_RETURN;
    node->data.ret.value = value;
    return node;
}

int evaluate_ast(AstNode* node) {
    if (!node) return 0;

    switch (node->type) {
        case NODE_LITERAL:
            return node->data.value;

        case NODE_BINOP: {
            int l = evaluate_ast(node->data.binop.left);
            int r = evaluate_ast(node->data.binop.right);
            switch (node->data.binop.op) {
                case OP_ADD: return l + r;
                case OP_SUB: return l - r;
                case OP_MUL: return l * r;
                case OP_DIV: return (r != 0) ? l / r : 0;
                case OP_MOD: return (r != 0) ? l % r : 0;
                default: return 0;
            }
        }

        case NODE_EQUAL:
            return evaluate_ast(node->data.equal.right);

        case NODE_IF:
            return evaluate_ast(node->data.if_stmt.cond)
                ? evaluate_ast(node->data.if_stmt.then_branch)
                : evaluate_ast(node->data.if_stmt.else_branch);

        case NODE_WHILE: {
            int result = 0;
            while (evaluate_ast(node->data.while_stmt.cond)) {
                result = evaluate_ast(node->data.while_stmt.body);
            }
            return result;
        }

        case NODE_RETURN:
            return evaluate_ast(node->data.ret.value);

        default:
            return 0;
    }
}

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
        case NODE_IF:
            free_ast(node->data.if_stmt.cond);
            free_ast(node->data.if_stmt.then_branch);
            free_ast(node->data.if_stmt.else_branch);
            break;
        case NODE_WHILE:
            free_ast(node->data.while_stmt.cond);
            free_ast(node->data.while_stmt.body);
            break;
        case NODE_RETURN:
            free_ast(node->data.ret.value);
            break;
        default:
            break;
    }

    free(node);
}

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) printf("  ");
}

void print_ast(AstNode* node, int indent) {
    if (!node) return;

    print_indent(indent);

    switch (node->type) {
        case NODE_LITERAL:
            printf("Literal: %d\n", node->data.value);
            break;

        case NODE_BINOP:
            printf("BinOp: ");
            switch (node->data.binop.op) {
                case OP_ADD: printf("+\n"); break;
                case OP_SUB: printf("-\n"); break;
                case OP_MUL: printf("*\n"); break;
                case OP_DIV: printf("/\n"); break;
                case OP_MOD: printf("%%\n"); break;
            }
            print_ast(node->data.binop.left, indent + 1);
            print_ast(node->data.binop.right, indent + 1);
            break;

        case NODE_EQUAL:
            printf("Atribuição (=)\n");
            print_ast(node->data.equal.left, indent + 1);
            print_ast(node->data.equal.right, indent + 1);
            break;

        case NODE_IF:
            printf("If\n");
            print_indent(indent + 1); printf("Condição:\n");
            print_ast(node->data.if_stmt.cond, indent + 2);
            print_indent(indent + 1); printf("Então:\n");
            print_ast(node->data.if_stmt.then_branch, indent + 2);
            if (node->data.if_stmt.else_branch) {
                print_indent(indent + 1); printf("Senão:\n");
                print_ast(node->data.if_stmt.else_branch, indent + 2);
            }
            break;

        case NODE_WHILE:
            printf("While\n");
            print_indent(indent + 1); printf("Condição:\n");
            print_ast(node->data.while_stmt.cond, indent + 2);
            print_indent(indent + 1); printf("Corpo:\n");
            print_ast(node->data.while_stmt.body, indent + 2);
            break;

        case NODE_RETURN:
            printf("Return\n");
            print_ast(node->data.ret.value, indent + 1);
            break;

        default:
            printf("Nó desconhecido\n");
            break;
    }
}

