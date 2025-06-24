#include "conversor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol *symbol_table = NULL;
int indent_level = 0;

// Função auxiliar para impressão de indentação
void print_indent() {
    for (int i = 0; i < indent_level; i++) {
        printf("    ");
    }
}

void init_symbol_table() {
    symbol_table = NULL;
}

Symbol* insert_symbol(const char *c_name, const char *type, int scope) {
    // Verifica se o símbolo já existe
    Symbol *existing = lookup_symbol(c_name);
    if (existing) {
        return existing;
    }
    
    Symbol *new_symbol = (Symbol*)malloc(sizeof(Symbol));
    if (!new_symbol) {
        perror("Erro ao alocar memória para símbolo");
        exit(EXIT_FAILURE);
    }
    
    new_symbol->c_name = strdup(c_name);
    new_symbol->portugol_name = strdup(c_name); // Mantém o mesmo nome por padrão
    new_symbol->type = strdup(type);
    new_symbol->scope = scope;
    new_symbol->next = symbol_table;
    symbol_table = new_symbol;
    
    return new_symbol;
}

Symbol* lookup_symbol(const char *c_name) {
    Symbol *cur = symbol_table;
    while (cur != NULL) {
        if (strcmp(cur->c_name, c_name) == 0) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void free_symbol_table() {
    Symbol *cur = symbol_table;
    while (cur != NULL) {
        Symbol *next = cur->next;
        free(cur->c_name);
        free(cur->portugol_name);
        free(cur->type);
        free(cur);
        cur = next;
    }
    symbol_table = NULL;
}

void print_symbol_table(void) {
    printf("\n===== TABELA DE SÍMBOLOS =====\n");
    printf("%-20s %-20s %-15s %-10s\n", "NOME C", "NOME PORTUGOL", "TIPO", "ESCOPO");
    printf("----------------------------------------\n");
    
    Symbol *cur = symbol_table;
    if (cur == NULL) {
        printf("(tabela vazia)\n");
    }
    
    while (cur != NULL) {
        printf("%-20s %-20s %-15s %-10d\n", 
               cur->c_name ? cur->c_name : "(null)",
               cur->portugol_name ? cur->portugol_name : "(null)",
               cur->type ? cur->type : "(null)", 
               cur->scope);
        cur = cur->next;
    }
    
    printf("==============================\n\n");
}

void print_symbol_table_stderr(void) {
    fprintf(stderr, "\n===== TABELA DE SÍMBOLOS =====\n");
    fprintf(stderr, "%-20s %-20s %-15s %-10s\n", "NOME C", "NOME PORTUGOL", "TIPO", "ESCOPO");
    fprintf(stderr, "----------------------------------------\n");
    
    Symbol *cur = symbol_table;
    if (cur == NULL) {
        fprintf(stderr, "(tabela vazia)\n");
    }
    
    while (cur != NULL) {
        fprintf(stderr, "%-20s %-20s %-15s %-10d\n", 
               cur->c_name ? cur->c_name : "(null)",
               cur->portugol_name ? cur->portugol_name : "(null)",
               cur->type ? cur->type : "(null)", 
               cur->scope);
        cur = cur->next;
    }
    
    fprintf(stderr, "==============================\n\n");
}

const char* c_type_to_portugol(const char *c_type) {
    if (strcmp(c_type, "int") == 0 || strcmp(c_type, "unsigned") == 0) {
        return "inteiro";
    } else if (strcmp(c_type, "float") == 0) {
        return "real";
    } else if (strcmp(c_type, "char") == 0) {
        return "caractere";
    } else if (strcmp(c_type, "void") == 0) {
        return "vazio";
    }
    return c_type; // Retorna o tipo original se não houver conversão
}

void generate_portugol(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
            printf("programa\n{\n");
            indent_level++;
            for (int i = 0; i < node->child_count; i++) {
                generate_portugol(node->children[i]);
            }
            indent_level--;
            printf("}\n");
            break;
            
        case NODE_FUNCTION:
            print_indent();
            // Traduz "main" para "inicio" em Portugol
            if (node->value && strcmp(node->value, "main") == 0) {
                printf("funcao inicio()\n");
            } else {
                printf("funcao %s()\n", node->value ? node->value : "inicio");
            }
            print_indent();
            printf("{\n");
            indent_level++;
            
            // Processa parâmetros (se houver)
            if (node->child_count > 1) {
                generate_portugol(node->children[1]); // Lista de parâmetros
            }
            
            // Processa corpo da função
            if (node->child_count > 2) {
                generate_portugol(node->children[2]); // Bloco de código
            }
            
            indent_level--;
            print_indent();
            printf("}\n");
            break;
            
        case NODE_DECLARATION:
            if (node->child_count > 0) {
                print_indent();
                
                // Obtém o tipo do símbolo
                const char *type = "desconhecido";
                Symbol *sym = lookup_symbol(node->value);
                if (sym) {
                    type = sym->type;
                }
                
                printf("%s %s", c_type_to_portugol(type), node->value);
                
                // Inicialização (se houver)
                if (node->child_count > 1) {
                    printf(" = ");
                    // Verifica se é uma expressão de atribuição simples
                    if (node->children[1]->type == NODE_ASSIGNMENT && 
                        node->children[1]->child_count > 0 && 
                        node->children[1]->children[0]->type == NODE_IDENTIFIER && 
                        node->children[1]->children[0]->value && 
                        node->value && 
                        strcmp(node->children[1]->children[0]->value, node->value) == 0) {
                        // Se a inicialização é uma atribuição para a mesma variável (x = x + ...),
                        // vamos gerar apenas o lado direito
                        if (node->children[1]->child_count > 1) {
                            generate_portugol(node->children[1]->children[1]);
                        }
                    } else {
                        generate_portugol(node->children[1]);
                    }
                }
                
                printf("\n");
            }
            break;
            
        case NODE_ASSIGNMENT:
            if (node->child_count >= 2) {
                print_indent();
                generate_portugol(node->children[0]); // Lado esquerdo
                printf(" %s ", node->value ? node->value : "=");
                generate_portugol(node->children[1]); // Lado direito
                printf("\n");
            }
            break;
            
        case NODE_IF:
            print_indent();
            printf("se (");
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Condição
            }
            printf(")\n");
            
            print_indent();
            printf("{\n");
            indent_level++;
            if (node->child_count > 1) {
                generate_portugol(node->children[1]); // Bloco then
            }
            indent_level--;
            print_indent();
            printf("}\n");
            
            // Else/Else if (se houver)
            if (node->child_count > 2) {
                generate_portugol(node->children[2]);
            }
            break;
            
        case NODE_WHILE:
            print_indent();
            printf("enquanto (");
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Condição
            }
            printf(")\n");
            
            print_indent();
            printf("{\n");
            indent_level++;
            if (node->child_count > 1) {
                generate_portugol(node->children[1]); // Corpo
            }
            indent_level--;
            print_indent();
            printf("}\n");
            break;
            
        case NODE_FOR:
            print_indent();
            printf("para (");
            // Inicialização
            if (node->child_count > 0) {
                generate_portugol(node->children[0]);
            }
            printf("; ");
            
            // Condição
            if (node->child_count > 1) {
                generate_portugol(node->children[1]);
            }
            printf("; ");
            
            // Incremento
            if (node->child_count > 2) {
                generate_portugol(node->children[2]);
            }
            printf(") faca\n");
            
            print_indent();
            printf("{\n");
            indent_level++;
            // Corpo
            if (node->child_count > 3) {
                generate_portugol(node->children[3]);
            }
            indent_level--;
            print_indent();
            printf("}\n");
            break;
            
        case NODE_PRINTF:
            print_indent();
            printf("escreva(");
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Expressão
            }
            printf(")\n");
            break;
            
        case NODE_SCANF:
            print_indent();
            printf("leia(");
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Variável
            }
            printf(")\n");
            break;
            
        case NODE_RETURN:
            print_indent();
            printf("// retorne ");
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Valor de retorno
            }
            printf("\n");
            break;
            
        case NODE_IDENTIFIER:
            printf("%s", node->value ? node->value : "???");
            break;
            
        case NODE_CONST_INT:
            printf("%s", node->value ? node->value : "0");
            break;
            
        case NODE_CONST_FLOAT:
            // Format float values with exactly two decimal places
            if (node->value) {
                float value = atof(node->value);
                printf("%.2f", value);
            } else {
                printf("0.00");
            }
            break;
            
        case NODE_CONST_STRING:
            // The node->value already contains the quotes, so we don't add more
            printf("%s", node->value ? node->value : "\"\"");
            break;
            
        case NODE_CONST_CHAR:
            // The node->value likely already contains the single quotes, so we don't add more
            printf("%s", node->value ? node->value : "' '");
            break;
            
        case NODE_BINARY_OP:
            // Remover parênteses desnecessários para operações básicas
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Operando esquerdo
            }
            printf(" %s ", node->value ? node->value : "?");
            if (node->child_count > 1) {
                generate_portugol(node->children[1]); // Operando direito
            }
            break;
            
        case NODE_UNARY_OP:
            // Handle unary operators
            if (node->value && strcmp(node->value, "nao") == 0) {
                // For 'nao' operator
                printf("nao ");
                
                // Check if the operand is a binary operation that needs parentheses
                if (node->child_count > 0) {
                    if (node->children[0]->type == NODE_BINARY_OP) {
                        printf("(");
                        generate_portugol(node->children[0]); // Operando
                        printf(")");
                    } else {
                        generate_portugol(node->children[0]); // Operando
                    }
                }
            } else {
                // Standard handling for other unary operators
                printf("%s", node->value ? node->value : "?");
                if (node->child_count > 0) {
                    generate_portugol(node->children[0]); // Operando
                }
            }
            break;
            
        case NODE_BREAK:
            print_indent();
            printf("pare\n");
            break;
            
        case NODE_CONTINUE:
            print_indent();
            printf("continue\n");
            break;
            
        case NODE_ELSE_IF:
            print_indent();
            printf("senao se (");
            if (node->child_count > 0) {
                generate_portugol(node->children[0]); // Condição
            }
            printf(")\n");
            print_indent();
            printf("{\n");
            indent_level++;
            if (node->child_count > 1) {
                generate_portugol(node->children[1]); // Bloco then
            }
            indent_level--;
            print_indent();
            printf("}\n");
            
            // Se tem um bloco else ou outro else-if
            if (node->child_count > 2) {
                generate_portugol(node->children[2]);
            }
            break;
            
        case NODE_ELSE:
            print_indent();
            printf("senao\n");
            print_indent();
            printf("{\n");
            indent_level++;
            // Processar o bloco else
            if (node->child_count > 0) {
                generate_portugol(node->children[0]);
            }
            indent_level--;
            print_indent();
            printf("}\n");
            break;
        
        // Casos padrão para estruturas de lista
        case NODE_STATEMENT_LIST:
        case NODE_DECLARATION_LIST:
        case NODE_BLOCK:
            for (int i = 0; i < node->child_count; i++) {
                generate_portugol(node->children[i]);
                
                // Add a blank line after declarations if followed by a control statement
                if (i < node->child_count - 1 && 
                    (node->children[i]->type == NODE_DECLARATION || 
                     (i > 0 && node->children[i-1]->type == NODE_DECLARATION)) && 
                    (node->children[i+1]->type == NODE_IF || 
                     node->children[i+1]->type == NODE_WHILE || 
                     node->children[i+1]->type == NODE_FOR)) {
                    printf("\n");
                }
            }
            break;
            
        default:
            // Suprimir mensagens de debug para nós não implementados
            // Descomentar na fase de depuração se necessário
            // print_indent();
            // printf("// [Nó não implementado: %d]\n", node->type);
            break;
    }
}