#include "conversor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol *symbol_table = NULL;
int indent_level = 0;

// Função auxiliar para impressão de indentação
void print_indent()
{
    for (int i = 0; i < indent_level; i++)
    {
        printf("    ");
    }
}

void init_symbol_table()
{
    symbol_table = NULL;
}

Symbol *insert_symbol(const char *c_name, const char *type, int scope)
{
    // Verifica se o símbolo já existe
    Symbol *existing = lookup_symbol(c_name);
    if (existing)
    {
        return existing;
    }

    Symbol *new_symbol = (Symbol *)malloc(sizeof(Symbol));
    if (!new_symbol)
    {
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

Symbol *lookup_symbol(const char *c_name)
{
    Symbol *cur = symbol_table;
    while (cur != NULL)
    {
        if (strcmp(cur->c_name, c_name) == 0)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void free_symbol_table()
{
    Symbol *cur = symbol_table;
    while (cur != NULL)
    {
        Symbol *next = cur->next;
        free(cur->c_name);
        free(cur->portugol_name);
        free(cur->type);
        free(cur);
        cur = next;
    }
    symbol_table = NULL;
}

void print_symbol_table(void)
{
    printf("\n===== TABELA DE SÍMBOLOS =====\n");
    printf("%-20s %-20s %-15s %-10s\n", "NOME C", "NOME PORTUGOL", "TIPO", "ESCOPO");
    printf("----------------------------------------\n");

    Symbol *cur = symbol_table;
    if (cur == NULL)
    {
        printf("(tabela vazia)\n");
    }

    while (cur != NULL)
    {
        printf("%-20s %-20s %-15s %-10d\n",
               cur->c_name ? cur->c_name : "(null)",
               cur->portugol_name ? cur->portugol_name : "(null)",
               cur->type ? cur->type : "(null)",
               cur->scope);
        cur = cur->next;
    }

    printf("==============================\n\n");
}

void print_symbol_table_stderr(void)
{
    fprintf(stderr, "\n===== TABELA DE SÍMBOLOS =====\n");
    fprintf(stderr, "%-20s %-20s %-15s %-10s\n", "NOME C", "NOME PORTUGOL", "TIPO", "ESCOPO");
    fprintf(stderr, "----------------------------------------\n");

    Symbol *cur = symbol_table;
    if (cur == NULL)
    {
        fprintf(stderr, "(tabela vazia)\n");
    }

    while (cur != NULL)
    {
        fprintf(stderr, "%-20s %-20s %-15s %-10d\n",
                cur->c_name ? cur->c_name : "(null)",
                cur->portugol_name ? cur->portugol_name : "(null)",
                cur->type ? cur->type : "(null)",
                cur->scope);
        cur = cur->next;
    }

    fprintf(stderr, "==============================\n\n");
}

const char *c_type_to_portugol(const char *c_type)
{
    if (strcmp(c_type, "int") == 0 || strcmp(c_type, "unsigned") == 0)
    {
        return "inteiro";
    }
    else if (strcmp(c_type, "float") == 0)
    {
        return "real";
    }
    else if (strcmp(c_type, "char") == 0)
    {
        return "caractere";
    }
    else if (strcmp(c_type, "void") == 0)
    {
        return "vazio";
    }
    return c_type; // Retorna o tipo original se não houver conversão
}

void add_parameters_to_symbol_table(ASTNode *param_list_node)
{

    if (!param_list_node || param_list_node->type != NODE_PARAM_LIST)
    {
        return;
    }

    for (int i = 0; i < param_list_node->child_count; i++)
    {
        ASTNode *param_node = param_list_node->children[i];

        if (param_node && param_node->type == NODE_PARAMETER)
        {
            const char *param_name = param_node->value;

            if (param_node->child_count > 0)
            {
                ASTNode *type_node = param_node->children[0];
                const char *type_name = type_node->value;

                insert_symbol(param_name, type_name, current_scope);
            }
        }
    }
}

void generate_portugol(ASTNode *node)
{
    if (!node)
        return;

    switch (node->type)
    {
    case NODE_PROGRAM:
        printf("programa\n{\n");
        indent_level++;
        for (int i = 0; i < node->child_count; i++)
        {
            generate_portugol(node->children[i]);
        }
        indent_level--;
        printf("}\n");
        break;

    case NODE_FUNCTION:
    {
        print_indent();

        const char *return_type_str = "vazio"; // Valor padrão
        if (node->child_count > 0 && node->children[0]->type == NODE_TYPE)
        {
            return_type_str = c_type_to_portugol(node->children[0]->value);
        }

        // Obter o nome da funcao
        const char *func_name = "inicio";
        if (node->value && strcmp(node->value, "main") != 0)
        {
            func_name = node->value;
        }
        else if (!node->value)
        {
            func_name = "desconhecida";
        }

        // Se a funcao for "inicio", o tipo de retorno nao e impresso
        if (strcmp(func_name, "inicio") == 0)
        {
            printf("funcao %s(", func_name);
        }
        else
        {
            // Imprimir  funcao <tipo> <nome> ...
            printf("funcao %s %s(", return_type_str, func_name);
        }

        // Processa a lista de parametros
        if (node->child_count > 1)
        {
            generate_portugol(node->children[1]);
        }

        printf(")\n");

        print_indent();
        printf("{\n");
        indent_level++;

        // Processa o corpo da funcao
        if (node->child_count > 2)
        {
            generate_portugol(node->children[2]);
        }

        indent_level--;
        print_indent();
        printf("}\n\n");
        break;
    }

    case NODE_PARAM_LIST:
        // caso para a lista de parametros
        for (int i = 0; i < node->child_count; i++)
        {
            if (i > 0)
            {
                printf(", ");
            }
            generate_portugol(node->children[i]);
        }
        break;

    // caso para um único parâmetro
    case NODE_PARAMETER:
        if (node->value)
        {
            Symbol *sym = lookup_symbol(node->value);
            if (sym)
            {
                // Usa a tabela de símbolos para obter o tipo e nome corretos
                printf("%s %s", c_type_to_portugol(sym->type), sym->portugol_name);
            }
            else
            {
                // caso o símbolo não seja encontrado
                printf("desconhecido %s", node->value);
            }
        }
        break;

    case NODE_DECLARATION:
        if (node->child_count > 0)
        {
            print_indent();

            // Obtém o tipo do símbolo
            const char *type = "desconhecido";
            Symbol *sym = lookup_symbol(node->value);
            if (sym)
            {
                type = sym->type;
            }

            printf("%s %s", c_type_to_portugol(type), node->value);

            // Inicialização (se houver)
            if (node->child_count > 1)
            {
                printf(" = ");
                // Verifica se é uma expressão de atribuição simples
                if (node->children[1]->type == NODE_ASSIGNMENT &&
                    node->children[1]->child_count > 0 &&
                    node->children[1]->children[0]->type == NODE_IDENTIFIER &&
                    node->children[1]->children[0]->value &&
                    node->value &&
                    strcmp(node->children[1]->children[0]->value, node->value) == 0)
                {
                    // Se a inicialização é uma atribuição para a mesma variável (x = x + ...),
                    // vamos gerar apenas o lado direito
                    if (node->children[1]->child_count > 1)
                    {
                        generate_portugol(node->children[1]->children[1]);
                    }
                }
                else
                {
                    generate_portugol(node->children[1]);
                }
            }

            printf("\n");
        }
        break;

    case NODE_ASSIGNMENT:
        if (node->child_count >= 2)
        {
            print_indent();
            generate_portugol(node->children[0]); // Lado esquerdo
            printf(" %s ", node->value ? node->value : "=");
            generate_portugol(node->children[1]); // Lado direito
            printf("\n");
        }
        break;

    case NODE_IF:
        // Imprime a estrutura if
        print_indent();
        printf("se (");
        if (node->child_count > 0)
        {
            generate_portugol(node->children[0]); // Condição
        }
        printf(")\n");

        print_indent();
        printf("{\n");
        indent_level++;
        if (node->child_count > 1)
        {
            generate_portugol(node->children[1]); // Bloco then
        }
        indent_level--;
        print_indent();
        printf("}\n");

        // Else/Else if (se houver)
        if (node->child_count > 2)
        {
            generate_portugol(node->children[2]);
        }
        break;

    case NODE_WHILE:
        // Imprime a estrutura while
        print_indent();
        printf("enquanto (");
        if (node->child_count > 0)
        {
            generate_portugol(node->children[0]); // Condição
        }
        printf(")\n");

        print_indent();
        printf("{\n");
        indent_level++;
        if (node->child_count > 1)
        {
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
        if (node->child_count > 0)
        {
            generate_portugol(node->children[0]);
        }
        printf("; ");

        // Condição
        if (node->child_count > 1)
        {
            generate_portugol(node->children[1]);
        }
        printf("; ");

        // Incremento
        if (node->child_count > 2)
        {
            generate_portugol(node->children[2]);
        }
        printf(") faca\n");

        print_indent();
        printf("{\n");
        indent_level++;
        // Corpo
        if (node->child_count > 3)
        {
            generate_portugol(node->children[3]);
        }
        indent_level--;
        print_indent();
        printf("}\n");
        break;

    case NODE_FUNCTION_CALL:
        // Imprime a chamada de função
        if (node->value && node->child_count > 0)
        {
            print_indent();
            printf("%s(", node->value);

            ASTNode *arg_list = node->children[0];
            if (arg_list)
            {
                for (int i = 0; i < arg_list->child_count; i++)
                {
                    if (i > 0)
                    {
                        printf(", ");
                    }
                    generate_portugol(arg_list->children[i]);
                }
            }
            printf(")\n");
        }
        break;

    case NODE_PRINTF:
    {
        print_indent();
        printf("escreva(");

        if (node->child_count > 0 && node->children[0]->child_count > 0)
        {
            ASTNode *arg_list = node->children[0];
            ASTNode *first_arg = arg_list->children[0];

            // Verifica se o primeiro argumento e uma string literal, que e a string de formatação
            if (first_arg->type == NODE_CONST_STRING && first_arg->value)
            {
                const char *format_string = first_arg->value;
                int len = strlen(format_string);
                int var_arg_index = 1; // indice para os outros argumentos
                char buffer[256];      // Buffer para acumular partes da string
                int buffer_idx = 0;
                int first_output = 1; // Flag para controlar a virgula

                // Itera sobre a string de formatacao, ignorando as aspas iniciais e finais
                for (int i = 1; i < len - 1; i++)
                {
                    if (format_string[i] == '%')
                    {
                        // Imprime o que estiver no buffer antes do '%
                        if (buffer_idx > 0)
                        {
                            buffer[buffer_idx] = '\0';
                            if (!first_output)
                                printf(", ");
                            printf("\"%s\"", buffer);
                            first_output = 0;
                            buffer_idx = 0;
                        }

                        // Pula o '%' e processa o especificador
                        i++;

                        //  Imprime a variavel correspondente da lista de argumentos
                        if (var_arg_index < arg_list->child_count)
                        {
                            if (!first_output)
                                printf(", ");
                            generate_portugol(arg_list->children[var_arg_index]);
                            var_arg_index++;
                            first_output = 0;
                        }
                    }
                    else if (format_string[i] == '\\' && i + 1 < len - 1 && format_string[i + 1] == 'n')
                    {
                        // Encontrou um '\n'
                        // Imprime o que estiver no buffer antes do '\n'
                        if (buffer_idx > 0)
                        {
                            buffer[buffer_idx] = '\0';
                            if (!first_output)
                                printf(", ");
                            printf("\"%s\"", buffer);
                            first_output = 0;
                            buffer_idx = 0;
                        }

                        // Imprime o "\n" como um argumento separado
                        if (!first_output)
                            printf(", ");
                        printf("\"\\n\"");
                        first_output = 0;
                        i++; // Pula o 'n'
                    }
                    else
                    {
                        // Acumula caracteres normais no buffer
                        buffer[buffer_idx++] = format_string[i];
                    }
                }

                // Imprime qualquer texto restante no buffer apos o loop
                if (buffer_idx > 0)
                {
                    buffer[buffer_idx] = '\0';
                    if (!first_output)
                        printf(", ");
                    printf("\"%s\"", buffer);
                }
            }
            else
            {
                // se o primeiro argumento nao for uma string, usa a logica simples
                for (int i = 0; i < arg_list->child_count; i++)
                {
                    if (i > 0)
                        printf(", ");
                    generate_portugol(arg_list->children[i]);
                }
            }
        }

        printf(")\n");
        break;
    }

    case NODE_PRINTF_ARGS:
        // Imprime os argumentos de printf
        for (int i = 0; i < node->child_count; i++)
        {
            if (i > 0)
            {
                printf(", ");
            }
            generate_portugol(node->children[i]);
        }
        break;

    case NODE_SCANF:
        // Imprime a chamada de scanf
        print_indent();
        printf("leia(");
        if (node->child_count > 0)
        {
            generate_portugol(node->children[0]); // Variável
        }
        printf(")\n");
        break;

    case NODE_RETURN:
        print_indent();
        printf("retorne ");
        if (node->child_count > 0)
        {
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
        // valores decimais
        if (node->value)
        {
            float value = atof(node->value);
            printf("%.2f", value);
        }
        else
        {
            printf("0.00");
        }
        break;

    case NODE_CONST_STRING:
        // imprime a string entre aspas duplas
        printf("%s", node->value ? node->value : "\"\"");
        break;

    case NODE_CONST_CHAR:
        // imprime o caractere entre aspas simples
        printf("%s", node->value ? node->value : "' '");
        break;

    case NODE_BINARY_OP:
        // operações binárias
        if (node->child_count > 0)
        {
            generate_portugol(node->children[0]); // Operando esquerdo
        }
        printf(" %s ", node->value ? node->value : "?");
        if (node->child_count > 1)
        {
            generate_portugol(node->children[1]); // Operando direito
        }
        break;

    case NODE_UNARY_OP:
        // Handle unary operators
        if (node->value && strcmp(node->value, "nao") == 0)
        {
            // For 'nao' operator
            printf("nao ");

            // Check if the operand is a binary operation that needs parentheses
            if (node->child_count > 0)
            {
                if (node->children[0]->type == NODE_BINARY_OP)
                {
                    printf("(");
                    generate_portugol(node->children[0]); // Operando
                    printf(")");
                }
                else
                {
                    generate_portugol(node->children[0]); // Operando
                }
            }
        }
        else
        {
            // Standard handling for other unary operators
            printf("%s", node->value ? node->value : "?");
            if (node->child_count > 0)
            {
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
        if (node->child_count > 0)
        {
            generate_portugol(node->children[0]); // Condição
        }
        printf(")\n");
        print_indent();
        printf("{\n");
        indent_level++;
        if (node->child_count > 1)
        {
            generate_portugol(node->children[1]); // Bloco then
        }
        indent_level--;
        print_indent();
        printf("}\n");

        // Se tem um bloco else ou outro else-if
        if (node->child_count > 2)
        {
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
        if (node->child_count > 0)
        {
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
        for (int i = 0; i < node->child_count; i++)
        {
            generate_portugol(node->children[i]);

            // Adiciona uma nova linha entre declarações e estruturas de controle
            if (i < node->child_count - 1 &&
                (node->children[i]->type == NODE_DECLARATION ||
                 (i > 0 && node->children[i - 1]->type == NODE_DECLARATION)) &&
                (node->children[i + 1]->type == NODE_IF ||
                 node->children[i + 1]->type == NODE_WHILE ||
                 node->children[i + 1]->type == NODE_FOR))
            {
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