#ifndef CONVERSOR_H
#define CONVERSOR_H

#include "ast.h"

typedef struct Symbol {
    char *c_name;        // Nome original em C
    char *portugol_name; // Nome convertido para Portugol
    char *type;          // Tipo de dado (ex: "inteiro", "real")
    int scope;           // Escopo do símbolo
    struct Symbol *next; // Próximo símbolo na tabela
} Symbol;

void init_symbol_table();
Symbol* insert_symbol(const char *c_name, const char *type, int scope);
Symbol* lookup_symbol(const char *c_name);
void free_symbol_table();
void generate_portugol(ASTNode *node);
const char* c_type_to_portugol(const char *c_type);
void print_symbol_table(void);
void print_symbol_table_stderr(void);

#endif