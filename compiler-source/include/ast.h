#ifndef AST_H
#define AST_H

typedef enum
{
    NODE_PROGRAM,
    NODE_FUNCTION,
    NODE_TYPE,
    NODE_PARAMETER,
    NODE_PARAM_LIST,
    NODE_BLOCK,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_IDENTIFIER,
    NODE_CONST_INT,
    NODE_CONST_FLOAT,
    NODE_CONST_STRING,
    NODE_CONST_CHAR,
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_IF,
    NODE_ELSE_IF,
    NODE_ELSE,
    NODE_WHILE,
    NODE_DO_WHILE,
    NODE_FOR,
    NODE_PRINTF,
    NODE_SCANF,
    NODE_RETURN,
    NODE_STRUCT,
    NODE_STRUCT_MEMBER,
    NODE_STRUCT_MEMBER_LIST,
    NODE_SWITCH,
    NODE_CASE,
    NODE_DEFAULT,
    NODE_CASE_LIST,
    NODE_STATEMENT_LIST,
    NODE_DECLARATION_LIST,
    NODE_FUNCTION_CALL,
    NODE_MEMBER_ACCESS,
    NODE_POINTER_ACCESS,
    NODE_BREAK,
    NODE_CONTINUE,
    NODE_EMPTY
} NodeType;

typedef struct ASTNode
{
    NodeType type;
    char *value;
    struct ASTNode **children;
    int child_count;
} ASTNode;

ASTNode *create_node(NodeType type, const char *value);
void add_child(ASTNode *parent, ASTNode *child);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int depth);
void print_ast_stderr(ASTNode *node, int depth);

#endif