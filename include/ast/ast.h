#ifndef AST_H
#define AST_H

/* Tipos de nós na AST */
typedef enum {
    NODE_LITERAL,    /* Valor literal (número) */
    NODE_BINOP,      /* Operação binária (soma, subtração, etc.) */
    NODE_EQUAL       /* Igualdade (=) */
} NodeType;

/* Tipos de operações binárias */
typedef enum {
    OP_ADD,          /* Adição (+) */
    OP_SUB,          /* Subtração (-) */
    OP_MUL,          /* Multiplicação (*) */
    OP_DIV,          /* Divisão (/) */
    OP_MOD           /* Módulo (%) */
} BinOpType;

/* Estrutura para um nó da AST */
typedef struct AstNode {
    NodeType type;
    union {
        /* Para nós de valor literal */
        int value;
        
        /* Para nós de operação binária */
        struct {
            BinOpType op;
            struct AstNode *left;
            struct AstNode *right;
        } binop;
        
        /* Para nós de igualdade */
        struct {
            struct AstNode *left;
            struct AstNode *right;
        } equal;
    } data;
} AstNode;

/* Funções para criar nós da AST */
AstNode* create_literal_node(int value);
AstNode* create_binop_node(BinOpType op, AstNode *left, AstNode *right);
AstNode* create_equal_node(AstNode *left, AstNode *right);

/* Função para avaliar a AST */
int evaluate_ast(AstNode *node);

/* Função para liberar a memória da AST */
void free_ast(AstNode *node);

#endif /* AST_H */
