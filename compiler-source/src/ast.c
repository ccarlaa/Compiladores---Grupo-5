#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* create_node(NodeType type, const char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

void add_child(ASTNode *parent, ASTNode *child) {
    parent->children = realloc(parent->children, 
                              sizeof(ASTNode*) * (parent->child_count + 1));
    parent->children[parent->child_count] = child;
    parent->child_count++;
}

void free_ast(ASTNode *node) {
    if (!node) return;
    
    for (int i = 0; i < node->child_count; i++) {
        free_ast(node->children[i]);
    }
    free(node->children);
    free(node->value);
    free(node);
}

void print_ast(ASTNode *node, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    
    const char *node_names[] = {
        "PROGRAM", "FUNCTION", "TYPE", "PARAM_LIST", "BLOCK", "DECLARATION", 
        "ASSIGNMENT", "IDENTIFIER", "CONST_INT", "CONST_FLOAT", "CONST_STRING", 
        "CONST_CHAR", "BINARY_OP", "UNARY_OP", "IF", "ELSE_IF", "ELSE", 
        "WHILE", "DO_WHILE", "FOR", "PRINTF", "SCANF", "RETURN", "STRUCT", 
        "STRUCT_MEMBER", "STRUCT_MEMBER_LIST", "SWITCH", "CASE", "DEFAULT", 
        "CASE_LIST", "STATEMENT_LIST", "DECLARATION_LIST", "FUNCTION_CALL", 
        "MEMBER_ACCESS", "POINTER_ACCESS", "BREAK", "CONTINUE", "EMPTY"
    };
    
    printf("%s", node_names[node->type]);
    if (node->value) printf(" (%s)", node->value);
    printf("\n");
    
    for (int i = 0; i < node->child_count; i++) {
        print_ast(node->children[i], depth + 1);
    }
}

void print_ast_branch(ASTNode *node, char *prefix, int is_last, int is_root) {
    const char *node_names[] = {
        "PROGRAM", "FUNCTION", "TYPE", "PARAM_LIST", "BLOCK", "DECLARATION", 
        "ASSIGNMENT", "IDENTIFIER", "CONST_INT", "CONST_FLOAT", "CONST_STRING", 
        "CONST_CHAR", "BINARY_OP", "UNARY_OP", "IF", "ELSE_IF", "ELSE", 
        "WHILE", "DO_WHILE", "FOR", "PRINTF", "SCANF", "RETURN", "STRUCT", 
        "STRUCT_MEMBER", "STRUCT_MEMBER_LIST", "SWITCH", "CASE", "DEFAULT", 
        "CASE_LIST", "STATEMENT_LIST", "DECLARATION_LIST", "FUNCTION_CALL", 
        "MEMBER_ACCESS", "POINTER_ACCESS", "BREAK", "CONTINUE", "EMPTY"
    };

    if (is_root) {
        fprintf(stderr, "%s", prefix);
    } else {
        fprintf(stderr, "%s%s", prefix, is_last ? "└── " : "├── ");
    }
    
    fprintf(stderr, "%s", node_names[node->type]);
    if (node->value) fprintf(stderr, " (%s)", node->value);
    fprintf(stderr, "\n");
    
    char new_prefix[1024];
    
    if (is_root) {
        strcpy(new_prefix, "");
    } else {
        strcpy(new_prefix, prefix);
        strcat(new_prefix, is_last ? "    " : "│   ");
    }
    
    for (int i = 0; i < node->child_count; i++) {
        print_ast_branch(node->children[i], new_prefix, i == node->child_count - 1, 0);
    }
}

void print_ast_stderr(ASTNode *node, int depth) {
    fprintf(stderr, "\n===== ÁRVORE AST =====\n");
    
    if (node) {
        print_ast_branch(node, "", 1, 1);
    } else {
        fprintf(stderr, "(Árvore vazia)\n");
    }
    
    fprintf(stderr, "========================\n\n");
}