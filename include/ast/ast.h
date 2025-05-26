#ifndef AST_H
#define AST_H

/* Tipos de nós na AST */
typedef enum {
    NODE_LITERAL,    // Valor literal (número)
    NODE_BINOP,      // Operação binária (+, -, *, /, %)
    NODE_EQUAL,      // Atribuição (=)
    NODE_IF,         // Estrutura condicional if
    NODE_WHILE,      // Estrutura de repetição while
    NODE_RETURN      // Comando de retorno
} NodeType;

/* Tipos de operações binárias */
typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD
} BinOpType;

/* Estrutura de um nó da AST */
typedef struct AstNode {
    NodeType type;
    union {
        int value;  // NODE_LITERAL

        struct {
            BinOpType op;
            struct AstNode *left;
            struct AstNode *right;
        } binop;  // NODE_BINOP

        struct {
            struct AstNode *left;
            struct AstNode *right;
        } equal;  // NODE_EQUAL

        struct {
            struct AstNode *cond;
            struct AstNode *then_branch;
            struct AstNode *else_branch;
        } if_stmt;  // NODE_IF

        struct {
            struct AstNode *cond;
            struct AstNode *body;
        } while_stmt;  // NODE_WHILE

        struct {
            struct AstNode *value;
        } ret;  // NODE_RETURN

    } data;
} AstNode;

/* Funções de criação de nós */
AstNode* create_literal_node(int value);
AstNode* create_binop_node(BinOpType op, AstNode* left, AstNode* right);
AstNode* create_equal_node(AstNode* left, AstNode* right);
AstNode* create_if_node(AstNode* cond, AstNode* then_branch, AstNode* else_branch);
AstNode* create_while_node(AstNode* cond, AstNode* body);
AstNode* create_return_node(AstNode* value);

/* Outras utilidades */
int evaluate_ast(AstNode* node);
void print_ast(AstNode* node, int indent);
void free_ast(AstNode* node);

#endif /* AST_H */
