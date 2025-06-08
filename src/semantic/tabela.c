#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic/tabela.h"

#define MAX_SIMBOLOS 1024

typedef struct
{
    char nome[64];
    TipoSimples tipo;
} Simbolo;

static Simbolo tabela[MAX_SIMBOLOS];
static int contador = 0;

void inicializa_tabela()
{
    contador = 0;
}

int insere_simbolo(const char *nome, TipoSimples tipo)
{
    for (int i = 0; i < contador; i++)
    {
        if (strcmp(tabela[i].nome, nome) == 0)
        {
            return 0;
        }
    }

    if (contador < MAX_SIMBOLOS)
    {
        strncpy(tabela[contador].nome, nome, sizeof(tabela[contador].nome) - 1);
        tabela[contador].nome[sizeof(tabela[contador].nome) - 1] = '\0';
        tabela[contador].tipo = tipo;
        contador++;
        return 1;
    }

    fprintf(stderr, "Erro: Tabela de símbolos cheia.\n");
    exit(1);
}

TipoSimples busca_simbolo(const char *nome)
{
    for (int i = 0; i < contador; i++)
    {
        if (strcmp(tabela[i].nome, nome) == 0)
        {
            return tabela[i].tipo;
        }
    }
    return TIPO_INVALIDO;
}
