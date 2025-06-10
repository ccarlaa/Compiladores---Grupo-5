/*
 * TRADUTOR C PARA PORTUGOL
 * AST: Árvore Sintática Abstrata para representar estruturas de código
 */
#ifndef AST_H
#define AST_H

/* Tipos de nós na AST */
typedef enum {
    NODE_FUNCTION,      // Função
    NODE_COMMAND_LIST,  // Lista de comandos
    NODE_PARAM_LIST,    // Lista de parâmetros
    NODE_PARAM,         // Parâmetro
    NODE_BLOCK,         // Bloco de comandos
    NODE_VAR_DECL,      // Declaração de variável
    NODE_IF,            // Estrutura condicional if
    NODE_WHILE,         // Estrutura de repetição while
    NODE_FOR,           // Estrutura de repetição for
    NODE_RETURN,        // Comando de retorno
    NODE_ASSIGN,        // Atribuição
    NODE_BINOP,         // Operação binária
    NODE_UNARY,         // Operação unária
    NODE_NUMBER,        // Número inteiro
    NODE_REAL,          // Número real
    NODE_ID,            // Identificador
    NODE_STRING,        // String literal
    NODE_CHAR           // Caractere literal
} NodeType;

/* Tipos de operações binárias */
typedef enum {
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_MOD,    // %
    OP_EQ,     // ==
    OP_NE,     // !=
    OP_LT,     // <
    OP_GT,     // >
    OP_LE,     // <=
    OP_GE,     // >=
    OP_AND,    // &&
    OP_OR,     // ||
    OP_NOT,    // ! (para unário)
    OP_NEG     // - (para unário)
} BinOpType;

/* Estrutura de um nó da AST */
typedef struct AstNode {
    NodeType type;
    // Removed semantic analysis dependency for translator-only mode

    union {
        // NODE_FUNCTION
        struct {
            char* return_type;
            char* name;
            struct AstNode* params;
            struct AstNode* body;
        } function;

        // NODE_COMMAND_LIST, NODE_PARAM_LIST
        struct {
            struct AstNode* first;
            struct AstNode* second;
        } command_list;

        // NODE_PARAM
        struct {
            char* type;
            char* name;
        } param;

        // NODE_BLOCK
        struct {
            struct AstNode* commands;
        } block;

        // NODE_VAR_DECL
        struct {
            char* type;
            char* name;
            struct AstNode* init;
        } var_decl;

        // NODE_IF
        struct {
            struct AstNode* condition;
            struct AstNode* then_block;
            struct AstNode* else_block;
        } if_stmt;

        // NODE_WHILE
        struct {
            struct AstNode* condition;
            struct AstNode* body;
        } while_stmt;

        // NODE_FOR
        struct {
            struct AstNode* init;
            struct AstNode* condition;
            struct AstNode* update;
            struct AstNode* body;
        } for_stmt;

        // NODE_RETURN
        struct {
            struct AstNode* expr;
        } return_stmt;

        // NODE_ASSIGN
        struct {
            char* var;
            struct AstNode* expr;
        } assign;

        // NODE_BINOP
        struct {
            BinOpType op;
            struct AstNode* left;
            struct AstNode* right;
        } binop;

        // NODE_UNARY
        struct {
            BinOpType op;
            struct AstNode* operand;
        } unary;

        // NODE_NUMBER
        struct {
            int value;
        } number;

        // NODE_REAL
        struct {
            float value;
        } real;

        // NODE_ID
        struct {
            char* name;
        } id;

        // NODE_STRING
        struct {
            char* value;
        } string;

        // NODE_CHAR
        struct {
            char* value;
        } character;

        // Manter compatibilidade com código existente
        int value;          // Para NODE_LITERAL
        struct {
            BinOpType op;
            struct AstNode *left;
            struct AstNode *right;
        } equal;           // Para NODE_EQUAL
        
        struct {
            struct AstNode *cond;
            struct AstNode *then_branch;
            struct AstNode *else_branch;
        } if_branch;       // Para compatibilidade
        
        struct {
            struct AstNode *cond;
            struct AstNode *body;
        } while_loop;      // Para compatibilidade
        
        struct {
            struct AstNode *value;
        } ret;             // Para compatibilidade

    } data;
} AstNode;

/* Funções de criação de nós */
AstNode* create_function_node(char* return_type, char* name, AstNode* body);
AstNode* create_command_list_node(AstNode* first, AstNode* second);
AstNode* create_param_list_node(AstNode* first, AstNode* second);
AstNode* create_param_node(char* type, char* name);
AstNode* create_block_node(AstNode* commands);
AstNode* create_var_decl_node(char* type, char* name, AstNode* init);
AstNode* create_if_node(AstNode* condition, AstNode* then_block, AstNode* else_block);
AstNode* create_while_node(AstNode* condition, AstNode* body);
AstNode* create_for_node(AstNode* init, AstNode* condition, AstNode* update, AstNode* body);
AstNode* create_return_node(AstNode* expr);
AstNode* create_assign_node(char* var, AstNode* expr);
AstNode* create_binop_node(BinOpType op, AstNode* left, AstNode* right);
AstNode* create_unary_node(BinOpType op, AstNode* operand);
AstNode* create_number_node(int value);
AstNode* create_real_node(float value);
AstNode* create_id_node(char* name);
AstNode* create_string_node(char* value);
AstNode* create_char_node(char* value);

/* Funções de compatibilidade com código existente */
AstNode* create_literal_node(int value);
AstNode* create_equal_node(AstNode* left, AstNode* right);

/* Outras utilidades */
int evaluate_ast(AstNode* node);
void print_ast(AstNode* node, int indent);
void free_ast(AstNode* node);

#endif /* AST_H */
